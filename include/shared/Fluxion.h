#ifndef LIBFLUXION_LIBRARY_H
#define LIBFLUXION_LIBRARY_H
#include <istream>
#include <vector>

#include "DataValues.h"
#include "Encodings.h"
#include "FluxionNode.h"
#include "AnalyzedDataContent.h"

class Fluxion {
public:
    static void Write(FluxionNode *node, const std::string &fileName, const Encoding *encoding,
                      unsigned char version = 0);

    static void Write(FluxionNode *node, std::ostream *stream, const Encoding *encoding, unsigned char version = 0);

    static FluxionNode *Read(std::istream &stream);

    static FluxionNode *Read(const std::string &fileName);

private:
    static bool ADC_Contains(std::vector<AnalyzedDataContent> *adc, DataValues *value);

    static void Write_V1(FluxionNode *node, std::ostream *stream, const Encoding *encoding, bool asRoot = false);

    static long Estimate_V2(FluxionNode *node, const Encoding *encoding, std::vector<AnalyzedDataContent> *adc);

    static long WriteData_V2(std::ostream *stream, const Encoding *encoding,
                             std::vector<AnalyzedDataContent> *adc);

    static void Write_V2(FluxionNode *node, std::ostream *stream, const Encoding *encoding,
                         std::vector<AnalyzedDataContent> *adc, bool asRoot = false);

    static FluxionNode *ReadRecurse_V1(std::istream &stream, const Encoding *encoding, FluxionNode *root,
                                       bool readRoot = false);

    static FluxionNode *ReadRecurse_V2(std::istream &stream, const Encoding *encoding, FluxionNode *root,
                                       bool readRoot = false);

    static DataValues *ReadBytesFromType_V1(std::istream &stream, unsigned char valueType, const Encoding *encoding);

    static DataValues *ReadBytesFromType_V2(std::istream &stream, unsigned char valueType, const Encoding *encoding,
                                            bool uniqueFlag);

    static Encoding *GetEncoding(unsigned char id);

    static void WriteArrayWithVarInt(std::ostream &stream, const std::vector<unsigned char> &arr);

    static void WriteVarInt(std::ostream &stream, unsigned int value);

    static void WriteVarLong(std::ostream &stream, unsigned long value);

    static std::vector<unsigned char> DecodeByteArrWithVarInt(std::istream &stream);

    static unsigned int DecodeVarInt(std::istream &stream);

    static unsigned long DecodeVarLong(std::istream &stream);
};

#endif // LIBFLUXION_LIBRARY_H
