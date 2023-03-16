#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/Node.hpp>

namespace co
{

    Node *Node::getParent() const
    {
        return nullptr;
    }

    szt Node::getChildCount() const
    {
        return 0;
    }

    SharedNode Node::getChild(szt index) const
    {
        return NoNode;
    }

    ////////////////////////////////////////////////////////

    void Node::append(const SharedNode &node)
    {
        node->attach(this);
        onAppend(node);
    }

    void Node::remove(const SharedNode &node)
    {
        onRemove(node);
        node->detach();
    }

    bool Node::dispatchEvent(Node *target, const sf::Event &event)
    {
        return handleEvent(target, event);
    }

    bool Node::bubbleEvent(Node *target, const sf::Event &event)
    {
        auto *parent = getParent();
        return (handleEvent(target, event) || (parent && parent->bubbleEvent(target, event)));
    }

    bool Node::handleEvent(Node *target, const sf::Event &event)
    {
        return false;
    }

    Node::Node() {}
    Node::~Node() {}

    const SharedNode Node::NoNode = nullptr;

    ////////////////////////////////////////////////////////////

    void Node::onAttach(Node *parent)
    {
        throw InvalidOperationException("This node not support parent nodes");
    }

    void Node::onDetach()
    {
        throw InvalidOperationException("This node not support parent nodes");
    }

    void Node::onAppend(const SharedNode &node)
    {
        throw InvalidOperationException("This node not support child nodes");
    }

    void Node::onRemove(const SharedNode &node)
    {
        throw InvalidOperationException("This node not support child nodes");
    }

    ///////////////////////////////////////////////////////////////////////////////////////

    void Node::attach(Node *parent)
    {
        auto _parent = getParent();
        if (_parent)
        {
            throw InvalidOperationException("This node is already attached to another node");
        }
        _parent = parent;
        while (_parent)
        {
            if (_parent == this)
            {
                throw InvalidOperationException("This node is ancestor of the parent node");
            }
            _parent = _parent->getParent();
        }
        onAttach(parent);
    }

    void Node::detach()
    {
        onDetach();
    }

}