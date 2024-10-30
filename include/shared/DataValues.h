//
// Created by haltroy on 01.05.2024.
//

#ifndef DATA_VALUES_H
#define DATA_VALUES_H
#include <ostream>
#include <string>
#include <utility>

#include "Encodings.h"

enum FluxionDataTypes
{
    Null,
    Bool,
    Byte,
    SByte,
    Char,
    Short,
    UShort,
    Int,
    UInt,
    Long,
    ULong,
    Float,
    Double,
    ByteArray,
    String
};

class FluxionValue final
{
public:
    FluxionDataTypes Type = Null;

    bool UniqueFlagSet() const;
    std::vector<unsigned char> GetBytes(const Encoding* encoding) const;

    void ReadValue(std::istream& stream);

    int EstimateSize(const Encoding* encoding) const;

    void WriteValueV2(std::ostream* os, const Encoding* encoding) const;

    bool IsEmpty() const;

    int ValueTypeIndex(int version) const;

    union UnionValue
    {
        unsigned char byteValue;
        signed char sbyteValue;
        char16_t charValue;
        short shortValue;
        unsigned short ushortValue;
        bool boolValue;
        int intValue;
        unsigned int uintValue;
        long longValue;
        unsigned long ulongValue;
        float floatValue;
        double doubleValue;
        std::string stringValue;
        std::vector<unsigned char> byteArrayValue;

        ~UnionValue()
        {
        }

        explicit UnionValue(bool value) : boolValue(value)
        {
        }

        explicit UnionValue(unsigned char value) : byteValue(value)
        {
        }

        explicit UnionValue(signed char value) : sbyteValue(value)
        {
        }

        explicit UnionValue(char16_t value) : charValue(value)
        {
        }

        explicit UnionValue(short value) : shortValue(value)
        {
        }

        explicit UnionValue(unsigned short value) : ushortValue(value)
        {
        }

        explicit UnionValue(int value) : intValue(value)
        {
        }

        explicit UnionValue(unsigned int value) : uintValue(value)
        {
        }

        explicit UnionValue(long value) : longValue(value)
        {
        }

        explicit UnionValue(unsigned long value) : ulongValue(value)
        {
        }

        explicit UnionValue(float value) : floatValue(value)
        {
        }

        explicit UnionValue(double value) : doubleValue(value)
        {
        }

        explicit UnionValue(std::string value) : stringValue(std::move(value))
        {
        }

        explicit UnionValue(std::vector<unsigned char> value) : byteArrayValue(std::move(value))
        {
        }
    } Value;

    FluxionValue& operator=(const FluxionValue& value);
    FluxionValue& operator=(bool value);
    FluxionValue& operator=(unsigned char value);
    FluxionValue& operator=(signed char value);
    FluxionValue& operator=(char16_t value);
    FluxionValue& operator=(short value);
    FluxionValue& operator=(unsigned short value);
    FluxionValue& operator=(int value);
    FluxionValue& operator=(unsigned int value);
    FluxionValue& operator=(long value);
    FluxionValue& operator=(unsigned long value);
    FluxionValue& operator=(float value);
    FluxionValue& operator=(double value);
    FluxionValue& operator=(nullptr_t value);
    FluxionValue& operator=(std::string value);
    FluxionValue& operator=(std::vector<unsigned char> value);

    bool operator==(const FluxionValue& other) const;
    bool operator==(nullptr_t other) const;
    bool operator==(bool other) const;
    bool operator==(unsigned char other) const;
    bool operator==(signed char other) const;
    bool operator==(char16_t other) const;
    bool operator==(short other) const;
    bool operator==(unsigned short other) const;
    bool operator==(int other) const;
    bool operator==(unsigned int other) const;
    bool operator==(long other) const;
    bool operator==(unsigned long other) const;
    bool operator==(float other) const;
    bool operator==(double other) const;
    bool operator==(const std::string& other) const;
    bool operator==(const std::vector<unsigned char>& other) const;

    explicit FluxionValue(nullptr_t value);
    explicit FluxionValue(bool value);
    explicit FluxionValue(unsigned char value);
    explicit FluxionValue(signed char value);
    explicit FluxionValue(char16_t value);
    explicit FluxionValue(short value);
    explicit FluxionValue(unsigned short value);
    explicit FluxionValue(int value);
    explicit FluxionValue(unsigned int value);
    explicit FluxionValue(long value);
    explicit FluxionValue(unsigned long value);
    explicit FluxionValue(float value);
    explicit FluxionValue(double value);
    explicit FluxionValue(std::string value);
    explicit FluxionValue(std::vector<unsigned char> value);
};

#endif // DATA_VALUES_H
