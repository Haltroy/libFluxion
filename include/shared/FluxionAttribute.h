//
// Created by haltroy on 17.10.2024.
//

#ifndef FLUXIONATTRIBUTE_H
#define FLUXIONATTRIBUTE_H
#include <cstddef>
#include <string>
#include <vector>

#include "DataValues.h"

class FluxionAttribute
{
public:
    FluxionAttribute()
    = default;

    FluxionAttribute(std::string name, nullptr_t value);
    FluxionAttribute(std::string name, bool value);
    FluxionAttribute(std::string name, unsigned char value);
    FluxionAttribute(std::string name, signed char value);
    FluxionAttribute(std::string name, char16_t value);
    FluxionAttribute(std::string name, short value);
    FluxionAttribute(std::string name, unsigned short value);
    FluxionAttribute(std::string name, int value);
    FluxionAttribute(std::string name, unsigned int value);
    FluxionAttribute(std::string name, long value);
    FluxionAttribute(std::string name, unsigned long value);
    FluxionAttribute(std::string name, float value);
    FluxionAttribute(std::string name, double value);
    FluxionAttribute(std::string name, std::string value);
    FluxionAttribute(std::string name, const std::vector<unsigned char>& value);
    explicit FluxionAttribute(nullptr_t value);
    explicit FluxionAttribute(bool value);
    explicit FluxionAttribute(unsigned char value);
    explicit FluxionAttribute(signed char value);
    explicit FluxionAttribute(char16_t value);
    explicit FluxionAttribute(short value);
    explicit FluxionAttribute(unsigned short value);
    explicit FluxionAttribute(int value);
    explicit FluxionAttribute(unsigned int value);
    explicit FluxionAttribute(long value);
    explicit FluxionAttribute(unsigned long value);
    explicit FluxionAttribute(float value);
    explicit FluxionAttribute(double value);
    explicit FluxionAttribute(const std::string& value);
    explicit FluxionAttribute(std::vector<unsigned char> value);
    std::string Name;
    FluxionValue* Value = nullptr;
    std::vector<unsigned char> value_;
};

#endif //FLUXIONATTRIBUTE_H
