#include "pieces.h"
#include <iostream>

Pieces::Pieces(float squareSize) : squareSize(squareSize) {
    loadTextures();
    setupBoard();
}

void Pieces::loadTextures() {
    const std::string names[] = {
        "white_pawn", "white_rook", "white_knight", "white_bishop", "white_queen", "white_king",
        "black_pawn", "black_rook", "black_knight", "black_bishop", "black_queen", "black_king"
    };

    for (const auto& name : names) {
        sf::Texture texture;
        if (!texture.loadFromFile("assets/" + name + ".png")) {
            std::cerr << "Failed to load: " << name << ".png\n";
        } else {
            textures[name] = std::move(texture);
        }
    }
}

void Pieces::setupBoard() {
    const std::string layout[8][8] = {
        {"black_rook", "black_knight", "black_bishop", "black_queen", "black_king", "black_bishop", "black_knight", "black_rook"},
        {"black_pawn", "black_pawn", "black_pawn", "black_pawn", "black_pawn", "black_pawn", "black_pawn", "black_pawn"},
        {"", "", "", "", "", "", "", ""},
        {"", "", "", "", "", "", "", ""},
        {"", "", "", "", "", "", "", ""},
        {"", "", "", "", "", "", "", ""},
        {"white_pawn", "white_pawn", "white_pawn", "white_pawn", "white_pawn", "white_pawn", "white_pawn", "white_pawn"},
        {"white_rook", "white_knight", "white_bishop", "white_queen", "white_king", "white_bishop", "white_knight", "white_rook"}
    };

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            const std::string& name = layout[row][col];
            if (name.empty()) continue;

            const sf::Texture& texture = textures.at(name);
            pieces.emplace_back(name, sf::Vector2i(col, row), texture);
            pieces.back().sprite.setPosition(sf::Vector2f(col * squareSize + 2.f, row * squareSize + 2.f));
        }
    }
}

void Pieces::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& piece : pieces) {
        target.draw(piece.sprite, states);
    }
}
