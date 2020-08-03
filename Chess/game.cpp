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
  // Create the projection matrix
  const glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width_),
                                          static_cast<float>(height_), 0.0f, -1.0f, 1.0f);
  
  // Set up the basic shader
  ResourceManager::load_shader("/Users/ianholdeman/Desktop/Develop/Chess/Chess/Shaders/board.vert",
                               "/Users/ianholdeman/Desktop/Develop/Chess/Chess/Shaders/board.frag",
                               nullptr, "board");
  ResourceManager::get_shader("board").use();
  ResourceManager::get_shader("board").set_matrix4("projection", projection);
  
  // Create the board
  board_ = new Board(width_, height_);
  
  // Create the renderer
  renderer_ = new Renderer();
}

Game::~Game()
{
  delete board_;
  delete renderer_;
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
}
