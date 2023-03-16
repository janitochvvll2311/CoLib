#include <iostream>
#include <SFML/Graphics.hpp>
#include <CoLib/UI/AnchorLayout.hpp>
#include <CoLib/UI/Background.hpp>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/LinearLayout.hpp>
#include <CoLib/UI/Label.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/Button.hpp>
#include <CoLib/UI/Input.hpp>
#include <CoLib/UI/Image.hpp>

sf::Font font;
sf::Texture texture;

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

auto makeLabel(const sf::String &text)
{
    auto label = std::make_shared<co::Label>();
    label->setBackground(makeBackground(sf::Color::Red));
    label->getSpan()->getText().setFont(font);
    label->getSpan()->getText().setString(text);
    return label;
}

auto makeButton(const sf::String &text)
{
    auto button = std::make_shared<co::Button>();
    button->setBackground(makeBackground(sf::Color(200, 200, 200, 255)));
    button->getSpan()->getText().setFont(font);
    button->getSpan()->getText().setString(text);
    button->setMaxWidth(0);
    button->setMaxHeight(0);
    button->setMargin(5);
    button->setPadding({20, 10});
    return button;
}

auto makeImage()
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

auto makeInput()
{
    auto input = std::make_shared<co::Input>();
    input->setBackground(makeBackground(sf::Color::Yellow));
    input->getSpan()->getText().setFont(font);
    input->getSpan()->getText().setFillColor(sf::Color::Black);
    input->getSpan()->getText().setString("Prevent space");
    input->setMinWidth(100);
    input->setPadding({20, 10});
    input->setMinHeight(10);
    input->setMaxWidth(0);
    input->setMaxHeight(0);
    return input;
}

auto makeSideMenu()
{
    auto layout = std::make_shared<co::LinearLayout>();
    layout->setBackground(makeBackground(sf::Color::Yellow));
    layout->setOrientation(co::LinearLayout::Vertical);
    auto image = makeImage();
    layout->append(image);
    layout->setAnchor(image, co::LinearLayout::Center);
    auto b1 = makeButton("Action A");
    b1->setOnClickListener([](auto &node, auto &event)
                           { std::cout << "Clicked A\n"; });
    layout->append(b1);
    layout->setAnchor(b1, co::LinearLayout::Center);
    auto b2 = makeButton("Action B");
    b2->setOnClickListener([](auto &node, auto &event)
                           { std::cout << "Clicked B\n"; });
    layout->append(b2);
    layout->setAnchor(b2, co::LinearLayout::Center);
    auto b3 = makeButton("Action C");
    b3->setOnClickListener([](auto &node, auto &event)
                           { std::cout << "Clicked C\n"; });
    layout->append(b3);
    layout->setAnchor(b3, co::LinearLayout::Center);
    return layout;
}

auto makeBody()
{
    auto layout = std::make_shared<co::LinearLayout>();
    layout->setBackground(makeBackground(sf::Color::Magenta));
    auto side = makeSideMenu();
    layout->append(side);
    layout->setWeight(side, 0.2);

    auto content = std::make_shared<co::FrameLayout>();
    auto input = makeInput();
    content->append(input);
    content->setHorizontalAnchor(input, co::LinearLayout::Center);
    content->setVerticalAnchor(input, co::LinearLayout::Center);

    layout->append(content);
    layout->setWeight(content, 0.8);
    return layout;
}

int main()
{

    sf::RenderWindow window({640, 480}, "My Window");
    window.setFramerateLimit(60);
    auto wsize = sf::Vector2f(window.getSize());

    auto _ = font.loadFromFile("./res/grandview.ttf");
    _ = texture.loadFromFile("./res/avatar.jpg");

    co::LinearLayout layout;
    layout.setBackground(makeBackground(sf::Color::White));
    layout.setOrientation(co::LinearLayout::Vertical);

    auto header = makeLabel("My Title");
    header->setHorizontalContentAnchor(co::Label::Center);
    header->setVerticalContentAnchor(co::Label::Center);
    layout.append(header);
    layout.setWeight(header, 0.2);

    auto body = makeBody();
    layout.append(body);
    layout.setWeight(body, 0.8);

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
                auto cursor = sf::Vector2f(sf::Mouse::getPosition(window));
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