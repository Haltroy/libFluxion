//
// Created by haltroy on 02.05.2024.
//

#include "shared/DataValues.h"
#include "shared/FluxionException.h"

#include <fstream>
#include <cstring>
#include <utility>

FluxionValue& FluxionValue::operator=(const FluxionValue& value)
{
    Type = value.Type;
    switch (Type)
    {
    case Null:
        {
        }
        break;
    case Bool:
        {
            Value.boolValue = value.Value.boolValue;
        }
        break;
    case Byte:
        {
            Value.byteValue = value.Value.byteValue;
        }
        break;
    case SByte:
        {
            Value.sbyteValue = value.Value.sbyteValue;
        }
        break;
    case Char:
        {
            Value.charValue = value.Value.charValue;
        }
        break;
    case Short:
        {
            Value.shortValue = value.Value.shortValue;
        }
        break;
    case UShort:
        {
            Value.ushortValue = value.Value.ushortValue;
        }
        break;
    case Int:
        {
            Value.intValue = value.Value.intValue;
        }
        break;
    case UInt:
        {
            Value.uintValue = value.Value.uintValue;
        }
        break;
    case Long:
        {
            Value.longValue = value.Value.longValue;
        }
        break;
    case ULong:
        {
            Value.ulongValue = value.Value.ulongValue;
        }
        break;
    case Float:
        {
            Value.floatValue = value.Value.floatValue;
        }
        break;
    case Double:
        {
            Value.doubleValue = value.Value.doubleValue;
        }
        break;
    case ByteArray:
        {
            Value.byteArrayValue = value.Value.byteArrayValue;
        }
        break;
    case String:
        {
            Value.stringValue = value.Value.stringValue;
        }
        break;
    }
    return *this;
}

FluxionValue& FluxionValue::operator=(nullptr_t _)
{
    Type = Null;
    return *this;
}

FluxionValue& FluxionValue::operator=(const bool value)
{
    Type = Bool;
    Value.boolValue = value;
    return *this;
}

FluxionValue& FluxionValue::operator=(const char16_t value)
{
    Type = Char;
    Value.charValue = value;
    return *this;
}

FluxionValue& FluxionValue::operator=(const unsigned char value)
{
    Type = Byte;
    Value.byteValue = value;
    return *this;
}

FluxionValue& FluxionValue::operator=(const signed char value)
{
    Type = SByte;
    Value.sbyteValue = value;
    return *this;
}

FluxionValue& FluxionValue::operator=(const unsigned short value)
{
    Type = Byte;
    Value.ushortValue = value;
    return *this;
}

FluxionValue& FluxionValue::operator=(const short value)
{
    Type = SByte;
    Value.shortValue = value;
    return *this;
}

FluxionValue& FluxionValue::operator=(const unsigned int value)
{
    Type = UInt;
    Value.uintValue = value;
    return *this;
}

FluxionValue& FluxionValue::operator=(const int value)
{
    Type = Int;
    Value.intValue = value;
    return *this;
}

FluxionValue& FluxionValue::operator=(const unsigned long value)
{
    Type = ULong;
    Value.ulongValue = value;
    return *this;
}

FluxionValue& FluxionValue::operator=(const long value)
{
    Type = Long;
    Value.longValue = value;
    return *this;
}

FluxionValue& FluxionValue::operator=(const float value)
{
    Type = Float;
    Value.floatValue = value;
    return *this;
}

FluxionValue& FluxionValue::operator=(const double value)
{
    Type = Double;
    Value.doubleValue = value;
    return *this;
}

FluxionValue& FluxionValue::operator=(std::string value)
{
    Type = String;
    Value.stringValue = std::move(value);
    return *this;
}

FluxionValue& FluxionValue::operator=(std::vector<unsigned char> value)
{
    Type = ByteArray;
    Value.byteArrayValue = std::move(value);
    return *this;
}

FluxionValue::FluxionValue(const bool value): Value(new UnionValue(value))
{
    Type = Bool;
}

FluxionValue::FluxionValue(nullptr_t _) : Value(new UnionValue(_))
{
    Type = Null;
}

FluxionValue::FluxionValue(const char16_t value): Value(new UnionValue(value))
{
    Type = Char;
}

FluxionValue::FluxionValue(const unsigned char value): Value(new UnionValue(value))
{
    Type = Byte;
}

FluxionValue::FluxionValue(const signed char value): Value(new UnionValue(value))
{
    Type = SByte;
}

FluxionValue::FluxionValue(const unsigned short value): Value(new UnionValue(value))
{
    Type = UShort;
}

FluxionValue::FluxionValue(const short value) : Value(new UnionValue(value))
{
    Type = Short;
}

FluxionValue::FluxionValue(const unsigned int value) : Value(new UnionValue(value))
{
    Type = UInt;
}

FluxionValue::FluxionValue(const int value): Value(new UnionValue(value))
{
    Type = Int;
}

FluxionValue::FluxionValue(const unsigned long value): Value(new UnionValue(value))
{
    Type = ULong;
}

FluxionValue::FluxionValue(const long value): Value(new UnionValue(value))
{
    Type = Long;
}

FluxionValue::FluxionValue(const float value): Value(new UnionValue(value))
{
    Type = Float;
}

FluxionValue::FluxionValue(const double value): Value(new UnionValue(value))
{
    Type = Double;
}

FluxionValue::FluxionValue(std::string value): Value(new UnionValue(std::move(value)))
{
    Type = String;
}

FluxionValue::FluxionValue(std::vector<unsigned char> value) : Value(new UnionValue(std::move(value)))
{
    Type = ByteArray;
}

int FluxionValue::ValueTypeIndex(int version) const
{
    switch (version)
    {
    default:
    case 1:
        {
            switch (Type)
            {
            default:
            case Null:
                {
                    return 0;
                }
                break;
            case Bool:
                {
                    return Value.boolValue ? 1 : 2;
                }
                break;
            case Byte:
                {
                    return 3;
                }
                break;
            case SByte:
                {
                    return 4;
                }
                break;
            case Char:
                {
                    return 5;
                }
                break;
            case Short:
                {
                    return 6;
                }
                break;
            case UShort:
                {
                    return 7;
                }
                break;
            case Int:
                {
                    return 8;
                }
                break;
            case UInt:
                {
                    return 9;
                }
                break;
            case Long:
                {
                    return 10;
                }
                break;
            case ULong:
                {
                    return 11;
                }
                break;
            case Float:
                {
                    return 12;
                }
                break;
            case Double:
                {
                    return 13;
                }
                break;
            case ByteArray:
                {
                    return 14;
                }
                break;
            case String:
                {
                    return 15;
                }
                break;
            }
        }
        break;
    case 2:
        {
            switch (Type)
            {
            default:
            case Null:
                {
                    return 0;
                }
                break;
            case Bool:
                {
                    return Value.boolValue ? 1 : 2;
                }
                break;
            case Byte:
                {
                    return 3;
                }
                break;
            case SByte:
                {
                    return 4;
                }
                break;
            case Char:
                {
                    return 5;
                }
                break;
            case Short:
                {
                    return Value.shortValue == 0 ? 0 : 6;
                }
                break;
            case UShort:
                {
                    return 7;
                }
                break;
            case Int:
                {
                    return Value.intValue == 0 ? 1 : 8;
                }
                break;
            case UInt:
                {
                    return 9;
                }
                break;
            case Long:
                {
                    return Value.longValue == 0 ? 2 : 10;
                }
                break;
            case ULong:
                {
                    return 11;
                }
                break;
            case Float:
                {
                    return 12;
                }
                break;
            case Double:
                {
                    return 13;
                }
                break;
            case ByteArray:
                {
                    return 14;
                }
                break;
            case String:
                {
                    return 15;
                }
                break;
            }
        }
        break;
    }
}


std::vector<unsigned char> FluxionValue::GetBytes(const Encoding* encoding) const
{
    switch (Type)
    {
    default:
    case Bool:
    case Null:
        {
            return {};
        }
        break;
    case Byte:
        {
            return {Value.byteValue};
        }
        break;
    case SByte:
        {
            return {static_cast<unsigned char>(Value.sbyteValue)};
        }
        break;
    case Char:
        {
            std::vector<unsigned char> utf16_bytes;
            if (Value.charValue <= 0xFFFF)
            {
                utf16_bytes.push_back(static_cast<unsigned char>(Value.charValue & 0xFF));
                utf16_bytes.push_back(static_cast<unsigned char>((Value.charValue >> 8) & 0xFF));
            }
            else
            {
                const char16_t high_surrogate = 0xD800 + ((Value.charValue - 0x10000) >> 10);
                const char16_t low_surrogate = 0xDC00 + ((Value.charValue - 0x10000) & 0x3FF);
                utf16_bytes.push_back(static_cast<unsigned char>(high_surrogate & 0xFF));
                utf16_bytes.push_back(static_cast<unsigned char>((high_surrogate >> 8) & 0xFF));
                utf16_bytes.push_back(static_cast<unsigned char>(low_surrogate & 0xFF));
                utf16_bytes.push_back(static_cast<unsigned char>((low_surrogate >> 8) & 0xFF));
            }

            return utf16_bytes;
        }
        break;
    case Short:
        {
            std::vector<unsigned char> bytes(sizeof(short));
            bytes[0] = static_cast<unsigned char>(Value.shortValue & 0xFF);
            bytes[1] = static_cast<unsigned char>((Value.shortValue >> 8) & 0xFF);
            return bytes;
        }
        break;
    case UShort:
        {
            std::vector<unsigned char> bytes(sizeof(ushort));
            // Little-endian: least significant byte first
            bytes[0] = static_cast<unsigned char>(Value.ushortValue & 0xFF);
            bytes[1] = static_cast<unsigned char>((Value.ushortValue >> 8) & 0xFF);
            return bytes;
        }
        break;
    case Int:
        {
            std::vector<unsigned char> bytes(sizeof(int));
            auto intValue = Value.intValue;
            for (int i = 0; i < sizeof(int); ++i)
            {
                bytes[i] = static_cast<unsigned char>(intValue & 0xFF);
                intValue >>= 8;
            }
            return bytes;
        }
        break;
    case UInt:
        {
            std::vector<unsigned char> bytes(sizeof(unsigned int));
            auto uintValue = Value.uintValue;
            for (int i = 0; i < sizeof(unsigned int); ++i)
            {
                bytes[i] = static_cast<unsigned char>(uintValue & 0xFF);
                uintValue >>= 8;
            }
            return bytes;
        }
        break;
    case Long:
        {
            std::vector<unsigned char> bytes(sizeof(long));
            auto longValue = Value.longValue;
            for (int i = 0; i < sizeof(long); ++i)
            {
                bytes[i] = static_cast<unsigned char>(longValue & 0xFF);
                longValue >>= 8;
            }
            return bytes;
        }
        break;
    case ULong:
        {
            std::vector<unsigned char> bytes(sizeof(unsigned long));
            auto ulongValue = Value.ulongValue;
            for (int i = 0; i < sizeof(unsigned long); ++i)
            {
                bytes[i] = static_cast<unsigned char>(ulongValue & 0xFF);
                ulongValue >>= 8;
            }
            return bytes;
        }
        break;
    case Float:
        {
            union
            {
                float f;
                unsigned int i;
            } conv{};
            conv.f = Value.floatValue;
            std::vector<unsigned char> bytes(sizeof(unsigned int));
            for (int i = 0; i < sizeof(unsigned int); ++i)
            {
                bytes[i] = static_cast<unsigned char>(conv.i & 0xFF);
                conv.i >>= 8;
            }
            return bytes;
        }
        break;
    case Double:
        {
            union
            {
                double d;
                unsigned long long i;
            } conv{};
            conv.d = Value.doubleValue;
            std::vector<unsigned char> bytes(sizeof(unsigned long long));
            for (int i = 0; i < sizeof(unsigned long long); ++i)
            {
                bytes[i] = static_cast<unsigned char>(conv.i & 0xFF);
                conv.i >>= 8;
            }
            return bytes;
        }
        break;
    case ByteArray:
        {
            return Value.byteArrayValue;
        }
        break;
    case String:
        {
            return encoding->string_to_bytes(Value.stringValue);
        }
        break;
    }
}

bool FluxionValue::IsEmpty() const
{
    switch (Type)
    {
    default:
    case Bool:
    case Null:
        {
            return true;
        }
        break;
    case Byte:
        {
            return Value.byteValue == 0;
        }
        break;
    case SByte:
        {
            return Value.sbyteValue == 0;
        }
        break;
    case Char:
        {
            return Value.charValue == 0;
        }
        break;
    case Short:
        {
            return Value.shortValue == 0;
        }
        break;
    case UShort:
        {
            return Value.ushortValue == 0;
        }
        break;
    case Int:
        {
            return Value.intValue == 0;
        }
        break;
    case UInt:
        {
            return Value.uintValue == 0;
        }
        break;
    case Long:
        {
            return Value.longValue == 0;
        }
        break;
    case ULong:
        {
            return Value.ulongValue == 0;
        }
        break;
    case Float:
        {
            return Value.floatValue == 0;
        }
        break;
    case Double:
        {
            return Value.doubleValue == 0;
        }
        break;
    case ByteArray:
        {
            return Value.byteArrayValue.empty();
        }
        break;
    case String:
        {
            return Value.stringValue.empty();
        }
        break;
    }
}

bool FluxionValue::UniqueFlagSet() const
{
    switch (Type)
    {
    default:
    case Bool:
    case Null:
        {
            return false;
        }
        break;
    case Byte:
        {
            return Value.byteValue == 0;
        }
        break;
    case SByte:
        {
            return Value.sbyteValue <= 0;
        }
        break;
    case Char:
        {
            return Value.charValue == 0;
        }
        break;
    case Short:
        {
            return Value.shortValue <= 0;
        }
        break;
    case UShort:
        {
            return Value.ushortValue == 0;
        }
        break;
    case Int:
        {
            return Value.intValue <= 0;
        }
        break;
    case UInt:
        {
            return Value.uintValue == 0;
        }
        break;
    case Long:
        {
            return Value.longValue <= 0;
        }
        break;
    case ULong:
        {
            return Value.ulongValue == 0;
        }
        break;
    case Float:
        {
            return Value.floatValue == 0;
        }
        break;
    case Double:
        {
            return Value.doubleValue == 0;
        }
        break;
    case ByteArray:
        {
            return Value.byteArrayValue.empty();
        }
        break;
    case String:
        {
            return Value.stringValue.empty();
        }
        break;
    }
}

int FluxionValue::EstimateSize(const Encoding* encoding) const
{
    switch (Type)
    {
    default:
    case Bool:
    case Null:
        {
            return 0;
        }
        break;
    case Byte:
    case SByte:
        {
            return 1;
        }
        break;
    case Char:
        {
            int bytes = 1;
            auto charValue = Value.charValue;
            while ((charValue >>= 7) != 0)
                bytes++;
            return bytes;
        }
        break;
    case Short:
        {
            int bytes = 1;
            auto shortValue = Value.shortValue;
            if (shortValue < 0)
            {
                shortValue = static_cast<short>(~shortValue);
                shortValue++;
            }

            while ((shortValue >>= 7) != 0)
                bytes++;
            return bytes;
        }
        break;
    case UShort:
        {
            int bytes = 1;
            auto unsignedShortValue = Value.ushortValue;
            while ((unsignedShortValue >>= 7) != 0)
                bytes++;
            return bytes;
        }
        break;
    case Int:
        {
            int bytes = 1;
            auto intValue = Value.intValue;
            if (intValue < 0)
            {
                intValue = ~intValue;
                intValue++;
            }

            while ((intValue >>= 7) != 0)
                bytes++;
            return bytes;
        }
        break;
    case UInt:
        {
            int bytes = 1;
            auto uintValue = Value.uintValue;
            while ((uintValue >>= 7) != 0)
                bytes++;
            return bytes;
        }
        break;
    case Long:
        {
            int bytes = 1;
            auto longValue = Value.longValue;
            if (longValue < 0)
            {
                longValue = ~longValue;
                longValue++;
            }

            while ((longValue >>= 7) != 0)
                bytes++;
            return bytes;
        }
        break;
    case ULong:
        {
            int bytes = 1;
            auto value = Value.ulongValue;
            while ((value >>= 7) != 0)
                bytes++;
            return bytes;
        }
        break;
    case Float:
        {
            return 4;
        }
        break;
    case Double:
        {
            return 8;
        }
        break;
    case ByteArray:
        {
            int bytes = 1;
            auto intValue = Value.byteArrayValue.size();
            while ((intValue >>= 7) != 0)
                bytes++;
            return bytes + static_cast<int>(Value.byteArrayValue.size());
        }
        break;
    case String:
        {
            auto encoded = encoding->string_to_bytes(Value.stringValue);
            int bytes = 1;
            auto intValue = encoded.size();

            while ((intValue >>= 7) != 0)
                bytes++;
            return bytes + static_cast<int>(encoded.size());
        }
        break;
    }
}

void FluxionValue::WriteValueV2(std::ostream* os, const Encoding* encoding) const
{
    switch (Type)
    {
    default:
    case Null:
    case Bool:
        break;
    case Byte:
        {
            os->put(static_cast<char>(Value.byteValue));
        }
        break;
    case SByte:
        {
            os->put(static_cast<char>(Value.sbyteValue));
        }
        break;
    case Char:
        {
            auto value = Value.charValue;
            while (true)
            {
                auto b = static_cast<char>(value & 0x7F);
                value >>= 7;

                if (value == 0)
                {
                    os->put(b);
                    break;
                }

                os->put(static_cast<char>(b | 0x80));
            }
        }
        break;
    case Short:
        {
            auto value = Value.shortValue;
            if (value < 0) value = static_cast<short>(-value);
            while (true)
            {
                auto b = static_cast<char>(value & 0x7F);
                value >>= 7;

                if (value == 0)
                {
                    os->put(b);
                    break;
                }

                os->put(static_cast<char>(b | 0x80));
            }
        }
        break;
    case UShort:
        {
            auto value = Value.ushortValue;
            while (true)
            {
                auto b = static_cast<char>(value & 0x7F);
                value >>= 7;

                if (value == 0)
                {
                    os->put(b);
                    break;
                }

                os->put(static_cast<char>(b | 0x80));
            }
        }
        break;
    case Int:
        {
            auto value = Value.intValue;
            if (value < 0) value = -value;
            while (true)
            {
                auto b = static_cast<char>(value & 0x7F);
                value >>= 7;

                if (value == 0)
                {
                    os->put(b);
                    break;
                }

                os->put(static_cast<char>(b | 0x80));
            }
        }
        break;
    case UInt:
        {
            auto value = Value.ulongValue;
            while (true)
            {
                auto b = static_cast<char>(value & 0x7F);
                value >>= 7;

                if (value == 0)
                {
                    os->put(b);
                    break;
                }

                os->put(static_cast<char>(b | 0x80));
            }
        }
        break;
    case Long:
        {
            auto value = Value.longValue;
            if (value < 0) value = -value;
            while (true)
            {
                auto b = static_cast<char>(value & 0x7F);
                value >>= 7;

                if (value == 0)
                {
                    os->put(b);
                    break;
                }

                os->put(static_cast<char>(b | 0x80));
            }
        }
        break;
    case ULong:
        {
            auto value = Value.ulongValue;
            while (true)
            {
                auto b = static_cast<char>(value & 0x7F);
                value >>= 7;

                if (value == 0)
                {
                    os->put(b);
                    break;
                }

                os->put(static_cast<char>(b | 0x80));
            }
        }
        break;
    case Float:
        {
            auto bytes = GetBytes(encoding);
            os->write(reinterpret_cast<const char*>(bytes.data()), static_cast<long int>(bytes.size()));
        }
        break;
    case Double:
        {
            auto bytes = GetBytes(encoding);
            os->write(reinterpret_cast<const char*>(bytes.data()), static_cast<long int>(bytes.size()));
        }
        break;
    case ByteArray:
        {
            auto valueSize = Value.byteArrayValue.size();
            do
            {
                unsigned char b = valueSize & 0x7F;
                valueSize >>= 7;
                b |= (valueSize > 0 ? 0x80 : 0);
                os->put(static_cast<char>(b));
            }
            while (valueSize > 0);
            os->write(reinterpret_cast<const char*>(Value.byteArrayValue.data()),
                      static_cast<long int>(Value.byteArrayValue.size()));
        }
        break;
    case String:
        {
            auto value = encoding->string_to_bytes(Value.stringValue);
            auto valueSize = value.size();
            do
            {
                unsigned char b = valueSize & 0x7F;
                valueSize >>= 7;
                b |= (valueSize > 0 ? 0x80 : 0);
                os->put(static_cast<char>(b));
            }
            while (valueSize > 0);
            os->write(reinterpret_cast<const char*>(value.data()), static_cast<long int>(value.size()));
        }
        break;
    }
}

void FluxionValue::ReadValue(std::istream& stream)
{
    switch (Type)
    {
    default:
    case Null:
    case Bool:
        {
        }
        break;
    case Byte:
        {
        }
        break;
    case SByte:
        break;
    case Char:
        {
            unsigned char byte1 = 0, byte2 = 0;
            stream >> byte1 >> byte2;

            if (byte1 <= 0x7F)
            {
                Type = Char;
                Value.charValue = byte1;
            }
            if (byte1 <= 0xDF)
            {
                Type = Char;
                Value.charValue = (byte1 - 0xD800) << 10 | ((byte2 & 0x3F) << 6);
            }
            if (byte1 <= 0xBF)
            {
                Type = Char;
                Value.charValue = 0x10000 + ((byte1 & 0x3F) << 10) | ((byte2 & 0x3F) << 6);
            }
            Type = Char;
            Value.charValue = 0;
        }
        break;
    case Short:
        {
            // Using ">>" does not work for some reason so we are going to read it by hand.
            short value;
            char bytes[sizeof(short)];
            for (char& byte : bytes)
            {
                const auto readByte = stream.get();
                if (readByte == -1)
                    throw FluxionEndOfStreamException();
                byte = static_cast<char>(readByte);
            }
            memcpy(&value, bytes, sizeof(short));
            Type = Short;
            Value.shortValue = value;
        }
        break;
    case UShort:
        {
            // Using ">>" does not work for some reason so we are going to read it by hand.
            unsigned short value;
            char bytes[sizeof(unsigned short)];
            for (char& byte : bytes)
            {
                const auto readByte = stream.get();
                if (readByte == -1)
                    throw FluxionEndOfStreamException();
                byte = static_cast<char>(readByte);
            }
            memcpy(&value, bytes, sizeof(unsigned short));
            Type = UShort;
            Value.ushortValue = value;
        }
        break;
    case Int:
        {
            // Using ">>" does not work for some reason so we are going to read it by hand.
            int value;
            char bytes[sizeof(int)];
            for (char& byte : bytes)
            {
                const auto readByte = stream.get();
                if (readByte == -1)
                    throw FluxionEndOfStreamException();
                byte = static_cast<char>(readByte);
            }
            memcpy(&value, bytes, sizeof(int));
            Type = Int;
            Value.intValue = value;
        }
        break;
    case UInt:
        {
            // Using ">>" does not work for some reason so we are going to read it by hand.
            unsigned int value;
            char bytes[sizeof(unsigned int)];
            for (char& byte : bytes)
            {
                const auto readByte = stream.get();
                if (readByte == -1)
                    throw FluxionEndOfStreamException();
                byte = static_cast<char>(readByte);
            }
            memcpy(&value, bytes, sizeof(unsigned int));
            Type = UInt;
            Value.uintValue = value;
        }
        break;
    case Long:
        {
            // Using ">>" does not work for some reason so we are going to read it by hand.
            long value;
            char bytes[sizeof(long)];
            for (char& byte : bytes)
            {
                const auto readByte = stream.get();
                if (readByte == -1)
                    throw FluxionEndOfStreamException();
                byte = static_cast<char>(readByte);
            }
            memcpy(&value, bytes, sizeof(long));
            Type = Long;
            Value.longValue = value;
        }
        break;
    case ULong:
        {
            // Using ">>" does not work for some reason so we are going to read it by hand.
            unsigned long value;
            char bytes[sizeof(unsigned long)];
            for (char& byte : bytes)
            {
                const auto readByte = stream.get();
                if (readByte == -1)
                    throw FluxionEndOfStreamException();
                byte = static_cast<char>(readByte);
            }
            memcpy(&value, bytes, sizeof(unsigned long));
            Type = UInt;
            Value.ulongValue = value;
        }
        break;
    case Float:
        {
            // Using ">>" does not work for some reason so we are going to read it by hand.
            float value;
            char bytes[sizeof(float)];
            for (char& byte : bytes)
            {
                const auto readByte = stream.get();
                if (readByte == -1)
                    throw FluxionEndOfStreamException();
                byte = static_cast<char>(readByte);
            }
            memcpy(&value, bytes, sizeof(float));
            Type = Float;
            Value.floatValue = value;
        }
        break;
    case Double:
        {
            // Using ">>" does not work for some reason so we are going to read it by hand.
            double value;
            char bytes[sizeof(double)];
            for (char& byte : bytes)
            {
                const auto readByte = stream.get();
                if (readByte == -1)
                    throw FluxionEndOfStreamException();
                byte = static_cast<char>(readByte);
            }
            memcpy(&value, bytes, sizeof(double));
            Type = Double;
            Value.doubleValue = value;
        }
        break;
    case ByteArray:
        break;
    case String:
        break;
    }
}

bool FluxionValue::operator==(const bool other) const
{
    if (Type != Bool) return false;
    return Value.boolValue == other;
}

bool FluxionValue::operator==(const std::vector<unsigned char>& other) const
{
    if (Type != ByteArray) return false;
    if (other.size() != Value.byteArrayValue.size()) return false;

    for (int i = 0; i < Value.byteArrayValue.size(); i++)
    {
        if (other[i] != Value.byteArrayValue[i]) return false;
    }
    return true;
}

bool FluxionValue::operator==(const std::string& other) const
{
    if (Type != String) return false;
    return other == Value.stringValue;
}

bool FluxionValue::operator==(const char16_t other) const
{
    if (Type != Char) return false;
    return other == Value.charValue;
}

bool FluxionValue::operator==(double other) const
{
    if (Type != Double) return false;
    return other == Value.doubleValue;
}

bool FluxionValue::operator==(float other) const
{
    if (Type != Float) return false;
    return other == Value.floatValue;
}

bool FluxionValue::operator==(int other) const
{
    if (Type != Int) return false;
    return other == Value.intValue;
}

bool FluxionValue::operator==(unsigned int other) const
{
    if (Type != UInt) return false;
    return other == Value.uintValue;
}

bool FluxionValue::operator==(long other) const
{
    if (Type != Long) return false;
    return other == Value.longValue;
}

bool FluxionValue::operator==(unsigned long other) const
{
    if (Type != ULong) return false;
    return other == Value.ulongValue;
}

bool FluxionValue::operator==(nullptr_t other) const
{
    return Type == Null;
}

bool FluxionValue::operator==(short other) const
{
    if (Type != Short) return false;
    return other == Value.shortValue;
}

bool FluxionValue::operator==(signed char other) const
{
    if (Type != SByte) return false;
    return other == Value.sbyteValue;
}

bool FluxionValue::operator==(unsigned char other) const
{
    if (Type != Byte) return false;
    return other == Value.byteValue;
}

bool FluxionValue::operator==(unsigned short other) const
{
    if (Type != UShort) return false;
    return other == Value.ushortValue;
}

bool FluxionValue::operator==(const FluxionValue& other) const
{
    if (Type != other.Type) return false;
    switch (other.Type)
    {
    default:
    case Null:
        {
            return true;
        }
        break;
    case Bool:
        {
            return Value.boolValue == other.Value.boolValue;
        }
        break;
    case Byte:
        {
            return Value.byteValue == other.Value.byteValue;
        }
        break;
    case SByte:
        {
            return Value.sbyteValue == other.Value.sbyteValue;
        }
        break;
    case Char:
        {
            return Value.charValue == other.Value.charValue;
        }
        break;
    case Short:
        {
            return Value.shortValue == other.Value.shortValue;
        }
        break;
    case UShort:
        {
            return Value.ushortValue == other.Value.ushortValue;
        }
        break;
    case Int:
        {
            return Value.intValue == other.Value.intValue;
        }
        break;
    case UInt:
        {
            return Value.uintValue == other.Value.uintValue;
        }
        break;
    case Long:
        {
            return Value.longValue == other.Value.longValue;
        }
        break;
    case ULong:
        {
            return Value.ulongValue == other.Value.ulongValue;
        }
        break;
    case Float:
        {
            return Value.floatValue == other.Value.floatValue;
        }
        break;
    case Double:
        {
            return Value.doubleValue == other.Value.doubleValue;
        }
        break;
    case ByteArray:
        {
            if (other.Value.byteArrayValue.size() != Value.byteArrayValue.size()) return false;

            for (int i = 0; i < Value.byteArrayValue.size(); i++)
            {
                if (other.Value.byteArrayValue[i] != Value.byteArrayValue[i]) return false;
            }
            return true;
        }
        break;
    case String:
        {
            return Value.stringValue == other.Value.stringValue;
        }
        break;
    }
}


