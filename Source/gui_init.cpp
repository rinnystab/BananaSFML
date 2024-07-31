#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
const std::string f_path = "C:\\Windows\\Fonts\\segoeui.ttf";
#elif defined(__linux__)
const std::string f_path = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
#else
#error "Unsupported OS"
#endif

auto main() -> int {

#if defined(_WIN32) || defined(_WIN64)
    HWND hwnd = GetConsoleWindow();
    if (hwnd) {
        ShowWindow(hwnd, SW_HIDE);
    }
#endif //hide the console just for the look
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Banana", sf::Style::Titlebar | sf::Style::Close);
    uint32_t count = 0; // Since it has nothign to do with minus
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile(f_path)) { printf("couldn't find font");  return EXIT_FAILURE; }
    text.setFont(font);
    text.setFillColor(sf::Color::White);

    sf::Texture texture;
    if (!texture.loadFromFile("banana.png")) return EXIT_FAILURE;
    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::Vector2u windowSize = window.getSize();

    sprite.setPosition((window.getSize().x - sprite.getLocalBounds().width) / 2.0f, (window.getSize().y - sprite.getLocalBounds().height) / 2.0f);

    auto updateCounterText = [&text, &window, &count, &sprite]() {
        text.setString(std::to_string(count));
        text.setPosition((window.getSize().x / 2) - (10 * (std::to_string(count).length() - 1)), sprite.getPosition().y - (sprite.getLocalBounds().height / 12));
    };

    updateCounterText();
    sf::Event ev;
    while (window.isOpen())
    {
        sf::Vector2i m_pos = sf::Mouse::getPosition(window);
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed) window.close();
            else if (ev.type == sf::Event::MouseButtonPressed)
            {
                if (ev.mouseButton.button == sf::Mouse::Left)
                {
                    printf("Left click triggered\n");
                    if (sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(m_pos)))
                    {
                        count++;
                        updateCounterText();
                    }
                }
                else if (ev.mouseButton.button == sf::Mouse::Right)
                {
                    printf("Right click triggered\n");
                    //don't know what todo
                }
            }
        }
        window.clear(sf::Color::Color(153, 153, 0));
        
        window.draw(text);
        window.draw(sprite);

        window.display();
    }

    return EXIT_SUCCESS;
}
