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

private:
  uint32_t width_;
  uint32_t height_;
  uint32_t square_size_;
};

#endif /* board_hpp */
