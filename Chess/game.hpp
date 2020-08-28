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
  void update(const float delta_time);
  void render();
  
  void handle_mouse_down();
  void handle_mouse_up(const double x, const double y);

private:
  enum class GameState
  {
    ACTIVE = 0,
    OVER = 1
  };
  
  uint32_t width_, height_;
  Board *board_ = nullptr;
  Renderer *renderer_ = nullptr;
  PieceManager *piece_manager_ = nullptr;
  
  uint8_t turn_ = 1;
  bool game_over_ = false;
  bool mouse_down_ = false;
  bool change_turn_ = false;
  uint8_t selected_piece_ = -1;
  GameState game_state_ = GameState::ACTIVE;
  glm::vec2 mouse_position_ = glm::vec2(1.0f);
};

#endif /* game_hpp */
