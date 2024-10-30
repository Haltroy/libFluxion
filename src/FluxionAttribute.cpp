//
// Created by haltroy on 17.10.2024.
//

#include <utility>

#include "shared/FluxionAttribute.h"

FluxionAttribute::FluxionAttribute(nullptr_t)
{
}

FluxionAttribute::FluxionAttribute(const unsigned char value) : Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(const signed char value) : Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(const bool value) : Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(const char16_t value) : Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(const short value) : Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(const unsigned short value) : Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(std::vector<unsigned char> value) : Value(new FluxionValue(std::move(value)))
{
}

FluxionAttribute::FluxionAttribute(const unsigned int value) : Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(const int value) : Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(const unsigned long value) : Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(const long value) : Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(const float value) : Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(const double value) : Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(const std::string& value) : Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(std::string name, nullptr_t) : Name(std::move(name))
{
}

FluxionAttribute::FluxionAttribute(std::string name, const bool value) : Name(std::move(name)),
                                                                         Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(std::string name, const char16_t value) : Name(std::move(name)),
                                                                             Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(std::string name, const unsigned char value) : Name(std::move(name)),
    Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(std::string name, const signed char value) : Name(std::move(name)),
    Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(std::string name, const unsigned short value) : Name(std::move(name)),
    Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(std::string name, const short value) : Name(std::move(name)),
                                                                          Value(new FluxionValue(value))
{
}


FluxionAttribute::FluxionAttribute(std::string name, const unsigned int value) : Name(std::move(name)),
    Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(std::string name, const int value) : Name(std::move(name)),
                                                                        Value(new FluxionValue(value))
{
}


FluxionAttribute::FluxionAttribute(std::string name, const unsigned long value) : Name(std::move(name)),
    Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(std::string name, const long value) : Name(std::move(name)),
                                                                         Value(new FluxionValue(value))
{
}


FluxionAttribute::FluxionAttribute(std::string name, const float value) : Name(std::move(name)),
                                                                          Value(new FluxionValue(value))
{
}

FluxionAttribute::FluxionAttribute(std::string name, const double value) : Name(std::move(name)),
                                                                           Value(new FluxionValue(value))
{
}


FluxionAttribute::FluxionAttribute(std::string name, std::string value) : Name(std::move(name)),
                                                                          Value(new FluxionValue(std::move(value)))
{
}

FluxionAttribute::FluxionAttribute(std::string name, const std::vector<unsigned char>& value) : Name(std::move(name)),
    Value(new FluxionValue(value))
{
}
