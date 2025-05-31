#pragma once
#include <SFML/Graphics.hpp>

struct Piece {
    std::string type;
    sf::Vector2i boardPosition;
    sf::Sprite sprite;

    Piece(const std::string& type, const sf::Vector2i& pos, const sf::Texture& texture)
        : type(type), boardPosition(pos), sprite(texture) {}
};
