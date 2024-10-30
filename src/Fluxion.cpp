#include "shared/Fluxion.h"

#include <cstdint>
#include <fstream>

void Fluxion::Write(FluxionNode* node, std::ostream* stream, const Encoding* encoding, unsigned char version)
{
    bool written = false;
    while (true)
    {
        if (written) break;
        switch (version)
        {
        case 0:
            {
                version = 2;
                continue;
            }
        case 1:
            {
                Write_V1(node, stream, encoding, true);
                written = true;
                break;
            }
        case 2:
            {
                std::vector<AnalyzedDataContent> adc(0);
                Write_V2(node, stream, encoding, &adc, true);
                written = true;
                break;
            }
        default:
            throw FluxionUnsupportedVersionException(version);
        }
    }
}

void Fluxion::Write_V1(FluxionNode* node, std::ostream* stream, const Encoding* encoding, const bool asRoot)
{
    if (asRoot)
    {
        node->IsRoot = true;
        node->setVersion(1);
        stream->put(0x46);
        stream->put(0x4C);
        stream->put(0x58);
        stream->put(static_cast<char>(node->getVersion()));
        stream->put(static_cast<char>(encoding->ID()));
    }

    const auto children = node->GetChildren();

    auto valueType = node->Value->ValueTypeIndex(1);
    if (!node->Name.empty())
        valueType = valueType ^ 16;
    if (children.empty())
        valueType = valueType ^ 32;
    if (node->Attributes.empty())
        valueType = valueType ^ 64;

    stream->put(static_cast<char>(valueType));

    if (!children.empty())
    {
        WriteVarInt(*stream, children.size());
    }

    if (!node->Name.empty())
    {
        WriteArrayWithVarInt(*stream, encoding->string_to_bytes(node->Name));
    }

    if (node->Value->Type == String)
    {
        WriteArrayWithVarInt(*stream, encoding->string_to_bytes(node->Value->Value.stringValue));
    }
    else if (node->Value->Type == ByteArray)
    {
        WriteArrayWithVarInt(*stream, node->Value->Value.byteArrayValue);
    }
    else
    {
        const auto bytes = node->Value->GetBytes(encoding);
        const auto* charData = reinterpret_cast<const std::ostream::char_type*>(bytes.data());
        const size_t dataSize = bytes.size();
        stream->write(charData, static_cast<long>(dataSize));
    }

    if (!node->Attributes.empty())
    {
        WriteVarInt(*stream, node->Attributes.size());

        for (const auto attribute : node->Attributes)
        {
            auto attr_valueType = attribute->Value->ValueTypeIndex(1);
            if (!attribute->Name.empty())
                attr_valueType = attr_valueType ^ 16;
            stream->put(static_cast<char>(attr_valueType));

            if (!attribute->Name.empty())
            {
                WriteArrayWithVarInt(*stream, encoding->string_to_bytes(attribute->Name));
            }

            if (attribute->Value->Type == String)
            {
                WriteArrayWithVarInt(*stream, encoding->string_to_bytes(attribute->Value->Value.stringValue));
            }
            else if (attribute->Value->Type == ByteArray)
            {
                WriteArrayWithVarInt(*stream, attribute->Value->Value.byteArrayValue);
            }
            else
            {
                const auto bytes = attribute->Value->GetBytes(encoding);
                const auto* charData = reinterpret_cast<const std::ostream::char_type*>(bytes.data());
                const size_t dataSize = bytes.size();
                stream->write(charData, static_cast<long>(dataSize));
            }
        }
    }

    if (!children.empty())
        for (const auto sub_node : children)
            Write_V1(&*sub_node, stream, encoding, false);
}

long Fluxion::Estimate_V2(FluxionNode* node, const Encoding* encoding, std::vector<AnalyzedDataContent>* adc)
{
    long estimation = 0;

    if (adc == nullptr)
    {
        std::vector<AnalyzedDataContent> new_adc(0);
        adc = &new_adc;
    }

    if (!node->Name.empty() && !ADC_Contains(adc, new FluxionValue(node->Name)))
    {
        auto newName = new FluxionValue(node->Name);
        auto newData = new AnalyzedDataContent(newName);
        adc->insert(adc->end(), *newData);
        estimation += newName->EstimateSize(encoding);
    }

    if (!node->Value->IsEmpty() && !ADC_Contains(adc, node->Value))
    {
        auto newData = new AnalyzedDataContent(node->Value);
        adc->insert(adc->end(), *newData);
        estimation += node->Value->EstimateSize(encoding);
    }

    if (!node->Attributes.empty())
    {
        for (const auto attribute : node->Attributes)
        {
            if (!attribute->Name.empty() && !ADC_Contains(adc, new FluxionValue(attribute->Name)))
            {
                auto newName = new FluxionValue(attribute->Name);
                auto newData = new AnalyzedDataContent(newName);
                adc->insert(adc->end(), *newData);
                estimation += newName->EstimateSize(encoding);
            }

            if (!attribute->Value->IsEmpty() && !ADC_Contains(adc, attribute->Value))
            {
                auto newData = new AnalyzedDataContent(attribute->Value);
                adc->insert(adc->end(), *newData);
                estimation += attribute->Value->EstimateSize(encoding);
            }
        }
    }

    const auto children = node->GetChildren();
    if (children.empty()) return estimation;

    for (const auto child : children)
    {
        estimation += Estimate_V2(child, encoding, adc);
    }

    return estimation;
}

long Fluxion::WriteData_V2(std::ostream* stream, const Encoding* encoding,
                           const std::vector<AnalyzedDataContent>* adc)
{
    if (adc->empty()) return stream->tellp();
    for (auto& item : *adc)
    {
        item.Position = stream->tellp();
        item.Value->WriteValueV2(stream, encoding);
    }
    return stream->tellp();
}

bool Fluxion::ADC_Contains(const std::vector<AnalyzedDataContent>* adc, const FluxionValue* targetValue)
{
    if (adc->empty()) return false;
    for (auto item : *adc)
    {
        if (item.Value->IsEmpty()) continue;
        if (item.Value->ValueTypeIndex(2) != targetValue->ValueTypeIndex(2)) continue;
        if (item.Value == targetValue) return true;
    }
    return false;
}

void Fluxion::Write_V2(FluxionNode* node, std::ostream* stream, const Encoding* encoding,
                       std::vector<AnalyzedDataContent>* adc, const bool asRoot)
{
    if (asRoot)
    {
        node->IsRoot = true;
        node->setVersion(2);
        stream->put(0x46);
        stream->put(0x4C);
        stream->put(0x58);
        stream->put(static_cast<char>(node->getVersion()));
        stream->put(static_cast<char>(encoding->ID()));

        // Estimate Data size
        auto dataSize = Estimate_V2(node, encoding, adc);
        auto data_Size = dataSize;
        int bytes = 1;
        while ((data_Size >>= 7) != 0)
            bytes++;
        auto dataEndPos = bytes + dataSize + stream->tellp();
        WriteVarInt(*stream, dataEndPos);

        auto dataEndPos2 = WriteData_V2(stream, encoding, adc);

        if (dataEndPos != dataEndPos2)
            throw FluxionEstimationException(dataEndPos, dataEndPos2);
    }

    const auto children = node->GetChildren();

    auto valueType = node->Value->ValueTypeIndex(2);
    if (!node->Name.empty())
        valueType = valueType ^ 16;
    if (children.empty())
        valueType = valueType ^ 32;
    if (node->Attributes.empty())
        valueType = valueType ^ 64;
    if (node->Value->UniqueFlagSet())
        valueType = valueType ^ 128;

    stream->put(static_cast<char>(valueType));

    if (!children.empty())
    {
        WriteVarInt(*stream, children.size());
    }

    if (!node->Name.empty())
    {
        auto targetValue = new FluxionValue(node->Name);
        for (auto item : *adc)
        {
            if (item.Value->IsEmpty()) continue;
            if (item.Value->ValueTypeIndex(2) != targetValue->ValueTypeIndex(2)) continue;
            if (item.Value == targetValue)
            {
                WriteVarLong(*stream, item.Position);
                break;
            }
        }
    }

    for (auto item : *adc)
    {
        if (item.Value->IsEmpty()) continue;
        if (item.Value->ValueTypeIndex(2) != node->Value->ValueTypeIndex(2)) continue;
        if (item.Value == node->Value)
        {
            WriteVarInt(*stream, item.Position);
            break;
        }
    }
    if (!node->Attributes.empty())
    {
        WriteVarInt(*stream, node->Attributes.size());

        for (const auto attribute : node->Attributes)
        {
            auto attr_valueType = attribute->Value->ValueTypeIndex(2);
            if (!attribute->Name.empty())
                attr_valueType = attr_valueType ^ 16;
            if (attribute->Value->UniqueFlagSet())
                attr_valueType = attr_valueType ^ 128;
            stream->put(static_cast<char>(attr_valueType));

            if (!attribute->Name.empty())
            {
                auto targetValue = new FluxionValue(attribute->Name);
                for (auto item : *adc)
                {
                    if (item.Value->IsEmpty()) continue;
                    if (item.Value->ValueTypeIndex(2) != targetValue->ValueTypeIndex(2)) continue;
                    if (item.Value == targetValue)
                    {
                        WriteVarInt(*stream, item.Position);
                        break;
                    }
                }
            }

            for (auto item : *adc)
            {
                if (item.Value->IsEmpty()) continue;
                if (item.Value->ValueTypeIndex(2) != attribute->Value->ValueTypeIndex(2)) continue;
                if (item.Value == attribute->Value)
                {
                    WriteVarInt(*stream, item.Position);
                    break;
                }
            }
        }
    }

    if (!children.empty())
        for (const auto sub_node : children)
            Write_V2(&*sub_node, stream, encoding, adc, false);
}

FluxionNode* Fluxion::Read(std::istream& stream)
{
    auto root = new FluxionNode;
    root->IsRoot = true;

    const auto byte_F = stream.get();
    const auto byte_L = stream.get();
    const auto byte_X = stream.get();

    if (byte_F != 0x46 && byte_L != 0x4C && byte_X != 0x58)
        throw FluxionInvalidHeaderException();

    const auto versionByte = stream.get();
    if (versionByte == -1)
        throw FluxionEndOfStreamException();

    const auto encodingByte = stream.get();
    if (encodingByte == -1)
        throw FluxionEndOfStreamException();
    const Encoding* encoding = GetEncoding(encodingByte);
    root->setVersion(versionByte);

    switch (versionByte)
    {
    case 1:
        root = ReadRecurse_V1(stream, encoding, root, true);
        break;

    case 2:
        root = ReadRecurse_V2(stream, encoding, root, true);
        break;

    default:
        throw FluxionUnsupportedVersionException(static_cast<unsigned char>(versionByte));
    }

    return root;
}

FluxionNode* Fluxion::ReadRecurse_V1(std::istream& stream, const Encoding* encoding, FluxionNode* root,
                                     bool readRoot)
{
    const auto node = readRoot ? root : new FluxionNode();
    if (!readRoot)
    {
        node->IsRoot = false;
        node->Parent = root;
    }
    auto valueType = stream.get();
    if (valueType == -1)
        throw FluxionEndOfStreamException();
    const bool hasName = valueType & 16;
    const bool noChild = valueType & 32;
    const bool noAttr = valueType & 64;
    valueType -= hasName ? 16 : 0;
    valueType -= noChild ? 32 : 0;
    valueType -= noAttr ? 64 : 0;

    int children_count = 0;
    if (!noChild)
    {
        children_count = static_cast<int>(DecodeVarInt(stream));
        if (children_count == -1)
            throw FluxionEndOfStreamException();
    }

    if (hasName)
    {
        node->Name = encoding->bytes_to_string(DecodeByteArrWithVarInt(stream));
    }

    node->Value = ReadBytesFromType_V1(stream, valueType, encoding);

    if (!noAttr)
    {
        int attributes_count = static_cast<int>(DecodeVarInt(stream));
        if (attributes_count == -1)
            throw FluxionEndOfStreamException();

        for (auto i = 0; i < attributes_count; i++)
        {
            auto attr = new FluxionAttribute();

            auto attr_valueType = stream.get();
            if (attr_valueType == -1)
                throw FluxionEndOfStreamException();
            const bool attr_HasName = attr_valueType & 16;
            attr_valueType -= attr_HasName ? 16 : 0;

            if (attr_HasName)
            {
                attr->Name = encoding->bytes_to_string(DecodeByteArrWithVarInt(stream));
            }

            attr->Value = ReadBytesFromType_V1(stream, attr_valueType, encoding);

            node->Attributes.insert(node->Attributes.end(), attr);
        }
    }

    if (!noChild)
        for (auto i = 0; i < children_count; i++)
            node->Add(ReadRecurse_V1(stream, encoding, node, false));

    return node;
}

FluxionNode* Fluxion::ReadRecurse_V2(std::istream& stream, const Encoding* encoding, FluxionNode* root,
                                     bool readRoot)
{
    const auto node = readRoot ? root : new FluxionNode();
    if (!readRoot)
    {
        node->IsRoot = false;
        node->Parent = root;
    }
    else
    {
        auto treeMarkPos = static_cast<long>(DecodeVarLong(stream));
        stream.seekg(treeMarkPos);
    }
    auto valueType = stream.get();
    if (valueType == -1)
        throw FluxionEndOfStreamException();

    const bool hasName = valueType & 16;
    const bool noChild = valueType & 32;
    const bool noAttr = valueType & 64;
    const bool uniqueFlag = valueType & 128;
    valueType -= hasName ? 16 : 0;
    valueType -= noChild ? 32 : 0;
    valueType -= noAttr ? 64 : 0;
    valueType -= uniqueFlag ? 128 : 0;

    int children_count = 0;
    if (!noChild)
    {
        children_count = static_cast<int>(DecodeVarInt(stream));
        if (children_count == -1)
            throw FluxionEndOfStreamException();
    }

    if (hasName)
    {
        auto namePos = static_cast<long>(DecodeVarLong(stream));
        auto pos = stream.tellg();
        stream.seekg(namePos);
        node->Name = encoding->bytes_to_string(DecodeByteArrWithVarInt(stream));
        stream.seekg(pos);
    }

    node->Value = ReadBytesFromType_V2(stream, valueType, encoding, uniqueFlag);

    if (!noAttr)
    {
        int attributes_count = static_cast<int>(DecodeVarInt(stream));
        if (attributes_count == -1)
            throw FluxionEndOfStreamException();

        for (auto i = 0; i < attributes_count; i++)
        {
            auto attr = new FluxionAttribute();

            auto attr_valueType = stream.get();
            if (attr_valueType == -1)
                throw FluxionEndOfStreamException();
            const bool attr_HasName = attr_valueType & 16;
            attr_valueType -= attr_HasName ? 16 : 0;
            const bool attr_uniqueFlag = attr_valueType & 128;
            attr_valueType -= attr_uniqueFlag ? 128 : 0;

            if (attr_HasName)
            {
                auto attr_namePos = static_cast<long>(DecodeVarLong(stream));
                auto pos = stream.tellg();
                stream.seekg(attr_namePos);
                attr->Name = encoding->bytes_to_string(DecodeByteArrWithVarInt(stream));
                stream.seekg(pos);
            }

            attr->Value = ReadBytesFromType_V2(stream, attr_valueType, encoding, attr_uniqueFlag);

            node->Attributes.insert(node->Attributes.end(), attr);
        }
    }

    if (noChild)
        return node;

    for (auto i = 0; i < children_count; i++)
        node->Add(ReadRecurse_V2(stream, encoding, node, false));

    return node;
}

void Fluxion::Write(FluxionNode* node, const std::string& fileName, const Encoding* encoding,
                    unsigned char version)
{
    encoding = encoding == nullptr ? new UTF8Encoding : encoding;
    std::ofstream stream(fileName, std::ios::binary | std::ios::out | std::ios::trunc);

    if (!stream.is_open())
    {
        throw std::runtime_error("Failed to create or open file \"" + fileName + "\".");
    }

    Write(node, &stream, encoding, version);
}

FluxionNode* Fluxion::Read(const std::string& fileName)
{
    std::ifstream fs(fileName, std::ios::binary | std::ios::in);
    if (!fs.is_open())
    {
        throw std::runtime_error("Failed to open file \"" + fileName + "\".");
    }
    return Read(fs);
}

FluxionValue* Fluxion::ReadBytesFromType_V1(std::istream& stream, const unsigned char valueType,
                                            const Encoding* encoding)
{
    switch (valueType)
    {
    case 0:
        return new FluxionValue(nullptr);
    case 1:
        return new FluxionValue(true);
    case 2:
        return new FluxionValue(false);
    case 3:
        {
            const auto byteValue = stream.get();
            if (byteValue == -1)
                throw FluxionEndOfStreamException();
            return new FluxionValue(byteValue);
        }
    case 4:
        {
            const auto signedByteValue = stream.get();
            if (signedByteValue == -1)
                throw FluxionEndOfStreamException();
            return new FluxionValue(static_cast<signed char>(signedByteValue));
        }
    case 5:
        {
            const auto charValue = new FluxionValue(0);
            charValue->ReadValue(stream);
            return charValue;
        }
    case 6:
        {
            const auto shortValue = new FluxionValue(0);
            shortValue->ReadValue(stream);
            return shortValue;
        }
    case 7:
        {
            const auto unsignedShortValue = new FluxionValue(0);
            unsignedShortValue->ReadValue(stream);
            return unsignedShortValue;
        }
    case 8:
        {
            const auto intValue = new FluxionValue(0);
            intValue->ReadValue(stream);
            return intValue;
        }
    case 9:
        {
            const auto uintValue = new FluxionValue(0);
            uintValue->ReadValue(stream);
            return uintValue;
        }
    case 10:
        {
            const auto longValue = new FluxionValue(0);
            longValue->ReadValue(stream);
            return longValue;
        }
    case 11:
        {
            const auto unsignedLongValue = new FluxionValue(0);
            unsignedLongValue->ReadValue(stream);
            return unsignedLongValue;
        }
    case 12:
        {
            const auto floatValue = new FluxionValue(0);
            floatValue->ReadValue(stream);
            return floatValue;
        }
    case 13:
        {
            const auto doubleValue = new FluxionValue(0);
            doubleValue->ReadValue(stream);
            return doubleValue;
        }
    case 14:
        return new FluxionValue(encoding->bytes_to_string(DecodeByteArrWithVarInt(stream)));
    case 15:
        return new FluxionValue(DecodeByteArrWithVarInt(stream));
    default:
        throw FluxionValueTypeException(valueType);
    }
}

FluxionValue* Fluxion::ReadBytesFromType_V2(std::istream& stream, const unsigned char valueType,
                                            const Encoding* encoding,
                                            bool uniqueFlag)
{
    switch (valueType)
    {
    case 0:
        if (uniqueFlag)
            return new FluxionValue(0);
        return new FluxionValue(nullptr);
    case 1:
        if (uniqueFlag)
            return new FluxionValue(0);
        return new FluxionValue(true);
    case 2:
        if (uniqueFlag)
            return new FluxionValue(0);
        return new FluxionValue(false);
    case 3:
        {
            if (uniqueFlag)
                return new FluxionValue(0);
            auto bytePos = static_cast<long>(DecodeVarLong(stream));
            auto byte_current = stream.tellg();
            stream.seekg(bytePos);
            const auto byteValue = stream.get();
            if (byteValue == -1)
                throw FluxionEndOfStreamException();
            stream.seekg(byte_current);
            return new FluxionValue(byteValue);
        }
    case 4:
        {
            if (uniqueFlag)
                return new FluxionValue(0);
            auto signedBytePos = static_cast<long>(DecodeVarLong(stream));
            auto signedByte_current = stream.tellg();
            stream.seekg(signedBytePos);
            const auto signedByte_Value = stream.get();
            if (signedByte_Value == -1)
                throw FluxionEndOfStreamException();
            stream.seekg(signedByte_current);
            return new FluxionValue(static_cast<signed char>(signedByte_Value));
        }
    case 5:
        {
            if (uniqueFlag)
                return new FluxionValue(0);
            auto charPos = static_cast<long>(DecodeVarLong(stream));
            auto char_current = stream.tellg();
            stream.seekg(charPos);
            const auto charValue = new FluxionValue(0);
            auto charShift = 0;

            while (true)
            {
                auto b = stream.get();
                charValue->Value.charValue |= static_cast<char16_t>((b & 0x7F) << charShift);
                charShift += 7;

                if ((b & 0x80) == 0)
                    break;
            }
            stream.seekg(char_current);
            return charValue;
        }
    case 6:
        {
            auto shortPos = static_cast<long>(DecodeVarLong(stream));
            auto short_current = stream.tellg();
            stream.seekg(shortPos);
            const auto shortValue = new FluxionValue(0);
            auto shortShift = 0;

            while (true)
            {
                auto b = static_cast<unsigned char>(stream.get());
                shortValue->Value.shortValue |= static_cast<short>((b & 0x7F) << shortShift);
                shortShift += 7;

                if ((b & 0x80) == 0)
                    break;
            }
            if (uniqueFlag)
                shortValue->Value.shortValue = static_cast<short>(-shortValue->Value.shortValue);
            stream.seekg(short_current);
            return shortValue;
        }
    case 7:
        {
            if (uniqueFlag)
                return new FluxionValue(0);
            auto unsignedShortPos = static_cast<long>(DecodeVarLong(stream));
            auto unsignedShort_current = stream.tellg();
            stream.seekg(unsignedShortPos);
            const auto unsignedShortValue = new FluxionValue(0);
            auto unsignedShortShift = 0;

            while (true)
            {
                auto b = stream.get();
                unsignedShortValue->Value.ushortValue |= static_cast<unsigned short>((b & 0x7F) << unsignedShortShift);
                unsignedShortShift += 7;

                if ((b & 0x80) == 0)
                    break;
            }
            stream.seekg(unsignedShort_current);
            return unsignedShortValue;
        }
    case 8:
        {
            auto intPos = static_cast<long>(DecodeVarLong(stream));
            auto int_current = stream.tellg();
            stream.seekg(intPos);
            const auto intValue = new FluxionValue(0);
            auto intShift = 0;

            while (true)
            {
                auto b = stream.get();
                intValue->Value.intValue |= (b & 0x7F) << intShift;
                intShift += 7;

                if ((b & 0x80) == 0)
                    break;
            }
            if (uniqueFlag)
                intValue->Value.intValue = -intValue->Value.intValue;
            stream.seekg(int_current);
            return intValue;
        }
    case 9:
        {
            if (uniqueFlag)
                return new FluxionValue(0);
            auto uintPos = static_cast<long>(DecodeVarLong(stream));
            auto uint_current = stream.tellg();
            stream.seekg(uintPos);
            const auto uintValue = new FluxionValue(0);
            auto uintShift = 0;

            while (true)
            {
                auto b = stream.get();
                uintValue->Value.uintValue |= static_cast<unsigned int>(b & 0x7F) << uintShift;
                uintShift += 7;

                if ((b & 0x80) == 0)
                    break;
            }
            stream.seekg(uint_current);
            return uintValue;
        }
    case 10:
        {
            auto longPos = static_cast<long>(DecodeVarLong(stream));
            auto long_current = stream.tellg();
            stream.seekg(longPos);
            const auto longValue = new FluxionValue(0);
            auto longShift = 0;

            while (true)
            {
                auto b = stream.get();
                longValue->Value.longValue |= static_cast<long>(b & 0x7F) << longShift;
                longShift += 7;

                if ((b & 0x80) == 0)
                    break;
            }
            if (uniqueFlag)
                longValue->Value.longValue = -longValue->Value.longValue;
            stream.seekg(long_current);
            return longValue;
        }
    case 11:
        {
            if (uniqueFlag)
                return new FluxionValue(0);
            auto unsignedLong_Pos = static_cast<long>(DecodeVarLong(stream));
            auto unsignedLong_current = stream.tellg();
            stream.seekg(unsignedLong_Pos);
            const auto unsignedLongValue = new FluxionValue(0);
            auto unsignedLongShift = 0;

            while (true)
            {
                auto b = stream.get();
                unsignedLongValue->Value.ulongValue |= static_cast<unsigned long>(b & 0x7F) << unsignedLongShift;
                unsignedLongShift += 7;

                if ((b & 0x80) == 0)
                    break;
            }
            stream.seekg(unsignedLong_current);
            return unsignedLongValue;
        }
    case 12:
        {
            if (uniqueFlag)
                return new FluxionValue(0);
            auto floatPos = static_cast<long>(DecodeVarLong(stream));
            auto float_current = stream.tellg();
            stream.seekg(floatPos);
            const auto floatValue = new FluxionValue(0);
            floatValue->ReadValue(stream);
            stream.seekg(float_current);
            return floatValue;
        }
    case 13:
        {
            if (uniqueFlag)
                return new FluxionValue(0);
            auto doublePos = static_cast<long>(DecodeVarLong(stream));
            auto double_current = stream.tellg();
            stream.seekg(doublePos);
            const auto doubleValue = new FluxionValue(0);
            doubleValue->ReadValue(stream);
            stream.seekg(double_current);
            return doubleValue;
        }
    case 14:
        {
            if (uniqueFlag)
                return new FluxionValue("");
            auto stringPos = static_cast<long>(DecodeVarLong(stream));
            auto string_current = stream.tellg();
            stream.seekg(stringPos);
            auto stringValue = new FluxionValue(encoding->bytes_to_string(DecodeByteArrWithVarInt(stream)));
            stream.seekg(string_current);
            return stringValue;
        }
    case 15:
        {
            auto byteArrPos = static_cast<long>(DecodeVarLong(stream));
            auto byteArr_current = stream.tellg();
            stream.seekg(byteArrPos);
            auto byteArrValue = new FluxionValue(DecodeByteArrWithVarInt(stream));
            stream.seekg(byteArr_current);
            return byteArrValue;
        }
    default:
        throw FluxionValueTypeException(valueType);
    }
}

Encoding* Fluxion::GetEncoding(const unsigned char id)
{
    static std::vector<Encoding*> encodings = {
        new UTF8Encoding(),
        new UTF16Encoding(),
    };

    for (const auto& encoding : encodings)
    {
        if (encoding->ID() == id)
            return encoding;
    }
    throw FluxionEncodingException(id);
}

void Fluxion::WriteArrayWithVarInt(std::ostream& stream, const std::vector<unsigned char>& arr)
{
    WriteVarInt(stream, arr.size());
    stream.write(reinterpret_cast<const char*>(arr.data()), static_cast<long int>(arr.size()));
}

void Fluxion::WriteVarInt(std::ostream& stream, unsigned int value)
{
    do
    {
        unsigned char b = value & 0x7F;
        value >>= 7;
        b |= (value > 0 ? 0x80 : 0);
        stream.put(static_cast<char>(b));
    }
    while (value > 0);
}

void Fluxion::WriteVarLong(std::ostream& stream, unsigned long value)
{
    do
    {
        unsigned char b = value & 0x7F;
        value >>= 7;
        b |= (value > 0 ? 0x80 : 0);
        stream.put(static_cast<char>(b));
    }
    while (value > 0);
}

std::vector<unsigned char> Fluxion::DecodeByteArrWithVarInt(std::istream& stream)
{
    uint32_t length = DecodeVarInt(stream);
    std::vector<unsigned char> decoded_data(length);
    stream.read(reinterpret_cast<char*>(decoded_data.data()), length);

    return decoded_data;
}

unsigned int Fluxion::DecodeVarInt(std::istream& stream)
{
    uint32_t length = 0;
    int shift = 0;
    while (true)
    {
        unsigned char byte = stream.get();
        length |= (byte & 0x7F) << shift;
        shift += 7;
        if (!(byte & 0x80))
        {
            break;
        }
    }
    return length;
}

unsigned long Fluxion::DecodeVarLong(std::istream& stream)
{
    uint64_t length = 0;
    int shift = 0;
    while (true)
    {
        unsigned char byte = stream.get();
        length |= (byte & 0x7F) << shift;
        shift += 7;
        if (!(byte & 0x80))
        {
            break;
        }
    }
    return length;
}
