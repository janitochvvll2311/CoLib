#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/UI/Thickness.hpp>
#include <CoLib/UI/Background.hpp>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/LinearLayout.hpp>
#include <CoLib/UI/VirtualLayout.hpp>
#include <CoLib/UI/Button.hpp>
#include <CoLib/UI/Image.hpp>
#include <CoLib/UI/Input.hpp>

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

auto makeLinear(const sf::Color &color)
{
    auto linear = std::make_shared<co::LinearLayout>();
    linear->setBackground(makeBackground(color));
    linear->setMargin(10);
    linear->setPadding(10);
    linear->append(makeBlock(sf::Color::Red));
    linear->append(makeBlock(sf::Color::Green));
    linear->append(makeBlock(sf::Color::Blue));
    linear->setMaxWidth(0);
    linear->setMaxHeight(0);
    return linear;
}

auto makeFrame(const sf::Color &color)
{
    auto frame = std::make_shared<co::FrameLayout>();
    frame->setBackground(makeBackground(color));
    frame->setMargin(10);
    frame->setPadding(10);
    frame->append(makeBlock(sf::Color::Red));
    return frame;
}

auto makeLabel(const sf::String &text, const sf::Font &font)
{
    auto label = std::make_shared<co::Label>();
    label->setBackground(makeBackground(sf::Color::Red));
    label->getSpan()->getText().setFont(font);
    label->getSpan()->getText().setString(text);
    return label;
}

auto makeButton(const sf::String &text, const sf::Font &font)
{
    auto button = std::make_shared<co::Button>();
    button->setBackground(makeBackground(sf::Color(200, 200, 200, 255)));
    button->getSpan()->getText().setFont(font);
    button->getSpan()->getText().setString(text);
    button->setMaxWidth(0);
    button->setMaxHeight(0);
    button->setPadding({20, 10});
    return button;
}

auto makeSpan(const sf::String &text, const sf::Font &font)
{
    auto span = std::make_shared<co::Span>();
    span->getText().setFont(font);
    span->getText().setString(text);
    span->getText().setFillColor(sf::Color::Red);
    return span;
}

auto makeImage(const sf::Texture &texture)
{
    auto image = std::make_shared<co::Image>();
    image->setBackground(makeBackground(sf::Color::Red));
    image->setPadding(10);
    image->setMinWidth(100);
    image->setMinHeight(100);
    image->setMaxWidth(0);
    image->setMaxHeight(0);
    image->getImage()->getGraph().setTexture(&texture);
    return image;
}

auto makeInput(const sf::Font &font)
{
    auto input = std::make_shared<co::Input>();
    input->setBackground(makeBackground(sf::Color::Yellow));
    input->getSpan()->getText().setFont(font);
    input->getSpan()->getText().setFillColor(sf::Color::Black);
    input->getSpan()->getText().setString("Prevent space");
    input->setMaxWidth(0);
    return input;
}

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    window.setFramerateLimit(60);
    auto wsize = sf::Vector2f(window.getSize());

    sf::Font font;
    auto _ = font.loadFromFile("./res/grandview.ttf");

    sf::Texture texture;
    _ = texture.loadFromFile("./res/avatar.jpg");

    co::LinearLayout layout;
    layout.setBackground(makeBackground(sf::Color::White));
    layout.setOrientation(co::LinearLayout::Vertical);
    layout.setContentAnchor(co::LinearLayout::Center);

    auto image = makeImage(texture);
    layout.append(image);
    layout.setAnchor(image, co::LinearLayout::Center);

    auto input1 = makeInput(font);
    layout.append(input1);
    layout.setAnchor(input1, co::LinearLayout::Center);

    auto input2 = makeInput(font);
    layout.append(input2);
    layout.setAnchor(input2, co::LinearLayout::Center);

    auto button = makeButton("Change", font);
    button->setOnClickListener(
        [&](auto &widget, auto &event)
        {
            image->setMinWidth(image->getMinWidth() + 10);
            image->invalidate();
        });
    layout.append(button);
    layout.setAnchor(button, co::LinearLayout::Center);

    sf::Transformable transformable;

    while (window.isOpen())
    {
        auto cursor = sf::Vector2f(sf::Mouse::getPosition(window));
        sf::Event event;
        while (window.pollEvent(event))
        {
            layout.dispatchEvent(nullptr, event);
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                wsize = sf::Vector2f(window.getSize());
                window.setView(sf::View(sf::FloatRect({0, 0}, wsize)));
                layout.invalidate();
                break;
            case sf::Event::MouseWheelScrolled:
                button->click();
                break;
            }
        }

        if (!layout.isValid())
        {
            layout.compact();
            layout.inflate(wsize);
        }

        window.clear();
        window.draw(layout);
        window.display();
    }

    return 0;
}