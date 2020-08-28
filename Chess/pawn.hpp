//
//  pawn.hpp
//  Chess
//
//  Created by Ian Holdeman on 8/9/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#ifndef pawn_h
#define pawn_h

// Local Includes
#include "piece.hpp"

class Pawn : public Piece
{
public:
  Pawn(const glm::vec2 position, const glm::vec2 size, const Color game_color,
       Texture2D texture, const glm::vec3 color = glm::vec3(1.0))
  : Piece(std::move(position), std::move(size), std::move(game_color), std::move(texture), std::move(color))
  {
    is_pawn_ = true;
  }
  
  std::vector<std::pair<uint8_t, uint8_t>> calculate_possible_moves(const std::vector<std::vector<int8_t>>& board, const uint8_t turn)
  {
    std::vector<std::pair<uint8_t, uint8_t>> moves;
    const uint8_t x = position_.x / 100;
    const uint8_t y = position_.y / 100;
    const uint8_t distance = has_moved_ ? 1 : 2;
    const uint8_t BOARD_MIN = 0;
    const uint8_t BOARD_MAX = board.size()-1;
    
    if (turn == 0) // Black's Turn
    {
      for (uint8_t i = 1; i <= distance; i++)
      {
        if (y+i <= BOARD_MAX && board[y+i][x] == -1)
        {
          moves.push_back(std::pair<uint8_t, uint8_t>{y+i, x});
        }
      }
      
      if (y+1 <= BOARD_MAX && x+1 <= BOARD_MAX &&
          board[y+1][x+1] != -1 && colors_are_different(board[y][x], board[y+1][x+1]))
      {
        moves.push_back(std::pair<uint8_t, uint8_t>{y+1, x+1});
      }
      
      if (y+1 <= BOARD_MAX && x-1 >= BOARD_MIN &&
          board[y+1][x-1] != -1 && colors_are_different(board[y][x], board[y+1][x-1]))
      {
        moves.push_back(std::pair<uint8_t, uint8_t>{y+1, x-1});
      }
    }
    else // White's Turn
    {
      for (uint8_t i = 1; i <= distance; i++)
      {
        if (y-i >= BOARD_MIN && board[y-i][x] == -1 || colors_are_different(board[y][x], board[y-i][x]))
        {
          moves.push_back(std::pair<uint8_t, uint8_t>{y-i, x});
        }
      }
      
      if (y-1 >= BOARD_MIN && x+1 <= BOARD_MAX &&
          board[y-1][x+1] != -1 && colors_are_different(board[y][x], board[y-1][x+1]))
      {
        moves.push_back(std::pair<uint8_t, uint8_t>{y-1, x+1});
      }
      
      if (y-1 >= BOARD_MIN && x-1 >= BOARD_MIN &&
          board[y-1][x-1] != -1 && colors_are_different(board[y][x], board[y-1][x-1]))
      {
        moves.push_back(std::pair<uint8_t, uint8_t>{y-1, x-1});
      }
    }
    
    return moves;
  }
};

#endif /* pawn_h */
