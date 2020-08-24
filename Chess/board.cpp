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
  board_ = std::vector<std::vector<int8_t>>(8, std::vector<int8_t>(8, -1));
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
      const glm::vec2 position(j * square_size_, i * square_size_);
      
      glm::vec4 color;
      color = (i + j) % 2 == 0 ? glm::vec4(0.9f, 0.9f, 0.9f, 1.0) : glm::vec4(0.4f, 0.4f, 0.4f, 1.0);
      renderer->render_basic_object(position, size, color, 0.0f);
      
      if (is_valid_move(i, j))
      {
        color = glm::vec4(0.0f, 0.8f, 0.8f, 0.4);
        renderer->render_basic_object(position, size, color, 0.0f);
      }
    }
  }
}

const std::vector<std::vector<int8_t>>& Board::get_current_board() const
{
  return board_;
}

bool Board::is_piece_at_square(const uint8_t x, const uint8_t y) const
{
  return board_[y][x] != -1;
}

int8_t Board::get_piece_at_square(const uint8_t x, const uint8_t y) const
{
  return board_[y][x];
}

bool Board::is_valid_move(const uint8_t x, const uint8_t y) const
{
  auto search = moves_.find(std::pair<uint8_t, uint8_t>{x, y});
  return search != moves_.end();
}

void Board::accept_valid_moves(const std::vector<std::pair<uint8_t, uint8_t>> moves)
{
  clear_moves();
  
  for (const std::pair<uint8_t, uint8_t>& pair : moves)
  {
    moves_[pair] = true;
  }
}

void Board::move_piece(const glm::vec2& old_position, const glm::vec2& new_position)
{
  board_[new_position.y][new_position.x] = board_[old_position.y][old_position.x];
  board_[old_position.y][old_position.x] = -1;
  clear_moves();
}

void Board::clear_moves()
{
  moves_.clear();
}
