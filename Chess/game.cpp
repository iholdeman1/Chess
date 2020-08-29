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
  
  // Set up the font shader
  ResourceManager::load_shader("/Users/ianholdeman/Desktop/Develop/Chess/Chess/Shaders/font.vert",
                               "/Users/ianholdeman/Desktop/Develop/Chess/Chess/Shaders/font.frag",
                               nullptr, "font");
  ResourceManager::get_shader("font").use();
  ResourceManager::get_shader("font").set_matrix4("projection", projection);
  
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
  renderer_->load_font("/Users/ianholdeman/Desktop/Develop/Chess/Chess/Assets/OCRAEXT.TTF", 48);
}

void Game::process_input()
{
  if (!mouse_up_)
  {
    return;
  }
  
  if (game_state_ == GameState::ACTIVE)
  {
    const uint8_t new_x = mouse_position_.x/100;
    const uint8_t new_y = mouse_position_.y/100;
    
    // If moves already calculated and you clicked a valid move
    if (selected_piece_ != -1 && board_->is_valid_move(new_y, new_x))
    {
      // If enemy capture
      if (board_->is_piece_at_square(new_x, new_y))
      {
        game_over_ = piece_manager_->is_piece_king(board_->get_piece_at_square(new_x, new_y));
        piece_manager_->delete_piece(board_->get_piece_at_square(new_x, new_y));
      }
      // Move piece
      const glm::vec2 old_position = piece_manager_->get_piece_position(selected_piece_);
      board_->move_piece(glm::vec2(old_position.x/100, old_position.y/100), glm::vec2(new_x, new_y));
      idle_mode_ = piece_manager_->move_piece(selected_piece_, glm::vec2(new_x*100, new_y*100));
      
      // If pawn made it to the other end
      if (idle_mode_)
      {
        handle_pawn_options(new_x*100, new_y*100);
      }
      
      selected_piece_ = -1;
      change_turn_ = true;
    }
    // Calculate moves for piece
    else if (board_->is_piece_at_square(new_x, new_y) &&
             piece_manager_->get_piece_game_color(board_->get_piece_at_square(new_x, new_y)) == static_cast<Color>(turn_))
    {
      selected_piece_ = board_->get_piece_at_square(new_x, new_y);
      const auto moves = piece_manager_->get_pieces_moves(selected_piece_, board_->get_current_board(), turn_);
      board_->accept_valid_moves(std::move(moves));
    }
  }
  else if (game_state_ == GameState::IDLE)
  {
    const uint32_t new_x = static_cast<uint8_t>(mouse_position_.x / 100.0) * 100;
    const uint32_t new_y = static_cast<uint8_t>(mouse_position_.y / 100.0) * 100;
    
    for (const PawnOptions& pawn_option : pawn_options_)
    {
      // If you clicked a pawn upgrade
      if (new_x == pawn_option.position.x && new_y == pawn_option.position.y)
      {
        piece_manager_->upgrade_pawn(lucky_pawn_, pawn_option.flag, pawn_option.texture);
        game_state_ = GameState::ACTIVE;
        lucky_pawn_ = -1;
        pawn_options_.clear();
      }
    }
  }
  else if (game_state_ == GameState::OVER)
  {
    reset_game();
  }
  mouse_up_ = false;
}

void Game::update()
{
  if (game_over_)
  {
    game_state_ = GameState::OVER;
  }
  else if (idle_mode_)
  {
    game_state_ = GameState::IDLE;
    idle_mode_ = false;
  }
  else if (game_state_ == GameState::ACTIVE && change_turn_)
  {
    turn_ = !turn_;
    change_turn_ = false;
  }
}

void Game::render()
{
  board_->render(renderer_);
  piece_manager_->render(renderer_);
  
  if (game_state_ == GameState::IDLE)
  {
    // Gray overlay
    renderer_->render_basic_object(glm::vec2(0, 0), glm::vec2(width_, height_),
                                   glm::vec4(0.25f, 0.25f, 0.25f, 0.75f), 0.0f);
    
    // Get state of pawn
    const glm::vec2 pawn_position = piece_manager_->get_piece_position(lucky_pawn_);
    const std::string piece_color_str = piece_manager_->get_piece_game_color(lucky_pawn_) == Color::WHITE ? "white" : "black";
    const glm::vec4 color = glm::vec4(0.9f, 0.9f, 0.9f, 1.0);
    
    // Render pawn and white square behind it
    renderer_->render_basic_object(pawn_position, glm::vec2(100), color, 0.0f);
    renderer_->render_textured_object(ResourceManager::get_texture(piece_color_str + "_pawn"), pawn_position,
                                      glm::vec2(100), color, 0.0f);
    
    // Render each pawn upgrade
    for (const PawnOptions& pawn_option : pawn_options_)
    {
      renderer_->render_basic_object(pawn_option.position, glm::vec2(100), color, 0.0f);
      renderer_->render_textured_object(pawn_option.texture, pawn_option.position,
                                        glm::vec2(100), color, 0.0f);
    }
  }
  else if (game_state_ == GameState::OVER)
  {
    // Gray overlay
    renderer_->render_basic_object(glm::vec2(0, 0), glm::vec2(width_, height_),
                                   glm::vec4(0.25f, 0.25f, 0.25f, 0.75f), 0.0f);
    
    // Winner
    const std::string color = turn_ == 1 ? "White" : "Black";
    renderer_->render_font(color + " wins!", 170.0f, 375.0f, 1.5f);
    
    // Click anywhere message
    renderer_->render_font("Click anywhere to play again!", 190.0f, 450.0f, 0.5f);
  }
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
    mouse_up_ = true;
    mouse_down_ = false;
    mouse_position_ = glm::vec2(x, y);
  }
}

void Game::reset_game()
{
  // Reset objects
  board_->reset_board();
  piece_manager_->reset_pieces();
  
  // Reset state
  turn_ = 1;
  idle_mode_ = false;
  game_over_ = false;
  change_turn_ = false;
  lucky_pawn_ = -1;
  selected_piece_ = -1;
  game_state_ = GameState::ACTIVE;
}

void Game::handle_pawn_options(const uint32_t x, const uint32_t y)
{
  lucky_pawn_ = selected_piece_;
  const Color lucky_color = piece_manager_->get_piece_game_color(lucky_pawn_);
  const std::string piece_color_str = lucky_color == Color::WHITE ? "white" : "black";
  
  for (uint8_t i = 0; i < 4; i++)
  {
    PawnOptions temp;
    const uint32_t y_val = lucky_color == Color::WHITE ? y + (100 * (i+1)) : y - (100 * (i+1));
    
    switch (i)
    {
      case 0:
        temp.texture = ResourceManager::get_texture(piece_color_str + "_queen");
        temp.position = glm::vec2(x, y_val);
        temp.flag = 0;
        break;
      case 1:
        temp.texture = ResourceManager::get_texture(piece_color_str + "_rook");
        temp.position = glm::vec2(x, y_val);
        temp.flag = 1;
        break;
      case 2:
        temp.texture = ResourceManager::get_texture(piece_color_str + "_bishop");
        temp.position = glm::vec2(x, y_val);
        temp.flag = 2;
        break;
      case 3:
        temp.texture = ResourceManager::get_texture(piece_color_str + "_knight");
        temp.position = glm::vec2(x, y_val);
        temp.flag = 3;
        break;
      default:
        break;
    }
    pawn_options_.push_back(temp);
  }
}
