//
// Created by haltroy on 4.9.2024.
//

#ifndef ANALYZEDDATACONTENT_H
#define ANALYZEDDATACONTENT_H

#include "DataValues.h"

class AnalyzedDataContent {
public:
    AnalyzedDataContent() : Position(0), Value(nullptr), IsHashed(false) {
    }

    explicit AnalyzedDataContent(DataValues *value): Position(0), Value(value), IsHashed(false) {
    }

    AnalyzedDataContent(unsigned long position, DataValues *value, bool ıs_hashed)
        : Position(position),
          Value(value),
          IsHashed(ıs_hashed) {
    }

    unsigned long Position = 0;
    DataValues *Value = new NullValue;
    bool IsHashed = false;
    std::string Hash;
};
#endif // ANALYZEDDATACONTENT_H
