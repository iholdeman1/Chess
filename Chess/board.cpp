//
//  board.cpp
//  Chess
//
//  Created by Ian Holdeman on 8/2/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#include "board.hpp"

#include <iostream>

Board::Board(const uint32_t width, const uint32_t height) : width_(width), height_(height)
{
  square_size_ = width_ / 8;
}

void Board::render(Renderer *renderer)
{
  const glm::vec2 size(square_size_, square_size_);
  for (uint8_t i = 0; i < 8; i++)
  {
    for (uint8_t j = 0; j < 8; j++)
    {
      const glm::vec3 color = (i + j) % 2 == 0 ? glm::vec3(0.9f, 0.9f, 0.9f) : glm::vec3(0.4f, 0.4f, 0.4f);
      const glm::vec2 position(j * square_size_, i * square_size_);
      renderer->render_basic_object(position, size, color, 0.0f);
    }
  }
}
