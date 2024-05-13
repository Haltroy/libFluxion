//
// Created by haltroy on 02.05.2024.
//

#include "shared/DataValues.h"
#include "shared/FluxionException.h"

#include <fstream>
#include <string.h>

std::vector<unsigned char> DoubleValue::GetBytes()
{
    union
    {
        double d;
        unsigned long long i;
    } conv{};
    conv.d = Value;
    std::vector<unsigned char> bytes(sizeof(unsigned long long));
    for (int i = 0; i < sizeof(unsigned long long); ++i)
    {
        bytes[i] = static_cast<unsigned char>(conv.i & 0xFF);
        conv.i >>= 8;
    }
    return bytes;
}

double DoubleValue::ReadValue(std::istream &stream)
{
    // Using ">>" does not work for some reason so we are going to read it by hand.
    double value;
    char bytes[sizeof(double)];
    for (int i = 0; i < sizeof(double); i++)
    {
        const auto readByte = stream.get();
        if (readByte == -1)
            throw FluxionEndOfStreamException();
        bytes[i] = static_cast<char>(readByte);
    }
    memcpy(&value, bytes, sizeof(double));
    return value;
}

std::vector<unsigned char> FloatValue::GetBytes()
{
    union
    {
        float f;
        unsigned int i;
    } conv{};
    conv.f = Value;
    std::vector<unsigned char> bytes(sizeof(unsigned int));
    for (int i = 0; i < sizeof(unsigned int); ++i)
    {
        bytes[i] = static_cast<unsigned char>(conv.i & 0xFF);
        conv.i >>= 8;
    }
    return bytes;
}

float FloatValue::ReadValue(std::istream &stream)
{
    // Using ">>" does not work for some reason so we are going to read it by hand.
    float value;
    char bytes[sizeof(float)];
    for (int i = 0; i < sizeof(float); i++)
    {
        const auto readByte = stream.get();
        if (readByte == -1)
            throw FluxionEndOfStreamException();
        bytes[i] = static_cast<char>(readByte);
    }
    memcpy(&value, bytes, sizeof(float));
    return value;
}

std::vector<unsigned char> ULongValue::GetBytes()
{
    std::vector<unsigned char> bytes(sizeof(unsigned long));
    for (int i = 0; i < sizeof(unsigned long); ++i)
    {
        bytes[i] = static_cast<unsigned char>(Value & 0xFF);
        Value >>= 8;
    }
    return bytes;
}

unsigned long ULongValue::ReadValue(std::istream &stream)
{
    // Using ">>" does not work for some reason so we are going to read it by hand.
    unsigned long value;
    char bytes[sizeof(unsigned long)];
    for (int i = 0; i < sizeof(unsigned long); i++)
    {
        const auto readByte = stream.get();
        if (readByte == -1)
            throw FluxionEndOfStreamException();
        bytes[i] = static_cast<char>(readByte);
    }
    memcpy(&value, bytes, sizeof(unsigned long));
    return value;
}

std::vector<unsigned char> LongValue::GetBytes()
{
    std::vector<unsigned char> bytes(sizeof(long));
    for (int i = 0; i < sizeof(long); ++i)
    {
        bytes[i] = static_cast<unsigned char>(Value & 0xFF);
        Value >>= 8;
    }
    return bytes;
}

long LongValue::ReadValue(std::istream &stream)
{
    // Using ">>" does not work for some reason so we are going to read it by hand.
    long value;
    char bytes[sizeof(long)];
    for (int i = 0; i < sizeof(long); i++)
    {
        const auto readByte = stream.get();
        if (readByte == -1)
            throw FluxionEndOfStreamException();
        bytes[i] = static_cast<char>(readByte);
    }
    memcpy(&value, bytes, sizeof(long));
    return value;
}

std::vector<unsigned char> UIntValue::GetBytes()
{
    std::vector<unsigned char> bytes(sizeof(unsigned int));
    for (int i = 0; i < sizeof(unsigned int); ++i)
    {
        bytes[i] = static_cast<unsigned char>(Value & 0xFF);
        Value >>= 8;
    }
    return bytes;
}

unsigned int UIntValue::ReadValue(std::istream &stream)
{
    // Using ">>" does not work for some reason so we are going to read it by hand.
    unsigned int value;
    char bytes[sizeof(unsigned int)];
    for (int i = 0; i < sizeof(unsigned int); i++)
    {
        const auto readByte = stream.get();
        if (readByte == -1)
            throw FluxionEndOfStreamException();
        bytes[i] = static_cast<char>(readByte);
    }
    memcpy(&value, bytes, sizeof(unsigned int));
    return value;
}

std::vector<unsigned char> IntValue::GetBytes()
{
    std::vector<unsigned char> bytes(sizeof(int));
    for (int i = 0; i < sizeof(int); ++i)
    {
        bytes[i] = static_cast<unsigned char>(Value & 0xFF);
        Value >>= 8;
    }
    return bytes;
}

int IntValue::ReadValue(std::istream &stream)
{
    // Using ">>" does not work for some reason so we are going to read it by hand.
    int value;
    char bytes[sizeof(int)];
    for (int i = 0; i < sizeof(int); i++)
    {
        const auto readByte = stream.get();
        if (readByte == -1)
            throw FluxionEndOfStreamException();
        bytes[i] = static_cast<char>(readByte);
    }
    memcpy(&value, bytes, sizeof(int));
    return value;
}

std::vector<unsigned char> UShortValue::GetBytes()
{
    std::vector<unsigned char> bytes(sizeof(ushort));
    // Little-endian: least significant byte first
    bytes[0] = static_cast<unsigned char>(Value & 0xFF);
    bytes[1] = static_cast<unsigned char>((Value >> 8) & 0xFF);
    return bytes;
}

unsigned short UShortValue::ReadValue(std::istream &stream)
{
    // Using ">>" does not work for some reason so we are going to read it by hand.
    unsigned short value;
    char bytes[sizeof(unsigned short)];
    for (int i = 0; i < sizeof(unsigned short); i++)
    {
        const auto readByte = stream.get();
        if (readByte == -1)
            throw FluxionEndOfStreamException();
        bytes[i] = static_cast<char>(readByte);
    }
    memcpy(&value, bytes, sizeof(unsigned short));
    return value;
}

std::vector<unsigned char> ShortValue::GetBytes()
{
    std::vector<unsigned char> bytes(sizeof(short));
    bytes[0] = static_cast<unsigned char>(Value & 0xFF);
    bytes[1] = static_cast<unsigned char>((Value >> 8) & 0xFF);
    return bytes;
}

short ShortValue::ReadValue(std::istream &stream)
{
    // Using ">>" does not work for some reason so we are going to read it by hand.
    short value;
    char bytes[sizeof(short)];
    for (int i = 0; i < sizeof(short); i++)
    {
        const auto readByte = stream.get();
        if (readByte == -1)
            throw FluxionEndOfStreamException();
        bytes[i] = static_cast<char>(readByte);
    }
    memcpy(&value, bytes, sizeof(short));
    return value;
}

std::vector<unsigned char> CharValue::GetBytes()
{
    std::vector<unsigned char> utf16_bytes;
    if (Value <= 0xFFFF)
    {
        utf16_bytes.push_back(static_cast<unsigned char>(Value & 0xFF));
        utf16_bytes.push_back(static_cast<unsigned char>((Value >> 8) & 0xFF));
    }
    else
    {
        const char16_t high_surrogate = 0xD800 + ((Value - 0x10000) >> 10);
        const char16_t low_surrogate = 0xDC00 + ((Value - 0x10000) & 0x3FF);
        utf16_bytes.push_back(static_cast<unsigned char>(high_surrogate & 0xFF));
        utf16_bytes.push_back(static_cast<unsigned char>((high_surrogate >> 8) & 0xFF));
        utf16_bytes.push_back(static_cast<unsigned char>(low_surrogate & 0xFF));
        utf16_bytes.push_back(static_cast<unsigned char>((low_surrogate >> 8) & 0xFF));
    }

    return utf16_bytes;
}

char16_t CharValue::ReadValue(std::istream &stream)
{
    unsigned char byte1 = 0, byte2 = 0;
    stream >> byte1 >> byte2;

    if (byte1 <= 0x7F)
    {
        return byte1;
    }
    if (byte1 <= 0xDF)
    {
        return (byte1 - 0xD800) << 10 | ((byte2 & 0x3F) << 6);
    }
    if (byte1 <= 0xBF)
    {
        return 0x10000 + ((byte1 & 0x3F) << 10) | ((byte2 & 0x3F) << 6);
    }
    return 0;
}
