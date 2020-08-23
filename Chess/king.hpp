//
//  king.hpp
//  Chess
//
//  Created by Ian Holdeman on 8/9/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#ifndef king_h
#define king_h

// Local Includes
#include "piece.hpp"

class King : public Piece
{
public:
  King(const glm::vec2 position, const glm::vec2 size, const Color game_color,
       Texture2D texture, const glm::vec3 color = glm::vec3(1.0))
  : Piece(std::move(position), std::move(size), std::move(game_color), std::move(texture), std::move(color))
  {
  }
  
  std::vector<std::pair<uint8_t, uint8_t>> calculate_possible_moves(const std::vector<std::vector<int8_t>>& board)
  {
    std::vector<std::pair<uint8_t, uint8_t>> moves;
    const uint8_t x = position_.x / 100;
    const uint8_t y = position_.y / 100;
    const uint8_t BOARD_MIN = 0;
    const uint8_t BOARD_MAX = board.size()-1;
    
    // Up-left
    if (y-1 >= BOARD_MIN && x-1 >= BOARD_MIN && board[y-1][x-1] == -1)
    {
      moves.push_back(std::pair<uint8_t, uint8_t>{y-1, x-1});
    }
      
    // Up
    if (y-1 >= BOARD_MIN && board[y-1][x] == -1)
    {
      moves.push_back(std::pair<uint8_t, uint8_t>{y-1, x});
    }
    
    // Up-right
    if (y-1 >= BOARD_MIN && x+1 <= BOARD_MAX && board[y-1][x+1] == -1)
    {
      moves.push_back(std::pair<uint8_t, uint8_t>{y-1, x+1});
    }
    
    // Right
    if (x+1 <= BOARD_MAX && board[y][x+1] == -1)
    {
      moves.push_back(std::pair<uint8_t, uint8_t>{y, x+1});
    }
    
    // Down-right
    if (y+1 <= BOARD_MAX && x+1 <= BOARD_MAX && board[y+1][x+1] == -1)
    {
      moves.push_back(std::pair<uint8_t, uint8_t>{y+1, x+1});
    }
    
    // Down
    if (y+1 <= BOARD_MAX && board[y+1][x] == -1)
    {
      moves.push_back(std::pair<uint8_t, uint8_t>{y+1, x});
    }
    
    // Down-left
    if (y+1 <= BOARD_MAX && x-1 >= BOARD_MIN && board[y+1][x-1] == -1)
    {
      moves.push_back(std::pair<uint8_t, uint8_t>{y+1, x-1});
    }
    
    // Left
    if (x-1 >= BOARD_MIN && board[y][x-1] == -1)
    {
      moves.push_back(std::pair<uint8_t, uint8_t>{y, x-1});
    }
    
    return moves;
  }
};

#endif /* king_h */
