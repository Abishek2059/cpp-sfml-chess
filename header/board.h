#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Board : public sf::Drawable {
public:
    Board(float squareSize = 64.f);
    void selectSquareAt(sf::Vector2i mousePos);

private:
    std::vector<sf::RectangleShape> squares;
    float squareSize;
    int selectedIndex = -1;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
