#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include "piece.h"

class Pieces : public sf::Drawable {
public:
    // Constructor
    explicit Pieces(float squareSize = 64.f);

    // Gameplay Interface
    bool hasPieceAt(sf::Vector2i pos) const;
    const Piece* getPieceAt(sf::Vector2i pos) const;
    bool isSameColor(sf::Vector2i from, sf::Vector2i to) const;
    bool isValidMove(sf::Vector2i from, sf::Vector2i to) const;
    void movePiece(sf::Vector2i from, sf::Vector2i to);

    // Game Rules
    bool isKingInCheck(bool isWhite) const;
    bool isMoveSafe(sf::Vector2i from, sf::Vector2i to, bool isWhite) const;

private:
    float squareSize;
    std::unordered_map<std::string, sf::Texture> textures;
    std::vector<Piece> pieces;

    // Internal Setup
    void loadTextures();
    void setupBoard();

    // SFML drawing
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
