#ifndef COLIB_NODE_HPP
#define COLIB_NODE_HPP

#include <memory>
#include <CoLib/UI/Export.hpp>

namespace sf
{
    class Event;
}

namespace co
{

    class Node;
    using SharedNode = std::shared_ptr<Node>;

    class COLIB_UI_API Node
    {

    public:
        virtual Node *getParent() const = 0;
        virtual szt getChildCount() const = 0;
        virtual SharedNode getChild(szt index) const = 0;

        void attach(Node *parent);
        void detach();
        void append(const SharedNode &child);
        void remove(const SharedNode &child);

        virtual bool dispatchEvent(Node *target, const sf::Event &event);
        virtual bool bubbleEvent(Node *target, const sf::Event &event);
        virtual bool handleEvent(Node *target, const sf::Event &event);

        Node();
        virtual ~Node();

    protected:
        virtual void onAttach(Node *parent) = 0;
        virtual void onDetach() = 0;
        virtual void onAppend(const SharedNode &child) = 0;
        virtual void onRemove(const SharedNode &child) = 0;

        virtual bool dispatchChildrenEvents(Node *target, const sf::Event &event) const = 0;
    };

    //////////////////////////////////////////////////////////////

    class COLIB_UI_API RootNode
        : public virtual Node
    {
    public:
        Node *getParent() const override;

        RootNode();
        virtual ~RootNode();

    protected:
        void onAttach(Node *parent) override;
        void onDetach() override;
    };

    //////////////////////////////////////////////////////////////

    class COLIB_UI_API LeafNode
        : public virtual Node
    {
    public:
        szt getChildCount() const override;
        SharedNode getChild(szt index = 0) const override;

        LeafNode();
        virtual ~LeafNode();

    protected:
        void onAppend(const SharedNode &child) override;
        void onRemove(const SharedNode &child) override;

        bool dispatchChildrenEvents(Node *target, const sf::Event &event) const override;
    };

}

#endif // COLIB_NODE_HPP