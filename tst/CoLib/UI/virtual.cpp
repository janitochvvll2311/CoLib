#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/Surface.hpp>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/Label.hpp>
#include <CoLib/UI/Button.hpp>
#include <CoLib/UI/Input.hpp>
#include <CoLib/UI/LinearLayout.hpp>
#include <CoLib/UI/VirtualLayout.hpp>
#include <CoLib/UI/Image.hpp>

sf::Font font;
bool _;

class ReactiveSurface : public co::Surface
{

protected:
    bool handleEvent(Node *target, const sf::Event &event) override
    {
        if (contains({float(event.mouseMove.x), float(event.mouseMove.y)}))
        {
            setColor(sf::Color::Green);
            invalidate();
        }
        else
        {
            setColor(sf::Color::Red);
            invalidate();
        }
        return false;
    }
};

auto makeBackground(const sf::Color &color)
{
    auto surface = std::make_shared<co::Surface>();
    surface->setColor(color);
    return surface;
}

auto makeSpan(const sf::String &string, const sf::Color &color)
{
    auto span = std::make_shared<co::Span>();
    span->setFont(font);
    span->setString(string);
    span->setFillColor(color);
    return span;
}

auto makeBlock(const sf::Color &color)
{
    auto block = std::make_shared<co::Block>();
    block->setBackground(makeBackground(color));
    block->setMargin(10);
    block->setPadding(10);
    block->setMinWidth(100);
    block->setMinHeight(100);
    block->setMaxWidth(0);
    block->setMaxHeight(0);
    return block;
}

auto makeFrame(const sf::Color &color, const co::SharedNode &child = nullptr)
{
    auto frame = std::make_shared<co::FrameLayout>();
    frame->setBackground(makeBackground(color));
    frame->setMargin(10);
    frame->setPadding(10);
    frame->setMaxWidth(0);
    frame->setMaxHeight(0);
    if (child)
    {
        frame->append(child);
    }
    return frame;
}

auto makeButton()
{
    auto button = std::make_shared<co::Button>();
    button->setHorizontalContentAnchor(co::Label::Anchor::Center);
    button->setVerticalContentAnchor(co::Label::Anchor::Center);
    button->getBlock().setBackground(std::make_shared<ReactiveSurface>());
    button->getBlock().setMargin(10);
    button->getBlock().setPadding(10);
    button->getSpan().setFont(font);
    button->getSpan().setString("It Works");
    button->getSpan().setFillColor(sf::Color::Black);
    button->setOnClickListener(
        [](auto &node, auto &event)
        {
            std::cout << "Clicked\n";
        });
    return button;
}

auto makeInput()
{
    auto input = std::make_shared<co::Input>();
    input->setHorizontalContentAnchor(co::Label::Anchor::Center);
    input->setVerticalContentAnchor(co::Label::Anchor::Center);
    input->getBlock().setBackground(makeBackground(sf::Color::Yellow));
    input->getBlock().setMargin(10);
    input->getBlock().setPadding(10);
    input->getSpan().setFont(font);
    input->getSpan().setString("It Works");
    input->getSpan().setFillColor(sf::Color::Red);
    input->setOnTextEnteredListener(
        [](auto &node, auto &event)
        {
            co::Input &input = dynamic_cast<co::Input &>(node);
            auto text = input.getSpan().getString().toAnsiString();
            std::cout << "Text entered: " << text << "\n";
        });
    return input;
}

auto makeImage()
{
    auto image = std::make_shared<co::Image>();
    image->setHorizontalContentAnchor(co::Label::Anchor::Center);
    image->setVerticalContentAnchor(co::Label::Anchor::Center);
    image->getBlock().setBackground(makeBackground(sf::Color::Red));
    image->getBlock().setMargin(10);
    image->getBlock().setPadding(10);
    auto texture = std::make_shared<sf::Texture>();
    _ = texture->loadFromFile("./res/avatar.jpg");
    image->getSurface().setTexture(texture);
    image->getSurface().setColor(sf::Color::White);
    return image;
}

auto makeLinear()
{
    auto layout = std::make_shared<co::LinearLayout>();
    layout->setBackground(makeBackground(sf::Color::Cyan));
    layout->setOrientation(co::LinearLayout::Vertical);
    layout->setContentAnchor(co::LinearLayout::Center);
    layout->setMargin(10);
    layout->setPadding(10);

    auto input1 = makeInput();
    layout->append(input1);
    layout->setAnchor(input1, co::LinearLayout::Start);
    layout->setWeight(input1, 0.33);

    auto image1 = makeImage();
    layout->append(image1);
    layout->setAnchor(image1, co::LinearLayout::End);
    layout->setWeight(image1, 0.33);

    auto button1 = makeButton();
    layout->append(button1);
    layout->setAnchor(button1, co::LinearLayout::Center);
    layout->setWeight(button1, 0.33);

    return layout;
}

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    window.setFramerateLimit(30);
    auto wsize = sf::Vector2f(window.getSize());
    _ = font.loadFromFile("./res/grandview.ttf");

    co::VirtualLayout layout;
    layout.setBackground(makeBackground(sf::Color::White));
    layout.setMargin(10);
    layout.setPadding(10);

    auto content = makeLinear();
    layout.append(content);
    layout.setHorizontalAnchor(content, co::VirtualLayout::Center);
    layout.setVerticalAnchor(content, co::VirtualLayout::Center);

    layout.compact();
    layout.inflate(wsize);
    layout.place({0, 0});

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
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Button::Right)
                {
                    layout.compact();
                    layout.inflate(cursor);
                    layout.place({0, 0});
                    layout.update(true);
                }
                break;
            }
        }

        if (!layout.isValid())
        {
            layout.compact();
            layout.inflate(wsize);
            layout.place({0, 0});
        }

        window.clear();
        window.draw(layout);
        window.display();
    }

    return 0;
}