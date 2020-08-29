//
//  board.hpp
//  Chess
//
//  Created by Ian Holdeman on 8/2/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

// System Includes
#include <map>
#include <stdint.h>
#include <vector>

// Local Includes
#include "renderer.hpp"

class Board
{
public:
  Board(const uint32_t width, const uint32_t height);
  
  void render(Renderer *renderer);

  const std::vector<std::vector<int8_t>>& get_current_board() const;
  bool is_piece_at_square(const uint8_t x, const uint8_t y) const;
  int8_t get_piece_at_square(const uint8_t x, const uint8_t y) const;
  bool is_valid_move(const uint8_t x, const uint8_t y) const;
  void accept_valid_moves(const std::vector<std::pair<uint8_t, uint8_t>> moves);
  void move_piece(const glm::vec2& old_position, const glm::vec2& new_position);
  void reset_board();
  
private:
  void initialize_board();
  void clear_moves();
  
  uint32_t width_;
  uint32_t height_;
  uint32_t square_size_;
  
  std::vector<std::vector<int8_t>> board_;
  std::map<std::pair<uint8_t, uint8_t>, bool> moves_;
};

#endif /* board_hpp */
