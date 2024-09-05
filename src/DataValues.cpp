//
// Created by haltroy on 02.05.2024.
//

#include "shared/DataValues.h"
#include "shared/FluxionException.h"

#include <fstream>
#include <cstring>
#include <bits/locale_facets_nonio.h>

int ByteArrayValue::EstimateSize(const Encoding *encoding) {
    int bytes = 1;
    auto intValue = Value.size();
    while ((intValue >>= 7) != 0)
        bytes++;
    return bytes + static_cast<int>(Value.size());
}

bool ByteArrayValue::isSame(DataValues *other) {
    if (ValueTypeIndexV2() != ValueTypeIndexV2()) return false;
    auto dynamic = dynamic_cast<ByteArrayValue *>(other);
    if (dynamic->Value.size() != Value.size()) return false;

    for (int i = 0; i < Value.size(); i++) {
        if (dynamic->Value[i] != Value[i]) return false;
    }
    return true;
}


void ByteArrayValue::WriteValueV2(std::ostream *os, const Encoding *encoding) {
    auto valueSize = Value.size();
    do {
        unsigned char b = valueSize & 0x7F;
        valueSize >>= 7;
        b |= (valueSize > 0 ? 0x80 : 0);
        os->put(static_cast<char>(b));
    } while (valueSize > 0);
    os->write(reinterpret_cast<const char *>(Value.data()), static_cast<long int>(Value.size()));
}


int StringValue::EstimateSize(const Encoding *encoding) {
    auto encoded = encoding->string_to_bytes(Value);
    int bytes = 1;
    auto intValue = encoded.size();

    while ((intValue >>= 7) != 0)
        bytes++;
    return bytes + static_cast<int>(encoded.size());
}

void StringValue::WriteValueV2(std::ostream *os, const Encoding *encoding) {
    auto value = encoding->string_to_bytes(Value);
    auto valueSize = value.size();
    do {
        unsigned char b = valueSize & 0x7F;
        valueSize >>= 7;
        b |= (valueSize > 0 ? 0x80 : 0);
        os->put(static_cast<char>(b));
    } while (valueSize > 0);
    os->write(reinterpret_cast<const char *>(value.data()), static_cast<long int>(value.size()));
}


std::vector<unsigned char> DoubleValue::GetBytes() {
    union {
        double d;
        unsigned long long i;
    } conv{};
    conv.d = Value;
    std::vector<unsigned char> bytes(sizeof(unsigned long long));
    for (int i = 0; i < sizeof(unsigned long long); ++i) {
        bytes[i] = static_cast<unsigned char>(conv.i & 0xFF);
        conv.i >>= 8;
    }
    return bytes;
}

void DoubleValue::WriteValueV2(std::ostream *os, const Encoding *encoding) {
    auto bytes = GetBytes();
    os->write(reinterpret_cast<const char *>(bytes.data()), static_cast<long int>(bytes.size()));
}


double DoubleValue::ReadValue(std::istream &stream) {
    // Using ">>" does not work for some reason so we are going to read it by hand.
    double value;
    char bytes[sizeof(double)];
    for (char &byte: bytes) {
        const auto readByte = stream.get();
        if (readByte == -1)
            throw FluxionEndOfStreamException();
        byte = static_cast<char>(readByte);
    }
    memcpy(&value, bytes, sizeof(double));
    return value;
}

std::vector<unsigned char> FloatValue::GetBytes() {
    union {
        float f;
        unsigned int i;
    } conv{};
    conv.f = Value;
    std::vector<unsigned char> bytes(sizeof(unsigned int));
    for (int i = 0; i < sizeof(unsigned int); ++i) {
        bytes[i] = static_cast<unsigned char>(conv.i & 0xFF);
        conv.i >>= 8;
    }
    return bytes;
}

void FloatValue::WriteValueV2(std::ostream *os, const Encoding *encoding) {
    auto bytes = GetBytes();
    os->write(reinterpret_cast<const char *>(bytes.data()), static_cast<long int>(bytes.size()));
}


float FloatValue::ReadValue(std::istream &stream) {
    // Using ">>" does not work for some reason so we are going to read it by hand.
    float value;
    char bytes[sizeof(float)];
    for (char &byte: bytes) {
        const auto readByte = stream.get();
        if (readByte == -1)
            throw FluxionEndOfStreamException();
        byte = static_cast<char>(readByte);
    }
    memcpy(&value, bytes, sizeof(float));
    return value;
}

std::vector<unsigned char> ULongValue::GetBytes() {
    std::vector<unsigned char> bytes(sizeof(unsigned long));
    for (int i = 0; i < sizeof(unsigned long); ++i) {
        bytes[i] = static_cast<unsigned char>(Value & 0xFF);
        Value >>= 8;
    }
    return bytes;
}

void ULongValue::WriteValueV2(std::ostream *os, const Encoding *encoding) {
    auto value = Value;
    while (true) {
        auto b = static_cast<char>(value & 0x7F);
        value >>= 7;

        if (value == 0) {
            os->put(b);
            break;
        }

        os->put(static_cast<char>(b | 0x80));
    }
}

int ULongValue::EstimateSize(const Encoding *encoding) {
    int bytes = 1;
    auto value = Value;
    while ((value >>= 7) != 0)
        bytes++;
    return bytes;
}

unsigned long ULongValue::ReadValue(std::istream &stream) {
    // Using ">>" does not work for some reason so we are going to read it by hand.
    unsigned long value;
    char bytes[sizeof(unsigned long)];
    for (char &byte: bytes) {
        const auto readByte = stream.get();
        if (readByte == -1)
            throw FluxionEndOfStreamException();
        byte = static_cast<char>(readByte);
    }
    memcpy(&value, bytes, sizeof(unsigned long));
    return value;
}

std::vector<unsigned char> LongValue::GetBytes() {
    std::vector<unsigned char> bytes(sizeof(long));
    for (int i = 0; i < sizeof(long); ++i) {
        bytes[i] = static_cast<unsigned char>(Value & 0xFF);
        Value >>= 8;
    }
    return bytes;
}

int LongValue::EstimateSize(const Encoding *encoding) {
    int bytes = 1;
    auto longValue = Value;
    if (longValue < 0) {
        longValue = ~longValue;
        longValue++;
    }

    while ((longValue >>= 7) != 0)
        bytes++;
    return bytes;
}

void LongValue::WriteValueV2(std::ostream *os, const Encoding *encoding) {
    auto value = Value;
    if (value < 0) value = -value;
    while (true) {
        auto b = static_cast<char>(value & 0x7F);
        value >>= 7;

        if (value == 0) {
            os->put(b);
            break;
        }

        os->put(static_cast<char>(b | 0x80));
    }
}


long LongValue::ReadValue(std::istream &stream) {
    // Using ">>" does not work for some reason so we are going to read it by hand.
    long value;
    char bytes[sizeof(long)];
    for (char &byte: bytes) {
        const auto readByte = stream.get();
        if (readByte == -1)
            throw FluxionEndOfStreamException();
        byte = static_cast<char>(readByte);
    }
    memcpy(&value, bytes, sizeof(long));
    return value;
}

std::vector<unsigned char> UIntValue::GetBytes() {
    std::vector<unsigned char> bytes(sizeof(unsigned int));
    for (int i = 0; i < sizeof(unsigned int); ++i) {
        bytes[i] = static_cast<unsigned char>(Value & 0xFF);
        Value >>= 8;
    }
    return bytes;
}

int UIntValue::EstimateSize(const Encoding *encoding) {
    int bytes = 1;
    auto uintValue = Value;
    while ((uintValue >>= 7) != 0)
        bytes++;
    return bytes;
}

void UIntValue::WriteValueV2(std::ostream *os, const Encoding *encoding) {
    auto value = Value;
    while (true) {
        auto b = static_cast<char>(value & 0x7F);
        value >>= 7;

        if (value == 0) {
            os->put(b);
            break;
        }

        os->put(static_cast<char>(b | 0x80));
    }
}


unsigned int UIntValue::ReadValue(std::istream &stream) {
    // Using ">>" does not work for some reason so we are going to read it by hand.
    unsigned int value;
    char bytes[sizeof(unsigned int)];
    for (char &byte: bytes) {
        const auto readByte = stream.get();
        if (readByte == -1)
            throw FluxionEndOfStreamException();
        byte = static_cast<char>(readByte);
    }
    memcpy(&value, bytes, sizeof(unsigned int));
    return value;
}

std::vector<unsigned char> IntValue::GetBytes() {
    std::vector<unsigned char> bytes(sizeof(int));
    for (int i = 0; i < sizeof(int); ++i) {
        bytes[i] = static_cast<unsigned char>(Value & 0xFF);
        Value >>= 8;
    }
    return bytes;
}

void IntValue::WriteValueV2(std::ostream *os, const Encoding *encoding) {
    auto value = Value;
    if (value < 0) value = -value;
    while (true) {
        auto b = static_cast<char>(value & 0x7F);
        value >>= 7;

        if (value == 0) {
            os->put(b);
            break;
        }

        os->put(static_cast<char>(b | 0x80));
    }
}


int IntValue::EstimateSize(const Encoding *encoding) {
    int bytes = 1;
    auto intValue = Value;
    if (intValue < 0) {
        intValue = ~intValue;
        intValue++;
    }

    while ((intValue >>= 7) != 0)
        bytes++;
    return bytes;
}

int IntValue::ReadValue(std::istream &stream) {
    // Using ">>" does not work for some reason so we are going to read it by hand.
    int value;
    char bytes[sizeof(int)];
    for (char &byte: bytes) {
        const auto readByte = stream.get();
        if (readByte == -1)
            throw FluxionEndOfStreamException();
        byte = static_cast<char>(readByte);
    }
    memcpy(&value, bytes, sizeof(int));
    return value;
}

std::vector<unsigned char> UShortValue::GetBytes() {
    std::vector<unsigned char> bytes(sizeof(ushort));
    // Little-endian: least significant byte first
    bytes[0] = static_cast<unsigned char>(Value & 0xFF);
    bytes[1] = static_cast<unsigned char>((Value >> 8) & 0xFF);
    return bytes;
}

int UShortValue::EstimateSize(const Encoding *encoding) {
    int bytes = 1;
    auto unsignedShortValue = Value;
    while ((unsignedShortValue >>= 7) != 0)
        bytes++;
    return bytes;
}

void UShortValue::WriteValueV2(std::ostream *os, const Encoding *encoding) {
    auto value = Value;
    while (true) {
        auto b = static_cast<char>(value & 0x7F);
        value >>= 7;

        if (value == 0) {
            os->put(b);
            break;
        }

        os->put(static_cast<char>(b | 0x80));
    }
}


unsigned short UShortValue::ReadValue(std::istream &stream) {
    // Using ">>" does not work for some reason so we are going to read it by hand.
    unsigned short value;
    char bytes[sizeof(unsigned short)];
    for (char &byte: bytes) {
        const auto readByte = stream.get();
        if (readByte == -1)
            throw FluxionEndOfStreamException();
        byte = static_cast<char>(readByte);
    }
    memcpy(&value, bytes, sizeof(unsigned short));
    return value;
}

std::vector<unsigned char> ShortValue::GetBytes() {
    std::vector<unsigned char> bytes(sizeof(short));
    bytes[0] = static_cast<unsigned char>(Value & 0xFF);
    bytes[1] = static_cast<unsigned char>((Value >> 8) & 0xFF);
    return bytes;
}

int ShortValue::EstimateSize(const Encoding *encoding) {
    int bytes = 1;
    auto shortValue = Value;
    if (shortValue < 0) {
        shortValue = static_cast<short>(~shortValue);
        shortValue++;
    }

    while ((shortValue >>= 7) != 0)
        bytes++;
    return bytes;
}

void ShortValue::WriteValueV2(std::ostream *os, const Encoding *encoding) {
    auto value = Value;
    if (value < 0) value = static_cast<short>(-value);
    while (true) {
        auto b = static_cast<char>(value & 0x7F);
        value >>= 7;

        if (value == 0) {
            os->put(b);
            break;
        }

        os->put(static_cast<char>(b | 0x80));
    }
}


short ShortValue::ReadValue(std::istream &stream) {
    // Using ">>" does not work for some reason so we are going to read it by hand.
    short value;
    char bytes[sizeof(short)];
    for (char &byte: bytes) {
        const auto readByte = stream.get();
        if (readByte == -1)
            throw FluxionEndOfStreamException();
        byte = static_cast<char>(readByte);
    }
    memcpy(&value, bytes, sizeof(short));
    return value;
}

std::vector<unsigned char> CharValue::GetBytes() {
    std::vector<unsigned char> utf16_bytes;
    if (Value <= 0xFFFF) {
        utf16_bytes.push_back(static_cast<unsigned char>(Value & 0xFF));
        utf16_bytes.push_back(static_cast<unsigned char>((Value >> 8) & 0xFF));
    } else {
        const char16_t high_surrogate = 0xD800 + ((Value - 0x10000) >> 10);
        const char16_t low_surrogate = 0xDC00 + ((Value - 0x10000) & 0x3FF);
        utf16_bytes.push_back(static_cast<unsigned char>(high_surrogate & 0xFF));
        utf16_bytes.push_back(static_cast<unsigned char>((high_surrogate >> 8) & 0xFF));
        utf16_bytes.push_back(static_cast<unsigned char>(low_surrogate & 0xFF));
        utf16_bytes.push_back(static_cast<unsigned char>((low_surrogate >> 8) & 0xFF));
    }

    return utf16_bytes;
}

void CharValue::WriteValueV2(std::ostream *os, const Encoding *encoding) {
    auto value = Value;
    while (true) {
        auto b = static_cast<char>(value & 0x7F);
        value >>= 7;

        if (value == 0) {
            os->put(b);
            break;
        }

        os->put(static_cast<char>(b | 0x80));
    }
}


int CharValue::EstimateSize(const Encoding *encoding) {
    int bytes = 1;
    auto charValue = Value;
    while ((charValue >>= 7) != 0)
        bytes++;
    return bytes;
}

char16_t CharValue::ReadValue(std::istream &stream) {
    unsigned char byte1 = 0, byte2 = 0;
    stream >> byte1 >> byte2;

    if (byte1 <= 0x7F) {
        return byte1;
    }
    if (byte1 <= 0xDF) {
        return (byte1 - 0xD800) << 10 | ((byte2 & 0x3F) << 6);
    }
    if (byte1 <= 0xBF) {
        return 0x10000 + ((byte1 & 0x3F) << 10) | ((byte2 & 0x3F) << 6);
    }
    return 0;
}
