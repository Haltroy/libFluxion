#ifndef LIBFLUXION_LIBRARY_H
#define LIBFLUXION_LIBRARY_H
#include <istream>
#include <vector>

#include "DataValues.h"
#include "Encodings.h"
#include "FluxionNode.h"

class Fluxion
{
public:
    static void Write(FluxionNode *node, std::ostream *stream, const Encoding *encoding, bool asRoot = true);

    static void Write(FluxionNode *node, const std::string &fileName, const Encoding *encoding);

    static FluxionNode *Read(std::istream &stream);

    static FluxionNode *Read(const std::string &fileName);

private:
    static FluxionNode *ReadRecurse(std::istream &stream, const Encoding *encoding, FluxionNode *root,
                                    bool readRoot = false);

    static DataValues *ReadBytesFromType(std::istream &stream, unsigned char valueType, const Encoding *encoding);

    static Encoding *GetEncoding(unsigned char id);

    static void WriteArrayWithVarInt(std::ostream &stream, const std::vector<unsigned char> &arr);
    static void WriteVarInt(std::ostream &stream, unsigned int value);

    static std::vector<unsigned char> DecodeByteArrWithVarInt(std::istream &stream);
    static unsigned int DecodeVarInt(std::istream &stream);
};

#endif // LIBFLUXION_LIBRARY_H
