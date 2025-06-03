#include <SFML/Graphics.hpp>
#include <optional>
#include "game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({512u, 512u}), "Chess", sf::Style::Titlebar | sf::Style::Close);

    window.setVerticalSyncEnabled(true);

    Game game(64.f);  // Each square is 64x64 pixels

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::MouseButtonPressed>()) {
                const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouse->button == sf::Mouse::Button::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2i boardPos = { mousePos.x / 64, mousePos.y / 64 };
                    game.handleClick(boardPos);
                }
            }
        }

        window.clear();
        window.draw(game);
        window.display();
    }

    return 0;
}
