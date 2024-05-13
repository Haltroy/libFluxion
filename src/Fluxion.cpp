#include "shared/Fluxion.h"

#include <cstdint>
#include <fstream>
#include <string.h>

void Fluxion::Write(FluxionNode *node, std::ostream *stream, const Encoding *encoding, const bool asRoot)
{
    if (asRoot)
    {
        node->IsRoot = true;
        stream->put(0x46);
        stream->put(0x4C);
        stream->put(0x58);
        stream->put(static_cast<char>(node->getVersion()));
        stream->put(static_cast<char>(encoding->ID()));
    }

    const auto children = node->GetChildren();

    auto valueType = node->Value->ValueTypeIndex();
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

    const auto *stringDerive = dynamic_cast<StringValue *>(node->Value);
    const auto *byteArrDerive = dynamic_cast<ByteArrayValue *>(node->Value);
    if (stringDerive)
    {
        WriteArrayWithVarInt(*stream, encoding->string_to_bytes(stringDerive->Value));
    }
    else if (byteArrDerive)
    {
        WriteArrayWithVarInt(*stream, byteArrDerive->Value);
    }
    else
    {
        const auto bytes = node->Value->GetBytes();
        const auto *charData = reinterpret_cast<const std::ostream::char_type *>(bytes.data());
        const size_t dataSize = bytes.size();
        stream->write(charData, static_cast<long>(dataSize));
    }

    if (!node->Attributes.empty())
    {
        WriteVarInt(*stream, node->Attributes.size());

        for (const auto attribute : node->Attributes)
        {
            auto attr_valueType = attribute->Value->ValueTypeIndex();
            if (!attribute->Name.empty())
                attr_valueType = attr_valueType ^ 16;
            stream->put(static_cast<char>(attr_valueType));

            if (!attribute->Name.empty())
            {
                WriteArrayWithVarInt(*stream, encoding->string_to_bytes(attribute->Name));
            }

            const auto *attr_stringDerive = dynamic_cast<StringValue *>(attribute->Value);
            const auto *attr_byteArrDerive = dynamic_cast<ByteArrayValue *>(attribute->Value);
            if (attr_stringDerive)
            {
                WriteArrayWithVarInt(*stream, encoding->string_to_bytes(attr_stringDerive->Value));
            }
            else if (attr_byteArrDerive)
            {
                WriteArrayWithVarInt(*stream, attr_byteArrDerive->Value);
            }
            else
            {
                const auto bytes = attribute->Value->GetBytes();
                const auto *charData = reinterpret_cast<const std::ostream::char_type *>(bytes.data());
                const size_t dataSize = bytes.size();
                stream->write(charData, static_cast<long>(dataSize));
            }
        }
    }

    if (!children.empty())
        for (const auto sub_node : children)
            Write(&*sub_node, stream, encoding, false);
}

FluxionNode *Fluxion::Read(std::istream &stream)
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
    if (versionByte > root->getVersion())
        throw FluxionUnsupportedVersionException(static_cast<unsigned char>(versionByte));

    const auto encodingByte = stream.get();
    if (encodingByte == -1)
        throw FluxionEndOfStreamException();
    const Encoding *encoding = GetEncoding(encodingByte);
    root->setVersion(versionByte);

    root = ReadRecurse(stream, encoding, root, true);

    return root;
}

FluxionNode *Fluxion::ReadRecurse(std::istream &stream, const Encoding *encoding, FluxionNode *root, bool readRoot)
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

    int children_count;
    if (!noChild)
    {
        children_count = DecodeVarInt(stream);
        if (children_count == -1)
            throw FluxionEndOfStreamException();
    }

    if (hasName)
    {
        node->Name = encoding->bytes_to_string(DecodeByteArrWithVarInt(stream));
    }

    node->Value = ReadBytesFromType(stream, valueType, encoding);

    if (!noAttr)
    {
        int attributes_count = DecodeVarInt(stream);
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

            attr->Value = ReadBytesFromType(stream, attr_valueType, encoding);

            node->Attributes.insert(node->Attributes.end(), attr);
        }
    }

    if (!noChild)
        for (auto i = 0; i < children_count; i++)
            node->Add(ReadRecurse(stream, encoding, node, false));

    return node;
}

void Fluxion::Write(FluxionNode *node, const std::string &fileName, const Encoding *encoding)
{
    encoding = encoding == nullptr ? new UTF8Encoding : encoding;
    std::ofstream stream(fileName, std::ios::binary | std::ios::out | std::ios::trunc);

    if (!stream.is_open())
    {
        throw std::runtime_error("Failed to create or open file \"" + fileName + "\".");
    }

    Write(node, &stream, encoding, true);
}

FluxionNode *Fluxion::Read(const std::string &fileName)
{
    std::ifstream fs(fileName, std::ios::binary | std::ios::in);
    if (!fs.is_open())
    {
        throw std::runtime_error("Failed to open file \"" + fileName + "\".");
    }
    return Read(fs);
}

DataValues *Fluxion::ReadBytesFromType(std::istream &stream, const unsigned char valueType, const Encoding *encoding)
{
    switch (valueType)
    {
    case 0:
        return new NullValue;
    case 1:
        return new BoolValue(true);
    case 2:
        return new BoolValue(false);
    case 3:
    {
        const auto byteValue = stream.get();
        if (byteValue == -1)
            throw FluxionEndOfStreamException();
        return new ByteValue(byteValue);
    }
    case 4:
    {
        const auto sbyteValue = stream.get();
        if (sbyteValue == -1)
            throw FluxionEndOfStreamException();
        return new SByteValue(static_cast<signed char>(sbyteValue));
    }
    case 5:
    {
        const auto charValue = new CharValue(0);
        charValue->Value = CharValue::ReadValue(stream);
        return charValue;
    }
    case 6:
    {
        const auto shortValue = new ShortValue(0);
        shortValue->Value = ShortValue::ReadValue(stream);
        return shortValue;
    }
    case 7:
    {
        const auto ushortValue = new UShortValue(0);
        ushortValue->Value = UShortValue::ReadValue(stream);
        return ushortValue;
    }
    case 8:
    {
        const auto intValue = new IntValue(0);
        intValue->Value = IntValue::ReadValue(stream);
        return intValue;
    }
    case 9:
    {
        const auto uintValue = new UIntValue(0);
        uintValue->Value = UIntValue::ReadValue(stream);
        return uintValue;
    }
    case 10:
    {
        const auto longValue = new LongValue(0);
        longValue->Value = LongValue::ReadValue(stream);
        return longValue;
    }
    case 11:
    {
        const auto ulongValue = new ULongValue(0);
        ulongValue->Value = ULongValue::ReadValue(stream);
        return ulongValue;
    }
    case 12:
    {
        const auto floatValue = new FloatValue(0);
        floatValue->Value = FloatValue::ReadValue(stream);
        return floatValue;
    }
    case 13:
    {
        const auto doubleValue = new DoubleValue(0);
        doubleValue->Value = DoubleValue::ReadValue(stream);
        return doubleValue;
    }
    case 14:
        return new StringValue(encoding->bytes_to_string(DecodeByteArrWithVarInt(stream)));
    case 15:
        return new ByteArrayValue(DecodeByteArrWithVarInt(stream));
    default:
        throw FluxionValueTypeException(valueType);
    }
}

Encoding *Fluxion::GetEncoding(const unsigned char id)
{
    static std::vector<Encoding *> encodings = {
        new UTF8Encoding(),
        new UTF16Encoding(),
        new UTF32Encoding(),
    };

    for (const auto &encoding : encodings)
    {
        if (encoding->ID() == id)
            return encoding;
    }
    throw FluxionEncodingException(id);
}

void Fluxion::WriteArrayWithVarInt(std::ostream &stream, const std::vector<unsigned char> &arr)
{
    WriteVarInt(stream, arr.size());
    stream.write(reinterpret_cast<const char *>(arr.data()), static_cast<long int>(arr.size()));
}

void Fluxion::WriteVarInt(std::ostream &stream, unsigned int value)
{
    do
    {
        unsigned char b = value & 0x7F;
        value >>= 7;
        b |= (value > 0 ? 0x80 : 0);
        stream.put(static_cast<char>(b));
    } while (value > 0);
}

std::vector<unsigned char> Fluxion::DecodeByteArrWithVarInt(std::istream &stream)
{
    uint32_t length = DecodeVarInt(stream);
    std::vector<unsigned char> decoded_data(length);
    stream.read(reinterpret_cast<char *>(decoded_data.data()), length);

    return decoded_data;
}

unsigned int Fluxion::DecodeVarInt(std::istream &stream)
{
    uint32_t length = 0;
    int shift = 0;
    uint8_t byte;
    while (true)
    {
        byte = stream.get();
        length |= (byte & 0x7F) << shift;
        shift += 7;
        if (!(byte & 0x80))
        {
            break;
        }
    }
    return length;
}
