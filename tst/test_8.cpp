#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/UI/Thickness.hpp>
#include <CoLib/UI/Background.hpp>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/LinearLayout.hpp>
#include <CoLib/UI/VirtualLayout.hpp>
#include <CoLib/UI/Label.hpp>

auto makeBackground(const sf::Color &color)
{
    auto background = std::make_shared<co::Background>();
    background->getGraph().setColor(color);
    return background;
}

auto makeBlock(const sf::Color &color)
{
    auto block = std::make_shared<co::Block>();
    block->setBackground(makeBackground(color));
    block->setMinWidth(100);
    block->setMinHeight(100);
    block->setMaxWidth(0);
    block->setMaxHeight(0);
    block->setMargin(10);
    return block;
}

class Label : public co::Label
{

public:
    bool handleEvent(Node *target, const sf::Event &event) override
    {
        if (!target && event.type == sf::Event::MouseButtonPressed)
        {
            if (contains({float(event.mouseButton.x), float(event.mouseButton.y)}))
            {
                std::cout << "Clicked\n";
                return true;
            }
        }
        return false;
    }
};

auto makeLabelButton(const sf::Font &font)
{
    auto label = std::make_shared<Label>();
    label->setBackground(makeBackground(sf::Color::Cyan));
    label->setMargin(10);
    label->setPadding(10);

    label->getSpan()->getText().setFont(font);
    label->getSpan()->getText().setString("It Works");
    label->getSpan()->getText().setFillColor(sf::Color::Red);
    label->setHorizontalContentAnchor(co::Label::Center);
    label->setVerticalContentAnchor(co::Label::Center);
    return label;
}

auto makeLinear(const sf::Color &color, const sf::Font &font)
{
    auto linear = std::make_shared<co::LinearLayout>();
    linear->setBackground(makeBackground(color));
    linear->setOrientation(co::LinearLayout::Vertical);
    linear->setMargin(10);
    linear->setPadding(10);
    linear->append(makeLabelButton(font));
    linear->append(makeLabelButton(font));
    linear->append(makeLabelButton(font));
    return linear;
}

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    auto wsize = sf::Vector2f(window.getSize());

    sf::Font font;
    auto _ = font.loadFromFile("./res/grandview.ttf");

    auto _layout = makeLinear(sf::Color::White, font);
    auto &layout = *_layout;

    layout.compact();
    layout.inflate(wsize);
    layout.invalidate();

    sf::Transformable transformable;

    while (window.isOpen())
    {
        auto cursor = sf::Vector2f(sf::Mouse::getPosition(window));
        sf::Event event;
        while (window.pollEvent(event))
        {
            layout.handleEvent(nullptr, event);
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                wsize = sf::Vector2f(window.getSize());
                window.setView(sf::View(sf::FloatRect({0, 0}, wsize)));
                layout.compact();
                layout.inflate(wsize);
                layout.invalidate();
                break;
            case sf::Event::MouseButtonPressed:
                layout.compact();
                layout.inflate(cursor);
                layout.invalidate();
                break;
            }
        }

        window.clear();
        window.draw(layout);
        window.display();
    }

    return 0;
}