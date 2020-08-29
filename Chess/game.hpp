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
#include <vector>

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
  void process_input();
  void update();
  void render();
  
  void handle_mouse_down();
  void handle_mouse_up(const double x, const double y);

private:
  enum class GameState
  {
    ACTIVE = 0,
    IDLE = 1,
    OVER = 2
  };
  
  struct PawnOptions
  {
    Texture2D texture;
    glm::vec2 position;
    uint8_t flag;
  };
  
  void reset_game();
  void handle_pawn_options(const uint32_t x, const uint32_t y);
  
  uint32_t width_, height_;
  Board *board_ = nullptr;
  Renderer *renderer_ = nullptr;
  PieceManager *piece_manager_ = nullptr;
  
  uint8_t turn_ = 1;
  bool game_over_ = false;
  bool mouse_up_ = false;
  bool mouse_down_ = false;
  bool change_turn_ = false;
  bool idle_mode_ = false;
  uint8_t lucky_pawn_ = -1;
  uint8_t selected_piece_ = -1;
  GameState game_state_ = GameState::ACTIVE;
  glm::vec2 mouse_position_ = glm::vec2(1.0f);
  std::vector<PawnOptions> pawn_options_;
};

#endif /* game_hpp */
