#define COLIB_UI_EXPORTS
#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/Constants.hpp>
#include <CoLib/UI/Node.hpp>

namespace co
{

    void Node::attach(Node *parent)
    {
        if (getParent() != nullptr)
        {
            throw InvalidOperationException(NODE_ALREADY_ATTACHED_STRING);
        }
        auto _parent = parent;
        while (_parent)
        {
            if (_parent == this)
            {
                throw InvalidOperationException(OWN_ANCESTOR_NODE_STRING);
            }
            _parent = _parent->getParent();
        }
        onAttach(parent);
    }

    void Node::detach()
    {
        if (getParent() == nullptr)
        {
            throw InvalidOperationException(NODE_ALREADY_DETACHED_STRING);
        }
        onDetach();
    }

    void Node::append(const SharedNode &child)
    {
        child->attach(this);
        onAppend(child);
    }

    void Node::remove(const SharedNode &child)
    {
        if (child->getParent() != this)
        {
            throw InvalidOperationException(NODE_ALREADY_ATTACHED_STRING);
        }
        child->detach();
        onRemove(child);
    }

    bool Node::dispatchEvent(Node *target, const sf::Event &event)
    {
        return (dispatchChildrenEvents(target, event) || handleEvent(target, event));
    }

    bool Node::bubbleEvent(Node *target, const sf::Event &event)
    {
        auto parent = getParent();
        return (handleEvent(target, event) || (parent != nullptr && parent->bubbleEvent(target, event)));
    }

    bool Node::handleEvent(Node *target, const sf::Event &event)
    {
        return false;
    }

    void Node::spreadEvent(Node *target, const sf::Event &event)
    {
        auto root = this;
        while (root->getParent())
        {
            root = root->getParent();
        }
        root->dispatchEvent(target, event);
    }

    Node::Node() {}
    Node::~Node() {}

    //////////////////////////////////////////////////////////////////////////////////////

    Node *RootNode::getParent() const
    {
        return nullptr;
    }

    RootNode::RootNode() {}
    RootNode::~RootNode() {}

    void RootNode::onAttach(Node *parent)
    {
        throw InvalidOperationException(PARENT_NODES_NOT_SUPPORTED_STRING);
    }

    void RootNode::onDetach()
    {
        throw InvalidOperationException(PARENT_NODES_NOT_SUPPORTED_STRING);
    }

    //////////////////////////////////////////////////////////////////////////////////

    szt LeafNode::getChildCount() const
    {
        return 0;
    }

    SharedNode LeafNode::getChild(szt index) const
    {
        return nullptr;
    }

    LeafNode::LeafNode() {}
    LeafNode::~LeafNode() {}

    void LeafNode::onAppend(const SharedNode &child)
    {
        throw InvalidOperationException(CHILD_NODES_NOT_SUPPORTED_STRING);
    }

    void LeafNode::onRemove(const SharedNode &child)
    {
        throw InvalidOperationException(CHILD_NODES_NOT_SUPPORTED_STRING);
    }

    bool LeafNode::dispatchChildrenEvents(Node *target, const sf::Event &event) const
    {
        return false;
    }

}