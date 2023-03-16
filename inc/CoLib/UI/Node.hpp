#ifndef COLIB_NODE_HPP
#define COLIB_NODE_HPP

#include <functional>
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

    ////////////////////////////////////////

    class COLIB_UI_API Node
    {

    public:
        using EventListener = std::function<void(Node &, const sf::Event &)>;

        virtual Node *getParent() const;
        virtual szt getChildCount() const;
        virtual SharedNode getChild(szt index) const;

        void append(const SharedNode &node);
        void remove(const SharedNode &node);

        virtual bool dispatchEvent(Node *target, const sf::Event &event);
        virtual bool bubbleEvent(Node *target, const sf::Event &event);
        virtual bool handleEvent(Node *target, const sf::Event &event);

        Node(const Node &other) = delete;

        Node();
        virtual ~Node();

        static const SharedNode NoNode;

    protected:
        virtual void onAttach(Node *parent);
        virtual void onDetach();
        virtual void onAppend(const SharedNode &node);
        virtual void onRemove(const SharedNode &node);

    private:
        void attach(Node *parent);
        void detach();
    };

}

#endif // COLIB_NODE_HPP