//
// Created by haltroy on 4.9.2024.
//

#ifndef ANALYZEDDATACONTENT_H
#define ANALYZEDDATACONTENT_H

#include "DataValues.h"

class AnalyzedDataContent
{
public:
    AnalyzedDataContent() : Position(0), Value(nullptr), IsHashed(false)
    {
    }

    explicit AnalyzedDataContent(FluxionValue* value): Position(0), Value(value), IsHashed(false)
    {
    }

    AnalyzedDataContent(unsigned long position, FluxionValue* value, bool ıs_hashed)
        : Position(position),
          Value(value),
          IsHashed(ıs_hashed)
    {
    }

    mutable unsigned long Position = 0;
    FluxionValue* Value = nullptr;
    bool IsHashed = false;
    std::string Hash;
};
#endif // ANALYZEDDATACONTENT_H
