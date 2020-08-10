//
//  board.cpp
//  Chess
//
//  Created by Ian Holdeman on 8/2/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#include "board.hpp"

Board::Board(const uint32_t width, const uint32_t height) : width_(width), height_(height)
{
  square_size_ = width_ / 8;
  
  // Initialized board with expected piece ids
  uint8_t id_count = 0;
  for (uint8_t i = 0; i < 8; i++)
  {
    for (uint8_t j = 0; j < 8; j++)
    {
      if (i == 0 || i == 1 || i == 6 || i == 7)
      {
        board_[i][j] = id_count;
        id_count++;
      }
      else
      {
        board_[i][j] = -1;
      }
    }
  }
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

bool Board::is_piece_at_square(const uint8_t x, const uint8_t y) const
{
  return board_[y][x] != -1;
}

int8_t Board::get_piece_at_square(const uint8_t x, const uint8_t y) const
{
  return board_[y][x];
}
