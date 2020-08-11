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
    std::vector<std::pair<uint8_t, uint8_t>> temp;
    const uint8_t x = position_.x / 100;
    const uint8_t y = position_.y / 100;
    uint8_t count = 1;
    
    // Up-left
    if (y-count >= 0 && x-count >= 0)
    {
      temp.push_back(std::pair<uint8_t, uint8_t>{y-count, x-count});
    }
      
    // Up
    if (y-count >= 0)
    {
      temp.push_back(std::pair<uint8_t, uint8_t>{y-count, x});
    }
    
    // Up-right
    if (y-count >= 0 && x+count <= 7)
    {
      temp.push_back(std::pair<uint8_t, uint8_t>{y-count, x+count});
    }
    
    // Right
    if (x+count <= 7)
    {
      temp.push_back(std::pair<uint8_t, uint8_t>{y, x+count});
    }
    
    // Down-right
    if (y+count <= 7 && x+count <= 7)
    {
      temp.push_back(std::pair<uint8_t, uint8_t>{y+count, x+count});
    }
    
    // Down
    if (y+count <= 7)
    {
      temp.push_back(std::pair<uint8_t, uint8_t>{y+count, x});
    }
    
    // Down-left
    if (y+count <= 7 && x-count >= 0)
    {
      temp.push_back(std::pair<uint8_t, uint8_t>{y+count, x-count});
    }
    
    // Left
    if (x-count >= 0)
    {
      temp.push_back(std::pair<uint8_t, uint8_t>{y, x-count});
    }
    
    return temp;
  }
};

#endif /* king_h */
