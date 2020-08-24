//
//  piece_manager.cpp
//  Chess
//
//  Created by Ian Holdeman on 8/9/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#include "piece_manager.hpp"

PieceManager::PieceManager(const uint32_t piece_size)
{
  pieces_.reserve(32);
  
  // Construct black army
  pieces_.push_back(new Rook(glm::vec2(0, 0), glm::vec2(piece_size), Color::BLACK,
                             ResourceManager::get_texture("black_rook")));
  pieces_.push_back(new Knight(glm::vec2(100, 0), glm::vec2(piece_size), Color::BLACK,
                               ResourceManager::get_texture("black_knight")));
  pieces_.push_back(new Bishop(glm::vec2(200, 0), glm::vec2(piece_size), Color::BLACK,
                               ResourceManager::get_texture("black_bishop")));
  pieces_.push_back(new Queen(glm::vec2(300, 0), glm::vec2(piece_size), Color::BLACK,
                              ResourceManager::get_texture("black_queen")));
  pieces_.push_back(new King(glm::vec2(400, 0), glm::vec2(piece_size), Color::BLACK,
                             ResourceManager::get_texture("black_king")));
  pieces_.push_back(new Bishop(glm::vec2(500, 0), glm::vec2(piece_size), Color::BLACK,
                               ResourceManager::get_texture("black_bishop")));
  pieces_.push_back(new Knight(glm::vec2(600, 0), glm::vec2(piece_size), Color::BLACK,
                               ResourceManager::get_texture("black_knight")));
  pieces_.push_back(new Rook(glm::vec2(700, 0), glm::vec2(piece_size), Color::BLACK,
                             ResourceManager::get_texture("black_rook")));
  
  // Construct black pawns
  for (uint32_t i = 0; i < 8; i++)
  {
    pieces_.push_back(new Pawn(glm::vec2(i*100, 100), glm::vec2(piece_size), Color::BLACK,
                               ResourceManager::get_texture("black_pawn")));
  }

  // Construct white pawns
  for (uint32_t i = 0; i < 8; i++)
  {
    pieces_.push_back(new Pawn(glm::vec2(i*100, 600), glm::vec2(piece_size), Color::WHITE,
                               ResourceManager::get_texture("white_pawn")));
  }
  
  // Construct white army
  pieces_.push_back(new Rook(glm::vec2(0, 700), glm::vec2(piece_size), Color::WHITE,
                             ResourceManager::get_texture("white_rook")));
  pieces_.push_back(new Knight(glm::vec2(100, 700), glm::vec2(piece_size), Color::WHITE,
                               ResourceManager::get_texture("white_knight")));
  pieces_.push_back(new Bishop(glm::vec2(200, 700), glm::vec2(piece_size), Color::WHITE,
                               ResourceManager::get_texture("white_bishop")));
  pieces_.push_back(new Queen(glm::vec2(300, 700), glm::vec2(piece_size), Color::WHITE,
                              ResourceManager::get_texture("white_queen")));
  pieces_.push_back(new King(glm::vec2(400, 700), glm::vec2(piece_size), Color::WHITE,
                             ResourceManager::get_texture("white_king")));
  pieces_.push_back(new Bishop(glm::vec2(500, 700), glm::vec2(piece_size), Color::WHITE,
                               ResourceManager::get_texture("white_bishop")));
  pieces_.push_back(new Knight(glm::vec2(600, 700), glm::vec2(piece_size), Color::WHITE,
                               ResourceManager::get_texture("white_knight")));
  pieces_.push_back(new Rook(glm::vec2(700, 700), glm::vec2(piece_size), Color::WHITE,
                             ResourceManager::get_texture("white_rook")));
}

PieceManager::~PieceManager()
{
  for (Piece *piece : pieces_)
  {
    delete piece;
  }
  
  pieces_.clear();
}

void PieceManager::render(Renderer *renderer)
{
  for (Piece *piece : pieces_)
  {
    if (piece != nullptr)
    {
      piece->render(renderer);
    }
  }
}

const std::vector<std::pair<uint8_t, uint8_t>> PieceManager::get_pieces_moves(const uint8_t id,
                                                                              const std::vector<std::vector<int8_t>>& board,
                                                                              const uint8_t turn) const
{
  return pieces_[id]->calculate_possible_moves(board, turn);
}

glm::vec2 PieceManager::get_piece_position(const uint8_t id) const
{
  return pieces_[id]->get_position();
}

Color PieceManager::get_piece_game_color(const uint8_t id) const
{
  return pieces_[id]->get_game_piece_color();
}

void PieceManager::move_piece(const uint8_t id, const glm::vec2 &position)
{
  pieces_[id]->update_position(position);
}

void PieceManager::delete_piece(const uint8_t id)
{
  delete pieces_[id];
  pieces_[id] = nullptr;
}
