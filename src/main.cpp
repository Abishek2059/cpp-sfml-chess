#include <SFML/Graphics.hpp>
#include <optional>
#include "board.h"
#include "pieces.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({512, 512}), "CHESS", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    float squareSize = 64.f;
    Board board(squareSize);
    Pieces pieces(squareSize);

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (event->is<sf::Event::MouseButtonPressed>()) {
                const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouse->button == sf::Mouse::Button::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    board.selectSquareAt(mousePos);
                }
            }
        }

        window.clear();
        window.draw(board);
        window.draw(pieces);
        window.display();
    }

    return 0;
}
