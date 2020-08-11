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
    std::vector<std::pair<uint8_t, uint8_t>> temp;
    const uint8_t x = position_.x / 100;
    const uint8_t y = position_.y / 100;
    uint8_t count = 1;
    
    // Up
    while (true)
    {
      if (y-count < 0)
      {
        count = 1;
        break;
      }
      temp.push_back(std::pair<uint8_t, uint8_t>{y-count, x});
      count++;
    }
    
    // Down
    while (true)
    {
      if (y+count > 7)
      {
        count = 1;
        break;
      }
      temp.push_back(std::pair<uint8_t, uint8_t>{y+count, x});
      count++;
    }
    
    // Right
    while (true)
    {
      if (x+count > 7)
      {
        count = 1;
        break;
      }
      temp.push_back(std::pair<uint8_t, uint8_t>{y, x+count});
      count++;
    }
    
    // Left
    while (true)
    {
      if (x-count < 0)
      {
        count = 1;
        break;
      }
      temp.push_back(std::pair<uint8_t, uint8_t>{y, x-count});
      count++;
    }
    
    // Up-left
    while (true)
    {
      if (y-count < 0 || x-count < 0)
      {
        count = 1;
        break;
      }
      
      temp.push_back(std::pair<uint8_t, uint8_t>{y-count, x-count});
      count++;
    }
    
    // Up-right
    while (true)
    {
      if (y-count < 0 || x+count > 7)
      {
        count = 1;
        break;
      }
      
      temp.push_back(std::pair<uint8_t, uint8_t>{y-count, x+count});
      count++;
    }
    
    // Down-right
    while (true)
    {
      if (y+count > 7 || x+count > 7)
      {
        count = 1;
        break;
      }
      
      temp.push_back(std::pair<uint8_t, uint8_t>{y+count, x+count});
      count++;
    }
    
    // Down-left
    while (true)
    {
      if (y+count > 7 || x-count < 0)
      {
        count = 1;
        break;
      }
      
      temp.push_back(std::pair<uint8_t, uint8_t>{y+count, x-count});
      count++;
    }
    
    
    return temp;
  }
};

#endif /* queen_h */
