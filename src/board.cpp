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

void Board::selectSquareAt(sf::Vector2i mousePos){
    int col = mousePos.x/(int)squareSize;
    int row = mousePos.y/(int)squareSize;
    if((col >= 0 && col < 8) && (row >=0 && row < 8)){
        selectedIndex = row*8+col;
    }
    else selectedIndex = -1;
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& square : squares) {
        target.draw(square, states);
    }
    if (selectedIndex >= 0 && selectedIndex < (int)squares.size()) {
        sf::RectangleShape highlight(sf::Vector2f(squareSize, squareSize));
        highlight.setPosition(squares[selectedIndex].getPosition());
        highlight.setFillColor(sf::Color(100,149,237,150));
        target.draw(highlight, states);
    }
}
