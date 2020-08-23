//
//  game.cpp
//  Chess
//
//  Created by Ian Holdeman on 8/2/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#include "game.hpp"

Game::Game(const uint32_t width, const uint32_t height) : width_(width), height_(height)
{
}

Game::~Game()
{
  delete board_;
  delete renderer_;
  delete piece_manager_;
}

void Game::init()
{
  // Create the projection matrix
  const glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width_),
                                          static_cast<float>(height_), 0.0f, -1.0f, 1.0f);
  
  // Set up the basic shader
  ResourceManager::load_shader("/Users/ianholdeman/Desktop/Develop/Chess/Chess/Shaders/board.vert",
                               "/Users/ianholdeman/Desktop/Develop/Chess/Chess/Shaders/board.frag",
                               nullptr, "board");
  ResourceManager::get_shader("board").use();
  ResourceManager::get_shader("board").set_matrix4("projection", projection);
  
  // Set up the texture shader
  ResourceManager::load_shader("/Users/ianholdeman/Desktop/Develop/Chess/Chess/Shaders/texture.vert",
                               "/Users/ianholdeman/Desktop/Develop/Chess/Chess/Shaders/texture.frag",
                               nullptr, "texture");
  ResourceManager::get_shader("texture").use();
  ResourceManager::get_shader("texture").set_matrix4("projection", projection);
  
  // Load textures
  ResourceManager::load_texture("/Users/ianholdeman/Desktop/Develop/Chess/Chess/Assets/white_king_100.png",
                                true, "white_king");
  ResourceManager::load_texture("/Users/ianholdeman/Desktop/Develop/Chess/Chess/Assets/white_queen_100.png",
                                true, "white_queen");
  ResourceManager::load_texture("/Users/ianholdeman/Desktop/Develop/Chess/Chess/Assets/white_knight_100.png",
                                true, "white_knight");
  ResourceManager::load_texture("/Users/ianholdeman/Desktop/Develop/Chess/Chess/Assets/white_rook_100.png",
                                true, "white_rook");
  ResourceManager::load_texture("/Users/ianholdeman/Desktop/Develop/Chess/Chess/Assets/white_bishop_100.png",
                                true, "white_bishop");
  ResourceManager::load_texture("/Users/ianholdeman/Desktop/Develop/Chess/Chess/Assets/white_pawn_100.png",
                                true, "white_pawn");
  ResourceManager::load_texture("/Users/ianholdeman/Desktop/Develop/Chess/Chess/Assets/black_king_100.png",
                                true, "black_king");
  ResourceManager::load_texture("/Users/ianholdeman/Desktop/Develop/Chess/Chess/Assets/black_queen_100.png",
                                true, "black_queen");
  ResourceManager::load_texture("/Users/ianholdeman/Desktop/Develop/Chess/Chess/Assets/black_knight_100.png",
                                true, "black_knight");
  ResourceManager::load_texture("/Users/ianholdeman/Desktop/Develop/Chess/Chess/Assets/black_rook_100.png",
                                true, "black_rook");
  ResourceManager::load_texture("/Users/ianholdeman/Desktop/Develop/Chess/Chess/Assets/black_bishop_100.png",
                                true, "black_bishop");
  ResourceManager::load_texture("/Users/ianholdeman/Desktop/Develop/Chess/Chess/Assets/black_pawn_100.png",
                                true, "black_pawn");
  
  // Create the board
  board_ = new Board(width_, height_);
  
  // Create the piece manager
  piece_manager_ = new PieceManager(width_ / 8);
  
  // Create the renderer
  renderer_ = new Renderer();
}

void Game::process_input(const float delta_time)
{
  
}

void Game::update(const float delta_time)
{
  
}

void Game::render()
{
  board_->render(renderer_);
  piece_manager_->render(renderer_);
}

void Game::handle_mouse_down()
{
  if (!mouse_down_)
  {
    mouse_down_ = true;
  }
}

void Game::handle_mouse_up(const double x, const double y)
{
  if (mouse_down_)
  {
    const int new_x = x/100;
    const int new_y = y/100;
    
    if (board_->is_piece_at_square(new_x, new_y))
    {
      const int8_t piece_id = board_->get_piece_at_square(new_x, new_y);
      const auto moves = piece_manager_->get_pieces_moves(piece_id, board_->get_current_board());
      board_->accept_valid_moves(std::move(moves));
    }
    
    mouse_down_ = false;
  }
}
