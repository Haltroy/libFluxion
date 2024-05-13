//
// Created by haltroy on 01.05.2024.
//

#ifndef DATAVALUES_H
#define DATAVALUES_H
#include <string>

#include "Encodings.h"

class DataValues
{
public:
    virtual unsigned char ValueTypeIndex() { return 0; };

    virtual std::vector<unsigned char> GetBytes()
    {
        return {};
    };
};

class NullValue final : public DataValues
{
public:
    unsigned char ValueTypeIndex() override
    {
        return 0;
    };

    std::vector<unsigned char> GetBytes() override
    {
        return {};
    };
};

class BoolValue final : public DataValues
{
public:
    BoolValue(const bool value) : Value(value)
    {
    }

    bool Value;

    unsigned char ValueTypeIndex() override
    {
        return this->Value ? 1 : 2;
    };

    std::vector<unsigned char> GetBytes() override
    {
        return {};
    };
};

class ByteValue final : public DataValues
{
public:
    ByteValue(const unsigned char value) : Value(value)
    {
    }

    unsigned char Value;

    unsigned char ValueTypeIndex() override
    {
        return 3;
    };

    std::vector<unsigned char> GetBytes() override
    {
        return {Value};
    };
};

class SByteValue final : public DataValues
{
public:
    SByteValue(const signed char value) : Value(value)
    {
    }

    signed char Value;

    unsigned char ValueTypeIndex() override
    {
        return 4;
    };

    std::vector<unsigned char> GetBytes() override
    {
        return {static_cast<unsigned char>(Value)};
    };
};

class CharValue final : public DataValues
{
public:
    CharValue(const char16_t value) : Value(value)
    {
    }

    char16_t Value;

    unsigned char ValueTypeIndex() override
    {
        return 5;
    };

    std::vector<unsigned char> GetBytes() override;

    static char16_t ReadValue(std::istream &stream);
};

class ShortValue final : public DataValues
{
public:
    ShortValue(const short value) : Value(value)
    {
    }

    short Value;

    unsigned char ValueTypeIndex() override
    {
        return 6;
    };

    std::vector<unsigned char> GetBytes() override;

    static short ReadValue(std::istream &stream);
};

class UShortValue final : public DataValues
{
public:
    UShortValue(const unsigned short value) : Value(value)
    {
    }

    unsigned short Value;

    unsigned char ValueTypeIndex() override
    {
        return 7;
    };

    std::vector<unsigned char> GetBytes() override;

    static unsigned short ReadValue(std::istream &stream);
};

class IntValue final : public DataValues
{
public:
    IntValue(const int value) : Value(value)
    {
    }

    int Value;

    unsigned char ValueTypeIndex() override
    {
        return 8;
    };

    std::vector<unsigned char> GetBytes() override;

    static int ReadValue(std::istream &stream);
};

class UIntValue final : public DataValues
{
public:
    UIntValue(const unsigned int value) : Value(value)
    {
    }

    unsigned int Value;

    unsigned char ValueTypeIndex() override
    {
        return 9;
    };

    std::vector<unsigned char> GetBytes() override;

    static unsigned int ReadValue(std::istream &stream);
};

class LongValue final : public DataValues
{
public:
    LongValue(const long value) : Value(value)
    {
    }

    long Value;

    unsigned char ValueTypeIndex() override
    {
        return 10;
    };

    std::vector<unsigned char> GetBytes() override;

    static long ReadValue(std::istream &stream);
};

class ULongValue final : public DataValues
{
public:
    ULongValue(const unsigned long value) : Value(value)
    {
    }

    unsigned long Value;

    unsigned char ValueTypeIndex() override
    {
        return 11;
    };

    std::vector<unsigned char> GetBytes() override;

    static unsigned long ReadValue(std::istream &stream);
};

class FloatValue final : public DataValues
{
public:
    FloatValue(const float value) : Value(value)
    {
    }

    float Value;

    unsigned char ValueTypeIndex() override
    {
        return 12;
    };

    std::vector<unsigned char> GetBytes() override;

    static float ReadValue(std::istream &stream);
};

class DoubleValue final : public DataValues
{
public:
    DoubleValue(const double value) : Value(value)
    {
    }

    double Value;

    unsigned char ValueTypeIndex() override
    {
        return 13;
    };

    std::vector<unsigned char> GetBytes() override;

    static double ReadValue(std::istream &stream);
};

class StringValue final : public DataValues
{
public:
    StringValue(std::string value) : Value(std::move(value))
    {
    }

    std::string Value;

    unsigned char ValueTypeIndex() override
    {
        return 14;
    };

    std::vector<unsigned char> GetBytes() override
    {
        return {}; // Handled specially
    };
};

class ByteArrayValue final : public DataValues
{
public:
    ByteArrayValue(std::vector<unsigned char> value) : Value(std::move(value))
    {
    }

    std::vector<unsigned char> Value;

    unsigned char ValueTypeIndex() override
    {
        return 15;
    };

    std::vector<unsigned char> GetBytes() override
    {
        return Value;
    };
};

#endif // DATAVALUES_H
