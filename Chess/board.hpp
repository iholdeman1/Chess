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
#include <stdint.h>

// Local Includes
#include "renderer.hpp"

class Board
{
public:
  Board(const uint32_t width, const uint32_t height);
  
  void render(Renderer *renderer);

  bool is_piece_at_square(const uint8_t x, const uint8_t y) const;
  int8_t get_piece_at_square(const uint8_t x, const uint8_t y) const;
  
private:
  uint32_t width_;
  uint32_t height_;
  uint32_t square_size_;
  
  int8_t board_[8][8];
};

#endif /* board_hpp */
