#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

int main()
{

    sf::Image image;
    if (!image.loadFromFile("./res/avatar.jpg"))
    {
        std::cout << "Error on image loading\n";
        return -1;
    }

    sf::Texture texture;
    if (!texture.loadFromImage(image))
    {
        std::cout << "Error on texture loading\n";
        return -1;
    }

    sf::RectangleShape shape;
    shape.setSize({200, 200});
    shape.setTexture(&texture);

    sf::Font font;
    if (!font.loadFromFile("./res/grandview.ttf"))
    {
        std::cout << "Error on font loading\n";
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("It Works");

    sf::Music music;
    if (!music.openFromFile("./res/canon_like.ogg"))
    {
        std::cout << "Error on music loading\n";
        return -1;
    }
    music.setLoop(true);

    sf::Http::Request request;
    request.setMethod(sf::Http::Request::Get);
    request.setUri("features.php");

    sf::Http http;
    http.setHost("http://www.sfml-dev.org");
    auto response = http.sendRequest(request, sf::seconds(10));
    if (response.getStatus() > 400)
    {
        std::cout << "Error on retrieve request (code " << response.getStatus() << ")\n";
        return -1;
    }
    std::cout << response.getBody() << "\n";

    sf::RenderWindow window({640, 480}, "My Window");
    music.play();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        window.draw(shape);
        window.draw(text);
        window.display();
    }

    return 0;
}