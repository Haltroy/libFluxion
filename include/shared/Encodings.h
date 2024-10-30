//
// Created by haltroy on 01.05.2024.
//

#ifndef ENCODINGS_H
#define ENCODINGS_H
#include <codecvt>
#include <locale>
#include <string>
#include <vector>

class Encoding
{
public:
    explicit Encoding(const unsigned char id) : id(id)
    {
    }

    virtual ~Encoding() = default;

    virtual std::vector<unsigned char> string_to_bytes(const std::string& string) const = 0;

    virtual std::string bytes_to_string(const std::vector<unsigned char>& bytes_data) const = 0;

    unsigned char ID() const { return id; };

private:
    unsigned char id;
};

class UTF8Encoding final : public Encoding
{
public:
    UTF8Encoding() : Encoding(0)
    {
    }

    std::vector<unsigned char> string_to_bytes(const std::string& string) const override
    {
        std::vector<unsigned char> result;
        result.reserve(string.length());

        for (const char c : string)
        {
            result.push_back(static_cast<unsigned char>(c));
        }

        return result;
    }

    std::string bytes_to_string(const std::vector<unsigned char>& bytes_data) const override
    {
        return {bytes_data.begin(), bytes_data.end()};
    }
};

class UTF16Encoding final : public Encoding
{
public:
    UTF16Encoding() : Encoding(1)
    {
    }

    std::vector<unsigned char> string_to_bytes(const std::string& string) const override
    {
        std::wstring_convert<std::codecvt_utf16<wchar_t>> converter;
        std::wstring wide_str = converter.from_bytes(string);

        std::vector<unsigned char> result;
        for (const wchar_t c : wide_str)
        {
            result.push_back(static_cast<unsigned char>(c & 0xFF));
            result.push_back(static_cast<unsigned char>((c >> 8) & 0xFF));
        }

        return result;
    }

    std::string bytes_to_string(const std::vector<unsigned char>& bytes_data) const override
    {
        if (bytes_data.size() % 2 != 0)
        {
            return "";
        }

        std::wstring wide_str;
        for (size_t i = 0; i < bytes_data.size(); i += 2)
        {
            const wchar_t c = (bytes_data[i] | (bytes_data[i + 1] << 8));
            wide_str.push_back(c);
        }

        std::wstring_convert<std::codecvt_utf16<wchar_t>> converter;
        return converter.to_bytes(wide_str);
    }
};

#endif //ENCODINGS_H
