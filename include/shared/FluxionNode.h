//

// Created by haltroy on 01.05.2024.

//

#ifndef FLUXIONNODE_H

#define FLUXIONNODE_H

#include "DataValues.h"
#define FLUXION_VERSION 2

#include "FluxionAttribute.h"
#include "FluxionException.h"


class FluxionNode
{
public:
    FluxionNode();
    explicit FluxionNode(FluxionNode* parent);
    FluxionNode(FluxionNode* parent, const std::vector<FluxionNode*>& nodes);
    FluxionNode(FluxionNode* parent, const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, nullptr_t value);
    FluxionNode(FluxionNode* parent, bool value);
    FluxionNode(FluxionNode* parent, unsigned char value);
    FluxionNode(FluxionNode* parent, signed char value);
    FluxionNode(FluxionNode* parent, char16_t value);
    FluxionNode(FluxionNode* parent, short value);
    FluxionNode(FluxionNode* parent, unsigned short value);
    FluxionNode(FluxionNode* parent, int value);
    FluxionNode(FluxionNode* parent, unsigned int value);
    FluxionNode(FluxionNode* parent, long value);
    FluxionNode(FluxionNode* parent, unsigned long value);
    FluxionNode(FluxionNode* parent, float value);
    FluxionNode(FluxionNode* parent, double value);
    FluxionNode(FluxionNode* parent, std::vector<unsigned char> value);
    FluxionNode(FluxionNode* parent, std::string value);
    FluxionNode(FluxionNode* parent, std::string name, nullptr_t value);
    FluxionNode(FluxionNode* parent, std::string name, bool value);
    FluxionNode(FluxionNode* parent, std::string name, unsigned char value);
    FluxionNode(FluxionNode* parent, std::string name, signed char value);
    FluxionNode(FluxionNode* parent, std::string name, char16_t value);
    FluxionNode(FluxionNode* parent, std::string name, short value);
    FluxionNode(FluxionNode* parent, std::string name, unsigned short value);
    FluxionNode(FluxionNode* parent, std::string name, int value);
    FluxionNode(FluxionNode* parent, std::string name, unsigned int value);
    FluxionNode(FluxionNode* parent, std::string name, long value);
    FluxionNode(FluxionNode* parent, std::string name, unsigned long value);
    FluxionNode(FluxionNode* parent, std::string name, float value);
    FluxionNode(FluxionNode* parent, std::string name, double value);
    FluxionNode(FluxionNode* parent, std::string name, std::vector<unsigned char> value);
    FluxionNode(FluxionNode* parent, std::string name, std::string value);
    FluxionNode(FluxionNode* parent, std::string name, nullptr_t value, const std::vector<FluxionNode*>& nodes);
    FluxionNode(FluxionNode* parent, std::string name, bool value, const std::vector<FluxionNode*>& nodes);
    FluxionNode(FluxionNode* parent, std::string name, unsigned char value, const std::vector<FluxionNode*>& nodes);
    FluxionNode(FluxionNode* parent, std::string name, signed char value, const std::vector<FluxionNode*>& nodes);
    FluxionNode(FluxionNode* parent, std::string name, char16_t value, const std::vector<FluxionNode*>& nodes);
    FluxionNode(FluxionNode* parent, std::string name, short value, const std::vector<FluxionNode*>& nodes);
    FluxionNode(FluxionNode* parent, std::string name, unsigned short value, const std::vector<FluxionNode*>& nodes);
    FluxionNode(FluxionNode* parent, std::string name, int value, const std::vector<FluxionNode*>& nodes);
    FluxionNode(FluxionNode* parent, std::string name, unsigned int value, const std::vector<FluxionNode*>& nodes);
    FluxionNode(FluxionNode* parent, std::string name, long value, const std::vector<FluxionNode*>& nodes);
    FluxionNode(FluxionNode* parent, std::string name, unsigned long value, const std::vector<FluxionNode*>& nodes);
    FluxionNode(FluxionNode* parent, std::string name, float value, const std::vector<FluxionNode*>& nodes);
    FluxionNode(FluxionNode* parent, std::string name, double value, const std::vector<FluxionNode*>& nodes);
    FluxionNode(FluxionNode* parent, std::string name, std::vector<unsigned char> value,
                const std::vector<FluxionNode*>& nodes);
    FluxionNode(FluxionNode* parent, std::string name, std::string value, const std::vector<FluxionNode*>& nodes);
    FluxionNode(FluxionNode* parent, std::string name, nullptr_t value,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, bool value, const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, unsigned char value,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, signed char value,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, char16_t value,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, short value, const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, unsigned short value,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, int value, const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, unsigned int value,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, long value, const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, unsigned long value,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, float value, const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, double value, const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, std::vector<unsigned char> value,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, std::string value,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, nullptr_t value, const std::vector<FluxionNode*>& nodes,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, bool value, const std::vector<FluxionNode*>& nodes,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, unsigned char value, const std::vector<FluxionNode*>& nodes,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, signed char value, const std::vector<FluxionNode*>& nodes,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, char16_t value, const std::vector<FluxionNode*>& nodes,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, short value, const std::vector<FluxionNode*>& nodes,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, unsigned short value, const std::vector<FluxionNode*>& nodes,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, int value, const std::vector<FluxionNode*>& nodes,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, unsigned int value, const std::vector<FluxionNode*>& nodes,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, long value, const std::vector<FluxionNode*>& nodes,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, unsigned long value, const std::vector<FluxionNode*>& nodes,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, float value, const std::vector<FluxionNode*>& nodes,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, double value, const std::vector<FluxionNode*>& nodes,
                const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, std::vector<unsigned char> value,
                const std::vector<FluxionNode*>& nodes, const std::vector<FluxionAttribute*>& attributes);
    FluxionNode(FluxionNode* parent, std::string name, std::string value, const std::vector<FluxionNode*>& nodes,
                const std::vector<FluxionAttribute*>& attributes);

    bool IsRoot;
    FluxionNode* Parent;
    std::vector<FluxionAttribute*> Attributes;

    std::vector<FluxionNode*> GetChildren();

    unsigned char getVersion() const;

    void setVersion(unsigned char version);

    std::string Name;
    FluxionValue* Value = nullptr;

    void Add(FluxionNode* child);

    void AddRange(const std::vector<FluxionNode*>& children);

    bool Remove(FluxionNode* child);

    void Insert(size_t index, FluxionNode* child);

    size_t IndexOf(const FluxionNode* child) const;

    bool Contains(const FluxionNode* child) const;

private:
    unsigned char _version = FLUXION_VERSION;
    std::vector<FluxionNode*> Children;

    static bool CheckIfNewParentIsChildOfNode(FluxionNode* node, FluxionNode* new_parent);
};

#endif // FLUXIONNODE_H
