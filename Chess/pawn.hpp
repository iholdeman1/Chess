//
//  pawn.hpp
//  Chess
//
//  Created by Ian Holdeman on 8/9/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#ifndef pawn_h
#define pawn_h

// Local Includes
#include "piece.hpp"

class Pawn : public Piece
{
public:
  Pawn(const glm::vec2 position, const glm::vec2 size, const Color game_color,
       Texture2D texture, const glm::vec3 color = glm::vec3(1.0))
  : Piece(std::move(position), std::move(size), std::move(game_color), std::move(texture), std::move(color))
  {
  }
  
  std::vector<std::pair<uint8_t, uint8_t>> calculate_possible_moves(const std::vector<std::vector<int8_t>>& board)
  {
    std::vector<std::pair<uint8_t, uint8_t>> temp;
    const uint8_t x = position_.x / 100;
    const uint8_t y = position_.y / 100;
    
    // Note: this is for WHITE PIECES ONLY! Will update when I implement players
    if (!has_moved_ && board[y-1][x] == -1 && board[y-2][x] == -1)
    {
      temp.push_back(std::pair<uint8_t, uint8_t>{y-2, x});
    }
    
    if (board[y-1][x] == -1)
    {
      temp.push_back(std::pair<uint8_t, uint8_t>{y-1, x});
    }
    
    return temp;
  }
  
private:
  bool has_moved_ = false;
};

#endif /* pawn_h */
