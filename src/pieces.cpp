#include "pieces.h"
#include <iostream>
#include <algorithm>

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

bool Pieces::hasPieceAt(sf::Vector2i pos) const {
    for (const auto& piece : pieces) {
        if (piece.boardPosition == pos)
            return true;
    }
    return false;
}

const Piece* Pieces::getPieceAt(sf::Vector2i pos) const {
    for (const auto& piece : pieces) {
        if (piece.boardPosition == pos)
            return &piece;
    }
    return nullptr;
}

bool Pieces::isSameColor(sf::Vector2i from, sf::Vector2i to) const {
    const Piece* a = getPieceAt(from);
    const Piece* b = getPieceAt(to);
    if (!a || !b) return false;

    return a->type.substr(0, 5) == b->type.substr(0, 5);  // compare "white" or "black"
}
bool Pieces::isKingInCheck(bool isWhite) const {
    // 1. Find the king’s position
    sf::Vector2i kingPos = {-1, -1};
    std::string kingType = isWhite ? "white_king" : "black_king";

    for (const auto& piece : pieces) {
        if (piece.type == kingType) {
            kingPos = piece.boardPosition;
            break;
        }
    }

    

    // 2. Check all enemy pieces to see if any can attack the king
    std::string enemyPrefix = isWhite ? "black" : "white";

    for (const auto& piece : pieces) {
        if (piece.type.substr(0, 5) == enemyPrefix) {
            if (isValidMove(piece.boardPosition, kingPos)) {
                return true;  // The king is under attack
            }
        }
    }

    return false;  // The king is safe
}
bool Pieces::isMoveSafe(sf::Vector2i from, sf::Vector2i to, bool isWhite) const {
    Pieces temp = *this;
    temp.movePiece(from, to);
    return !temp.isKingInCheck(isWhite);
}



bool Pieces::isValidMove(sf::Vector2i from, sf::Vector2i to) const {
    const Piece* piece = getPieceAt(from);
    if(!piece) return false;
    if(isSameColor(from, to)) return false;

    const std::string& type = piece->type;
    bool isWhite = type.substr(0, 5) == "white";

    //check for pawn
    if(type.find("pawn") != std::string::npos){

        //dx:horizontal movement. if dx == 0 (straight move, no capture) dx == 1(diagonal)
        int dx = to.x - from.x;
        //dy:vertical movement. for black moving down(up for black) is +1 and -1 for white 
        int dy = to.y - from.y;
        //forward movement is -1 for white and 1 for black;
        int forward = isWhite ? -1 : 1;
        int startrow = isWhite ? 6 : 1;

        // moving 1 step forward without capture from anywhere if no piece at destination
        if(dx == 0 && dy == forward && !hasPieceAt(to)){
           return true;

        }
        //move 2 step forward if at startrow and no piece inbetween
        if(dx == 0 && dy == 2*forward && from.y == startrow 
            && !hasPieceAt({from.x, from.y+forward}) && !hasPieceAt(to)){
            return true;

        }
        if(abs(dx) == 1 && dy == forward && hasPieceAt(to)){
            return true;

        }
        return false;
    }
    else if(type.find("bishop") != std::string::npos){
        int dx = to.x - from.x;
        int dy = to.y - from.y;

        if(abs(dx) != abs(dy)) return false;  //must move diagonally
        
        // Determine direction of movement in x and y
        // Example: moving right = +1, left = -1
        int stepX = (dx > 0) ? 1 : -1;
        int stepY = (dy > 0) ? 1 : -1;

        // Start checking the squares one step at a time from the starting position
        int x = from.x + stepX;
        int y = from.y + stepY;


          //  Loop through every square on the diagonal path (excluding the destination)
        while (x != to.x && y != to.y) {
            if (hasPieceAt({x, y})) {
                // If any square along the path is occupied, bishop can't move there
                return false;
            }
            // Move one step diagonally
            x += stepX;
            y += stepY;
        }
        return true;



    }
    else if(type.find("rook") != std::string::npos) {
        int dx = to.x - from.x;
        int dy = to.y - from.y;

        // Rook must move in a straight line: either horizontal or vertical
        if (dx != 0 && dy != 0) return false;

        // Step direction for x and y
        int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);  // horizontal movement (if any)
        int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);  // vertical movement (if any)

        // Start at the first square in the direction of movement
        int x = from.x + stepX;
        int y = from.y + stepY;

        // 🧱 Check all squares between from and to (excluding destination)
        while (x != to.x || y != to.y) {
            if (hasPieceAt({x, y})) {
                return false;  // Blocked by a piece in the way
            }
            x += stepX;
            y += stepY;
        }

        // 🟢 If path is clear and destination is empty or has enemy piece, it's valid
        return true;

    }
    else if(type.find("queen") != std::string::npos) {
        int dx = to.x - from.x;
        int dy = to.y - from.y;

        // ♝ Diagonal movement (bishop-like)
        if (abs(dx) == abs(dy)) {
            int stepX = (dx > 0) ? 1 : -1;
            int stepY = (dy > 0) ? 1 : -1;

            int x = from.x + stepX;
            int y = from.y + stepY;

            while (x != to.x && y != to.y) {
                if (hasPieceAt({x, y})) return false;  // Blocked
                x += stepX;
                y += stepY;
            }

            return true;
          // Clear path, valid diagonal
        }

        // ♜ Straight movement (rook-like)
        if (dx == 0 || dy == 0) {
            int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
            int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);

            int x = from.x + stepX;
            int y = from.y + stepY;

            while (x != to.x || y != to.y) {
                if (hasPieceAt({x, y})) return false;  // Blocked
                x += stepX;
                y += stepY;
            }

            return true;
              // Clear path, valid straight
        }

        //not a valid rook or bishop move
        return false;
    }
    else if(type.find("knight") != std::string::npos){
        int dx = to.x - from.x;
        int dy = to.y - from.y;

        // List of all 8 valid knight moves
        std::vector<sf::Vector2i> knightMoves = {
            { -2, -1 }, { -2, +1 },
            { -1, -2 }, { -1, +2 },
            { +1, -2 }, { +1, +2 },
            { +2, -1 }, { +2, +1 }
        };

        for(const auto& move: knightMoves){
            if(dx == move.x && dy == move.y){
                return true;

            }
        }
        return false;

    }
    else if (type.find("king") != std::string::npos) {
        int dx = abs(to.x - from.x);
        int dy = abs(to.y - from.y);

        // Can move only 1 square in any direction
        if (dx <= 1 && dy <= 1) {
            return true;

        }

        return false;
    }
    return false;
    
}

void Pieces::movePiece(sf::Vector2i from, sf::Vector2i to) {

    pieces.erase(
        std::remove_if(pieces.begin(), pieces.end(), [&](const Piece& p) {
            return p.boardPosition == to;
        }),
        pieces.end()
    );


    for (auto& piece : pieces) {
        if (piece.boardPosition == from) {
            piece.boardPosition = to;
            piece.sprite.setPosition(sf::Vector2f(to.x * squareSize + 2.f, to.y * squareSize + 2.f));
            break;
        }
    }

    // // Optional: remove captured piece
    // pieces.erase(std::remove_if(pieces.begin(), pieces.end(), [&](const Piece& p) {
    //     return p.boardPosition == to && p.boardPosition != from;
    // }), pieces.end());
}

void Pieces::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& piece : pieces) {
        target.draw(piece.sprite, states);
    }
}
