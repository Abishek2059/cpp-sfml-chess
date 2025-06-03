#include "game.h"
#include <iostream>


Game::Game(float squareSize)
    : board(squareSize), pieces(squareSize) {
    if (!font.openFromFile("assets/arial.ttf")) {
        std::cerr << "Failed to load font.\n";
    }
}


void Game::handleClick(sf::Vector2i boardPos) {
    if (gameOver) return; // Ignore input if game ended

    // Select a piece
    if (selectedSquare == sf::Vector2i{-1, -1} && pieces.hasPieceAt(boardPos)) {
        if (isCurrentPlayerPiece(boardPos)) {
            selectedSquare = boardPos;
            board.setSelectedSquare(selectedSquare);
        }
    }
    // Attempt a move
    else if (selectedSquare != sf::Vector2i{-1, -1}) {
        bool isWhite = whiteTurn;
        if (pieces.isValidMove(selectedSquare, boardPos) &&
            pieces.isMoveSafe(selectedSquare, boardPos, isWhite)) {

            pieces.movePiece(selectedSquare, boardPos);
            board.setLastMove(selectedSquare, boardPos);
            whiteTurn = !whiteTurn;

            // After move: check for end condition
            if (!hasAnyLegalMove(whiteTurn)) {
                bool inCheck = pieces.isKingInCheck(whiteTurn);
                gameOver = true;
                gameResult = inCheck
                    ? (whiteTurn ? "Black wins by checkmate" : "White wins by checkmate")
                    : "Stalemate";
            }
        }

        selectedSquare = { -1, -1 };
        board.setSelectedSquare(selectedSquare);
    }
}

bool Game::isCurrentPlayerPiece(sf::Vector2i pos) const {
    const Piece* piece = pieces.getPieceAt(pos);
    if (!piece) return false;

    return (whiteTurn && piece->type.find("white") == 0) ||
           (!whiteTurn && piece->type.find("black") == 0);
}

bool Game::hasAnyLegalMove(bool isWhite) const {
    for (int y1 = 0; y1 < 8; ++y1) {
        for (int x1 = 0; x1 < 8; ++x1) {
            sf::Vector2i from(x1, y1);
            const Piece* piece = pieces.getPieceAt(from);
            if (!piece) continue;

            if (isWhite && piece->type.find("white") == std::string::npos) continue;
            if (!isWhite && piece->type.find("black") == std::string::npos) continue;

            for (int y2 = 0; y2 < 8; ++y2) {
                for (int x2 = 0; x2 < 8; ++x2) {
                    sf::Vector2i to(x2, y2);
                    if (from == to) continue;

                    if (pieces.isValidMove(from, to) &&
                        pieces.isMoveSafe(from, to, isWhite)) {
                        return true; // Found at least one legal move
                    }
                }
            }
        }
    }
    return false;
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(board, states);
    target.draw(pieces, states);

if (gameOver) {
    sf::Text text(font, gameResult, 28);
    text.setFillColor(sf::Color(248, 248, 255, 255)); // Hint of blue
    text.setStyle(sf::Text::Bold);

    sf::FloatRect bounds = text.getLocalBounds();

    // Calculate a virtual background position to center the text (512x512 window)
    sf::Vector2f centerPos(
        (512.f - (bounds.size.x + 20.f)) / 2.f,
        (512.f - (bounds.size.y + 20.f)) / 2.f
    );

    // Use background-style offset to correctly align the text
    text.setPosition(centerPos + sf::Vector2f(10.f - bounds.position.x, 10.f - bounds.position.y));

    target.draw(text, states);
}



}
