//
// Created by haltroy on 01.05.2024.
//

#ifndef ENCODINGS_H
#define ENCODINGS_H
#include <string>
#include <vector>

class Encoding {
public:
    explicit Encoding(const unsigned char id) : id(id) {
    }

    virtual ~Encoding() = default;

    virtual std::vector<unsigned char> string_to_bytes(const std::string &string) const = 0;

    virtual std::string bytes_to_string(const std::vector<unsigned char> &bytes_data) const = 0;

    unsigned char ID() const { return id; };

private:
    unsigned char id;
};

class UTF8Encoding : public Encoding {
public:
    UTF8Encoding() : Encoding(0) {
    }

    std::vector<unsigned char> string_to_bytes(const std::string &string) const override {
        return std::vector<unsigned char>(string.begin(), string.end());
    }

    std::string bytes_to_string(const std::vector<unsigned char> &bytes_data) const override {
        return std::string(bytes_data.begin(), bytes_data.end());
    }
};

class UTF16Encoding : public Encoding {
public:
    UTF16Encoding() : Encoding(1) {
    }

    std::vector<unsigned char> string_to_bytes(const std::string &string) const override {
        return std::vector<unsigned char>(string.begin(), string.end());
    }

    std::string bytes_to_string(const std::vector<unsigned char> &bytes_data) const override {
        return std::string(bytes_data.begin(), bytes_data.end());
    }
};

class UTF32Encoding : public Encoding {
public:
    UTF32Encoding() : Encoding(2) {
    }

    std::vector<unsigned char> string_to_bytes(const std::string &string) const override {
        return std::vector<unsigned char>(string.begin(), string.end());
    }

    std::string bytes_to_string(const std::vector<unsigned char> &bytes_data) const override {
        return std::string(bytes_data.begin(), bytes_data.end());
    }
};

#endif //ENCODINGS_H
