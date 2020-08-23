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
#include <string>

// Local Includes
#include "board.hpp"
#include "piece_manager.hpp"
#include "renderer.hpp"
#include "resource_manager.hpp"

class Game
{
public:
  Game(const uint32_t width, const uint32_t height);
  ~Game();
  
  void init();
  void process_input(const float delta_time);
  void update(const float delta_time);
  void render();
  
  void handle_mouse_down();
  void handle_mouse_up(const double x, const double y);

private:
  uint32_t width_, height_;
  Board *board_ = nullptr;
  Renderer *renderer_ = nullptr;
  PieceManager *piece_manager_ = nullptr;
  
  bool mouse_down_ = false;
  uint8_t selected_piece_ = -1;
  glm::vec2 mouse_position_ = glm::vec2(1.0f);
};

#endif /* game_hpp */
