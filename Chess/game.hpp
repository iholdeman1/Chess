//
//  game.hpp
//  Chess
//
//  Created by Ian Holdeman on 8/2/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

// System Includes
#include <stdint.h>

// Local Includes
#include "board.hpp"
#include "renderer.hpp"
#include "resource_manager.hpp"

class Game
{
public:
  Game(const uint32_t width, const uint32_t height);
  ~Game();
  
  void process_input(const float delta_time);
  void update(const float delta_time);
  void render();

private:
  uint32_t width_, height_;
  Board *board_ = nullptr;
  Renderer *renderer_ = nullptr;
};

#endif /* game_hpp */
