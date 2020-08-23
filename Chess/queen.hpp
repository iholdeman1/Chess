//
//  queen.hpp
//  Chess
//
//  Created by Ian Holdeman on 8/9/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#ifndef queen_h
#define queen_h

// Local Includes
#include "piece.hpp"

class Queen : public Piece
{
public:
  Queen(const glm::vec2 position, const glm::vec2 size, const Color game_color,
        Texture2D texture, const glm::vec3 color = glm::vec3(1.0))
  : Piece(std::move(position), std::move(size), std::move(game_color), std::move(texture), std::move(color))
  {
  }
  
  std::vector<std::pair<uint8_t, uint8_t>> calculate_possible_moves(const std::vector<std::vector<int8_t>>& board)
  {
    std::vector<std::pair<uint8_t, uint8_t>> moves;
    const uint8_t x = position_.x / 100;
    const uint8_t y = position_.y / 100;
    
    moves = calcules_moves_in_a_direction(std::move(moves), Direction::UP, x, y, board);
    moves = calcules_moves_in_a_direction(std::move(moves), Direction::UP_RIGHT, x, y, board);
    moves = calcules_moves_in_a_direction(std::move(moves), Direction::RIGHT, x, y, board);
    moves = calcules_moves_in_a_direction(std::move(moves), Direction::DOWN_RIGHT, x, y, board);
    moves = calcules_moves_in_a_direction(std::move(moves), Direction::DOWN, x, y, board);
    moves = calcules_moves_in_a_direction(std::move(moves), Direction::DOWN_LEFT, x, y, board);
    moves = calcules_moves_in_a_direction(std::move(moves), Direction::LEFT, x, y, board);
    moves = calcules_moves_in_a_direction(std::move(moves), Direction::UP_LEFT, x, y, board);
        
    return moves;
  }
};

#endif /* queen_h */
