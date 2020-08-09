//
//  rook.hpp
//  Chess
//
//  Created by Ian Holdeman on 8/9/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#ifndef rook_h
#define rook_h

// Local Includes
#include "piece.hpp"

class Rook : public Piece
{
public:
  Rook(const glm::vec2 position, const glm::vec2 size, const Color game_color,
       Texture2D texture, const glm::vec3 color = glm::vec3(1.0))
  : Piece(std::move(position), std::move(size), std::move(game_color), std::move(texture), std::move(color))
  {
  }
};

#endif /* rook_h */
