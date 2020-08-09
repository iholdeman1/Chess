//
//  piece.hpp
//  Chess
//
//  Created by Ian Holdeman on 8/9/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#ifndef piece_hpp
#define piece_hpp

// Library Includes
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

// Local Includes
#include "renderer.hpp"
#include "texture.hpp"

enum class Color
{
  WHITE = 0,
  BLACK = 1
};

class Piece
{
public:
  Piece(const glm::vec2 position, const glm::vec2 size, const Color game_color,
        Texture2D texture, const glm::vec3 color)
  : position_(position), size_(size), game_color_(game_color), texture_(texture), color_(color)
  {
  }
  
  void render(Renderer *renderer)
  {
    renderer->render_textured_object(texture_, position_, size_, color_, 0.0f);
  }

protected:
  glm::vec2 position_;
  glm::vec2 size_;
  Color game_color_;
  Texture2D texture_;
  glm::vec3 color_;
};

#endif /* piece_hpp */
