#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Board : public sf::Drawable {
public:
    Board(float squareSize = 64.f);
    void setSelectedSquare(sf::Vector2i pos);     // highlight selected piece
    void setLastMove(sf::Vector2i from, sf::Vector2i to); // highlight last move

private:
    std::vector<sf::RectangleShape> squares;
    float squareSize;
    sf::Vector2i lastFrom = {-1, -1}, lastTo = {-1, -1};
    sf::Vector2i selectedSquare = {-1, -1};
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
