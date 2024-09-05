//
// Created by haltroy on 01.05.2024.
//

#ifndef DATA_VALUES_H
#define DATA_VALUES_H
#include <ostream>
#include <string>

#include "Encodings.h"

class DataValues {
public:
    virtual ~DataValues() = default;

    virtual unsigned char ValueTypeIndex() { return 0; };
    virtual unsigned char ValueTypeIndexV2() { return 0; };
    virtual bool UniqueFlagSet() { return false; };

    virtual void WriteValueV2(std::ostream *os, const Encoding *encoding) {
    };

    virtual std::vector<unsigned char> GetBytes() {
        return {};
    };
    virtual int EstimateSize(const Encoding *encoding) { return 0; };
    virtual bool isSame(DataValues *other) { return false; };
    virtual bool IsEmpty() { return false; };
};

class NullValue final : public DataValues {
public:
    unsigned char ValueTypeIndex() override {
        return 0;
    };
    unsigned char ValueTypeIndexV2() override { return ValueTypeIndex(); };
    bool UniqueFlagSet() override { return false; };

    std::vector<unsigned char> GetBytes() override {
        return {};
    };
    int EstimateSize(const Encoding *encoding) override { return 0; };

    void WriteValueV2(std::ostream *os, const Encoding *encoding) override {
    };

    bool isSame(DataValues *other) override { return ValueTypeIndexV2() == ValueTypeIndexV2(); };
    bool IsEmpty() override { return true; };
};

class BoolValue final : public DataValues {
public:
    explicit BoolValue(const bool value) : Value(value) {
    }

    bool Value;

    unsigned char ValueTypeIndex() override {
        return this->Value ? 1 : 2;
    };

    unsigned char ValueTypeIndexV2() override { return ValueTypeIndex(); };
    bool UniqueFlagSet() override { return false; };

    std::vector<unsigned char> GetBytes() override {
        return {};
    };
    int EstimateSize(const Encoding *encoding) override { return 0; };

    void WriteValueV2(std::ostream *os, const Encoding *encoding) override {
    };

    bool isSame(DataValues *other) override {
        if (ValueTypeIndexV2() != ValueTypeIndexV2()) return false;
        auto dynamic = dynamic_cast<BoolValue *>(other);
        return dynamic->Value == Value;
    };
    bool IsEmpty() override { return true; };
};

class ByteValue final : public DataValues {
public:
    explicit ByteValue(const unsigned char value) : Value(value) {
    }

    unsigned char Value;

    unsigned char ValueTypeIndex() override {
        return 3;
    };

    unsigned char ValueTypeIndexV2() override { return ValueTypeIndex(); };
    bool UniqueFlagSet() override { return Value == 0; };

    std::vector<unsigned char> GetBytes() override {
        return {Value};
    };

    int EstimateSize(const Encoding *encoding) override { return 1; };

    void WriteValueV2(std::ostream *os, const Encoding *encoding) override {
        os->put(static_cast<char>(Value));
    };

    bool isSame(DataValues *other) override {
        if (ValueTypeIndexV2() != ValueTypeIndexV2()) return false;
        auto dynamic = dynamic_cast<ByteValue *>(other);
        return dynamic->Value == Value;
    };
    bool IsEmpty() override { return Value == 0; };
};

class SByteValue final : public DataValues {
public:
    explicit SByteValue(const signed char value) : Value(value) {
    }

    signed char Value;

    unsigned char ValueTypeIndex() override {
        return 4;
    };

    unsigned char ValueTypeIndexV2() override { return ValueTypeIndex(); };
    bool UniqueFlagSet() override { return Value <= 0; };

    std::vector<unsigned char> GetBytes() override {
        return {static_cast<unsigned char>(Value)};
    };

    int EstimateSize(const Encoding *encoding) override { return 1; };

    void WriteValueV2(std::ostream *os, const Encoding *encoding) override {
        os->put(static_cast<char>(Value));
    };

    bool isSame(DataValues *other) override {
        if (ValueTypeIndexV2() != ValueTypeIndexV2()) return false;
        auto dynamic = dynamic_cast<SByteValue *>(other);
        return dynamic->Value == Value;
    };
    bool IsEmpty() override { return Value == 0; };
};

class CharValue final : public DataValues {
public:
    explicit CharValue(const char16_t value) : Value(value) {
    }

    char16_t Value;

    unsigned char ValueTypeIndex() override {
        return 5;
    };


    unsigned char ValueTypeIndexV2() override { return ValueTypeIndex(); };
    bool UniqueFlagSet() override { return Value == 0; };

    std::vector<unsigned char> GetBytes() override;

    static char16_t ReadValue(std::istream &stream);

    int EstimateSize(const Encoding *encoding) override;

    void WriteValueV2(std::ostream *os, const Encoding *encoding) override;

    bool isSame(DataValues *other) override {
        if (ValueTypeIndexV2() != ValueTypeIndexV2()) return false;
        auto dynamic = dynamic_cast<CharValue *>(other);
        return dynamic->Value == Value;
    };
    bool IsEmpty() override { return Value == 0; };
};

class ShortValue final : public DataValues {
public:
    explicit ShortValue(const short value) : Value(value) {
    }

    short Value;

    unsigned char ValueTypeIndex() override {
        return 6;
    };

    unsigned char ValueTypeIndexV2() override {
        return Value == 0 ? 0 : ValueTypeIndex();
    };
    bool UniqueFlagSet() override { return Value < 0; };

    std::vector<unsigned char> GetBytes() override;

    static short ReadValue(std::istream &stream);

    int EstimateSize(const Encoding *encoding) override;

    void WriteValueV2(std::ostream *os, const Encoding *encoding) override;

    bool isSame(DataValues *other) override {
        if (ValueTypeIndexV2() != ValueTypeIndexV2()) return false;
        auto dynamic = dynamic_cast<ShortValue *>(other);
        return dynamic->Value == Value;
    };
    bool IsEmpty() override { return Value == 0; };
};

class UShortValue final : public DataValues {
public:
    explicit UShortValue(const unsigned short value) : Value(value) {
    }

    unsigned short Value;

    unsigned char ValueTypeIndex() override {
        return 7;
    };

    unsigned char ValueTypeIndexV2() override { return ValueTypeIndex(); };
    bool UniqueFlagSet() override { return Value == 0; };

    std::vector<unsigned char> GetBytes() override;

    static unsigned short ReadValue(std::istream &stream);

    int EstimateSize(const Encoding *encoding) override;

    void WriteValueV2(std::ostream *os, const Encoding *encoding) override;

    bool isSame(DataValues *other) override {
        if (ValueTypeIndexV2() != ValueTypeIndexV2()) return false;
        auto dynamic = dynamic_cast<UShortValue *>(other);
        return dynamic->Value == Value;
    };
    bool IsEmpty() override { return Value == 0; };
};

class IntValue final : public DataValues {
public:
    explicit IntValue(const int value) : Value(value) {
    }

    int Value;

    unsigned char ValueTypeIndex() override {
        return 8;
    };

    unsigned char ValueTypeIndexV2() override {
        return Value == 0 ? 1 : ValueTypeIndex();
    };
    bool UniqueFlagSet() override { return Value < 0; };

    std::vector<unsigned char> GetBytes() override;

    static int ReadValue(std::istream &stream);

    int EstimateSize(const Encoding *encoding) override;

    void WriteValueV2(std::ostream *os, const Encoding *encoding) override;

    bool isSame(DataValues *other) override {
        if (ValueTypeIndexV2() != ValueTypeIndexV2()) return false;
        auto dynamic = dynamic_cast<IntValue *>(other);
        return dynamic->Value == Value;
    };
    bool IsEmpty() override { return Value == 0; };
};

class UIntValue final : public DataValues {
public:
    explicit UIntValue(const unsigned int value) : Value(value) {
    }

    unsigned int Value;

    unsigned char ValueTypeIndex() override {
        return 9;
    };

    unsigned char ValueTypeIndexV2() override { return ValueTypeIndex(); };
    bool UniqueFlagSet() override { return Value == 0; };

    std::vector<unsigned char> GetBytes() override;

    static unsigned int ReadValue(std::istream &stream);

    int EstimateSize(const Encoding *encoding) override;

    void WriteValueV2(std::ostream *os, const Encoding *encoding) override;

    bool isSame(DataValues *other) override {
        if (ValueTypeIndexV2() != ValueTypeIndexV2()) return false;
        auto dynamic = dynamic_cast<UIntValue *>(other);
        return dynamic->Value == Value;
    };
    bool IsEmpty() override { return Value == 0; };
};

class LongValue final : public DataValues {
public:
    explicit LongValue(const long value) : Value(value) {
    }

    long Value;

    unsigned char ValueTypeIndex() override {
        return 10;
    };

    unsigned char ValueTypeIndexV2() override {
        return Value == 0 ? 2 : ValueTypeIndex();
    };
    bool UniqueFlagSet() override { return Value < 0; };

    std::vector<unsigned char> GetBytes() override;

    static long ReadValue(std::istream &stream);

    int EstimateSize(const Encoding *encoding) override;

    void WriteValueV2(std::ostream *os, const Encoding *encoding) override;

    bool isSame(DataValues *other) override {
        if (ValueTypeIndexV2() != ValueTypeIndexV2()) return false;
        auto dynamic = dynamic_cast<LongValue *>(other);
        return dynamic->Value == Value;
    };
    bool IsEmpty() override { return Value == 0; };
};

class ULongValue final : public DataValues {
public:
    explicit ULongValue(const unsigned long value) : Value(value) {
    }

    unsigned long Value;

    unsigned char ValueTypeIndex() override {
        return 11;
    };

    unsigned char ValueTypeIndexV2() override { return ValueTypeIndex(); };
    bool UniqueFlagSet() override { return Value == 0; };

    std::vector<unsigned char> GetBytes() override;

    static unsigned long ReadValue(std::istream &stream);

    int EstimateSize(const Encoding *encoding) override;

    void WriteValueV2(std::ostream *os, const Encoding *encoding) override;

    bool isSame(DataValues *other) override {
        if (ValueTypeIndexV2() != ValueTypeIndexV2()) return false;
        auto dynamic = dynamic_cast<ULongValue *>(other);
        return dynamic->Value == Value;
    };
    bool IsEmpty() override { return Value == 0; };
};

class FloatValue final : public DataValues {
public:
    explicit FloatValue(const float value) : Value(value) {
    }

    float Value;

    unsigned char ValueTypeIndex() override {
        return 12;
    };

    unsigned char ValueTypeIndexV2() override { return ValueTypeIndex(); };
    bool UniqueFlagSet() override { return Value == 0; };

    std::vector<unsigned char> GetBytes() override;

    static float ReadValue(std::istream &stream);

    int EstimateSize(const Encoding *encoding) override { return 4; };

    void WriteValueV2(std::ostream *os, const Encoding *encoding) override;

    bool isSame(DataValues *other) override {
        if (ValueTypeIndexV2() != ValueTypeIndexV2()) return false;
        auto dynamic = dynamic_cast<FloatValue *>(other);
        return dynamic->Value == Value;
    };
    bool IsEmpty() override { return Value == 0; };
};

class DoubleValue final : public DataValues {
public:
    explicit DoubleValue(const double value) : Value(value) {
    }

    double Value;

    unsigned char ValueTypeIndex() override {
        return 13;
    };

    unsigned char ValueTypeIndexV2() override { return ValueTypeIndex(); };
    bool UniqueFlagSet() override { return Value == 0; };

    std::vector<unsigned char> GetBytes() override;

    static double ReadValue(std::istream &stream);

    int EstimateSize(const Encoding *encoding) override { return 8; };

    void WriteValueV2(std::ostream *os, const Encoding *encoding) override;

    bool isSame(DataValues *other) override {
        if (ValueTypeIndexV2() != ValueTypeIndexV2()) return false;
        auto dynamic = dynamic_cast<DoubleValue *>(other);
        return dynamic->Value == Value;
    };

    bool IsEmpty() override { return Value == 0; };
};

class StringValue final : public DataValues {
public:
    explicit StringValue(std::string value) : Value(std::move(value)) {
    }

    std::string Value;

    unsigned char ValueTypeIndex() override {
        return 14;
    };

    unsigned char ValueTypeIndexV2() override { return ValueTypeIndex(); };
    bool UniqueFlagSet() override { return Value.empty(); };

    std::vector<unsigned char> GetBytes() override {
        return {}; // Handled specially
    };

    int EstimateSize(const Encoding *encoding) override;

    void WriteValueV2(std::ostream *os, const Encoding *encoding) override;

    bool isSame(DataValues *other) override {
        if (ValueTypeIndexV2() != ValueTypeIndexV2()) return false;
        auto dynamic = dynamic_cast<StringValue *>(other);
        return dynamic->Value == Value;
    };

    bool IsEmpty() override { return Value.empty(); };
};

class ByteArrayValue final : public DataValues {
public:
    explicit ByteArrayValue(std::vector<unsigned char> value) : Value(std::move(value)) {
    }

    std::vector<unsigned char> Value;

    unsigned char ValueTypeIndex() override {
        return 15;
    };

    unsigned char ValueTypeIndexV2() override { return ValueTypeIndex(); };
    bool UniqueFlagSet() override { return Value.empty(); };

    std::vector<unsigned char> GetBytes() override {
        return Value;
    };

    int EstimateSize(const Encoding *encoding) override;

    void WriteValueV2(std::ostream *os, const Encoding *encoding) override;

    bool isSame(DataValues *other) override;

    bool IsEmpty() override { return Value.empty(); };
};

#endif // DATA_VALUES_H
