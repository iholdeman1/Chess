//
//  knight.hpp
//  Chess
//
//  Created by Ian Holdeman on 8/9/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#ifndef knight_h
#define knight_h

// Local Includes
#include "piece.hpp"

class Knight : public Piece
{
public:
  Knight(const glm::vec2 position, const glm::vec2 size, const Color game_color,
         Texture2D texture, const glm::vec3 color = glm::vec3(1.0))
  : Piece(std::move(position), std::move(size), std::move(game_color), std::move(texture), std::move(color))
  {
  }
  
  std::vector<std::pair<uint8_t, uint8_t>> calculate_possible_moves(const std::vector<std::vector<int8_t>>& board)
  {
    std::vector<std::pair<uint8_t, uint8_t>> temp;
    const uint8_t x = position_.x / 100;
    const uint8_t y = position_.y / 100;
    
    // Up-left
    if (y-2 >= 0 && x-1 >= 0)
    {
      temp.push_back(std::pair<uint8_t, uint8_t>{y-2, x-1});
    }
      
    // Up-right
    if (y-2 >= 0 && x+1 <= 7)
    {
      temp.push_back(std::pair<uint8_t, uint8_t>{y-2, x+1});
    }
    
    // Right-up
    if (y-1 >= 0 && x+2 <= 7)
    {
      temp.push_back(std::pair<uint8_t, uint8_t>{y-1, x+2});
    }
    
    // Right-down
    if (y+1 >= 0 && x+2 <= 7)
    {
      temp.push_back(std::pair<uint8_t, uint8_t>{y+1, x+2});
    }
    
    // Down-right
    if (y+2 <= 7 && x+1 <= 7)
    {
      temp.push_back(std::pair<uint8_t, uint8_t>{y+2, x+1});
    }
    
    // Down-left
    if (y+2 <= 7 && x-1 >= 0)
    {
      temp.push_back(std::pair<uint8_t, uint8_t>{y+2, x-1});
    }
    
    // Left-down
    if (y+1 <= 7 && x-2 >= 0)
    {
      temp.push_back(std::pair<uint8_t, uint8_t>{y+1, x-2});
    }
    
    // Left-up
    if (y-1 >= 0 && x-2 >= 0)
    {
      temp.push_back(std::pair<uint8_t, uint8_t>{y-1, x-2});
    }
    
    return temp;
  }
};

#endif /* knight_h */
