#include "board.h"

Board::Board(float squareSize) : squareSize(squareSize) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
            square.setPosition(sf::Vector2f(col * squareSize, row * squareSize));
            bool isWhite = (row + col) % 2 == 0;
            square.setFillColor(isWhite ? sf::Color(240, 217, 181) : sf::Color(181, 136, 99));
            squares.push_back(square);
        }
    }
}
void Board::setSelectedSquare(sf::Vector2i pos) {
    selectedSquare = pos;
}
void Board::setLastMove(sf::Vector2i from, sf::Vector2i to) {
    lastFrom = from;
    lastTo = to;
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int row = 0; row < 8; ++row) {
    for (int col = 0; col < 8; ++col) {
        sf::RectangleShape square = squares[row * 8 + col];
        sf::Vector2i current(col, row);

        // Highlight last move with translucent blue fill
        if (current == lastFrom || current == lastTo) {
            square.setFillColor(sf::Color(255, 255, 30, 150)); // Sky blue, subtle tint
        }

        // Outline for selected square
        if (current == selectedSquare) {
            square.setFillColor(sf::Color(255, 255, 30, 150)); // Sky blue, subtle tint
        }

        target.draw(square, states);
    }
}

}
