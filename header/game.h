#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "board.h"
#include "pieces.h"

class Game : public sf::Drawable {
public:
    Game(float squareSize);

    void handleClick(sf::Vector2i boardPos);

private:
    Board board;
    Pieces pieces;
    bool whiteTurn = true;

    sf::Vector2i selectedSquare = { -1, -1 };

    // ✅ ADD THESE:
    bool gameOver = false;
    std::string gameResult;
    sf::Font font;

    bool isCurrentPlayerPiece(sf::Vector2i pos) const;
    bool hasAnyLegalMove(bool isWhite) const;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
