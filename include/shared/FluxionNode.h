//

// Created by haltroy on 01.05.2024.

//

#ifndef FLUXIONNODE_H

#define FLUXIONNODE_H

#include "DataValues.h"
#define FLUXION_VERSION 2
#include <algorithm>

#include "FluxionException.h"

class FluxionAttribute
{
public:
    FluxionAttribute() {}
    FluxionAttribute(DataValues *value);
    FluxionAttribute(const std::string name, DataValues *value);
    std::string Name;
    DataValues *Value = new NullValue;
};

class FluxionNode
{
public:
    FluxionNode();
    explicit FluxionNode(FluxionNode *parent);
    FluxionNode(FluxionNode *parent, const std::vector<FluxionNode *> &nodes);
    FluxionNode(FluxionNode *parent, const std::vector<FluxionAttribute *> &attributes);
    FluxionNode(FluxionNode *parent, DataValues *value);
    FluxionNode(FluxionNode *parent, const std::string name, DataValues *value);
    FluxionNode(FluxionNode *parent, const std::string name, DataValues *value, const std::vector<FluxionNode *> &nodes);
    FluxionNode(FluxionNode *parent, const std::string name, DataValues *value, const std::vector<FluxionAttribute *> &attributes);
    FluxionNode(FluxionNode *parent, const std::string name, DataValues *value, const std::vector<FluxionNode *> &nodes, const std::vector<FluxionAttribute *> &attributes);

    bool IsRoot;
    FluxionNode *Parent;
    std::vector<FluxionAttribute *> Attributes;

    std::vector<FluxionNode *> GetChildren();

    unsigned char getVersion() const;
    ;

    void setVersion(unsigned char version);

    std::string Name;
    DataValues *Value = new NullValue;

    void Add(FluxionNode *child);

    void AddRange(const std::vector<FluxionNode *> &children);

    bool Remove(FluxionNode *child);

    void Insert(size_t index, FluxionNode *child);

    size_t IndexOf(const FluxionNode *child) const;

    bool Contains(const FluxionNode *child) const;

private:
    unsigned char _version = FLUXION_VERSION;
    std::vector<FluxionNode *> Children;

    static bool CheckIfNewParentIsChildOfNode(FluxionNode *node, FluxionNode *new_parent);
};

#endif // FLUXIONNODE_H
