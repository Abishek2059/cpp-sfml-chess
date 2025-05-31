#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include "piece.h"

class Pieces : public sf::Drawable {
public:
    Pieces(float squareSize = 64.f);

private:
    float squareSize;
    std::unordered_map<std::string, sf::Texture> textures;
    std::vector<Piece> pieces;

    void loadTextures();
    void setupBoard();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
