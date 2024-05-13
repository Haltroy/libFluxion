//
// Created by haltroy on 02.05.2024.
//
#include "shared/FluxionNode.h"

FluxionAttribute::FluxionAttribute(DataValues *value) : Name(nullptr), Value(value) {}
FluxionAttribute::FluxionAttribute(const std::string name, DataValues *value) : Name(std::move(name)), Value(value) {}

FluxionNode::FluxionNode() : IsRoot(false), Parent(nullptr)
{
}

FluxionNode::FluxionNode(FluxionNode *parent) : IsRoot(false), Parent(parent)
{
}

FluxionNode::FluxionNode(FluxionNode *parent, const std::vector<FluxionNode *> &nodes) : IsRoot(false), Parent(parent)
{
    for (FluxionNode *node : nodes)
    {
        node->Parent = parent;
    }
    Children.insert(Children.end(), nodes.begin(), nodes.end());
}

FluxionNode::FluxionNode(FluxionNode *parent, const std::vector<FluxionAttribute *> &attributes) : IsRoot(false),
                                                                                                   Parent(parent)
{
    Attributes.insert(Attributes.end(), attributes.begin(), attributes.end());
}

FluxionNode::FluxionNode(FluxionNode *parent, std::string name, DataValues *value) : IsRoot(false), Parent(parent), Name(std::move(name)), Value(value)
{
}

std::vector<FluxionNode *> FluxionNode::GetChildren()
{
    return Children;
}

unsigned char FluxionNode::getVersion() const { return _version; }

void FluxionNode::setVersion(const unsigned char version)
{
    if (IsRoot)
    {
        _version = version;
    }
}

void FluxionNode::Add(FluxionNode *child)
{
    if (child == this || CheckIfNewParentIsChildOfNode(child, this))
        throw FluxionParentException();
    child->Parent = this;
    Children.push_back(child);
}

void FluxionNode::AddRange(const std::vector<FluxionNode *> &children)
{
    for (const auto node : children)
    {
        if (node == this || CheckIfNewParentIsChildOfNode(node, this))
            throw FluxionParentException();
        node->Parent = this;
    }
    Children.insert(Children.end(), children.begin(), children.end());
}

bool FluxionNode::Remove(FluxionNode *child)
{
    if (child->Parent == this)
    {
        child->Parent = nullptr;
        const auto it = std::find_if(Children.begin(), Children.end(),
                                     [&](const FluxionNode *child1)
                                     { return child1 == child; });
        if (it != Children.end())
        {
            Children.erase(it);
            return true;
        }
    }
    return false;
}

void FluxionNode::Insert(const size_t index, FluxionNode *child)
{
    if (index < Children.size())
    {
        if (child == this || CheckIfNewParentIsChildOfNode(child, this))
            throw FluxionParentException();
        child->Parent = this;
        Children.insert(Children.begin() + static_cast<ptrdiff_t>(index), child);
    }
}

size_t FluxionNode::IndexOf(const FluxionNode *child) const
{
    const auto it = std::find_if(Children.begin(), Children.end(),
                                 [&](const FluxionNode *child1)
                                 { return child1 == child; });
    if (it != Children.end())
    {
        return std::distance(Children.begin(), it);
    }
    return -1;
}

bool FluxionNode::Contains(const FluxionNode *child) const
{
    return std::find_if(Children.begin(), Children.end(),
                        [&](const FluxionNode *child1)
                        { return child1 == child; }) != Children.end();
}

bool FluxionNode::CheckIfNewParentIsChildOfNode(FluxionNode *node, FluxionNode *new_parent)
{
    auto children = node->GetChildren();
    if (children.empty())
        return false;
    if (node->Contains(new_parent))
        return true;
    for (const auto child : children)
        return CheckIfNewParentIsChildOfNode(child, new_parent);
    return false;
}
