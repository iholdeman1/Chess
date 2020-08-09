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
};

#endif /* king_h */
