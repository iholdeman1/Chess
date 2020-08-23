//
//  piece.hpp
//  Chess
//
//  Created by Ian Holdeman on 8/9/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#ifndef piece_hpp
#define piece_hpp

// Library Includes
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

// System Includes
#include <utility>
#include <vector>

// Local Includes
#include "renderer.hpp"
#include "texture.hpp"

enum class Color
{
  WHITE = 0,
  BLACK = 1
};

enum class Direction
{
  UP = 0,
  UP_RIGHT = 1,
  RIGHT = 2,
  DOWN_RIGHT = 3,
  DOWN = 4,
  DOWN_LEFT = 5,
  LEFT = 6,
  UP_LEFT = 7
};

using PairsList = std::vector<std::pair<uint8_t, uint8_t>>;

class Piece
{
public:
  Piece(const glm::vec2 position, const glm::vec2 size, const Color game_color,
        Texture2D texture, const glm::vec3 color)
  : position_(position), size_(size), game_color_(game_color), texture_(texture), color_(color)
  {
  }
  
  void render(Renderer *renderer)
  {
    renderer->render_textured_object(texture_, position_, size_, color_, 0.0f);
  }
  
  PairsList calcules_moves_in_a_direction(PairsList moves, Direction dir, const int x,
                                          const int y, const std::vector<std::vector<int8_t>>& board)
  {
    uint8_t count = 1;
    const uint8_t BOARD_MIN = 0;
    const uint8_t BOARD_MAX = board.size();
    
    switch (dir)
    {
      case Direction::UP:
      {
        while (y-count >= BOARD_MIN)
        {
          moves.push_back(std::pair<uint8_t, uint8_t>{y-count, x});
          if (board[y-count][x] != -1)
          {
            break;
          }
          count++;
        }
        break;
      }
      case Direction::UP_RIGHT:
      {
        while (y-count >= BOARD_MIN || x+count <= BOARD_MAX)
        {
          moves.push_back(std::pair<uint8_t, uint8_t>{y-count, x+count});
          if (board[y-count][x+count] != -1)
          {
            break;
          }
          count++;
        }
        break;
      }
      case Direction::RIGHT:
      {
        while (x+count <= BOARD_MAX)
        {
          moves.push_back(std::pair<uint8_t, uint8_t>{y, x+count});
          if (board[y][x+count] != -1)
          {
            break;
          }
          count++;
        }
        break;
      }
      case Direction::DOWN_RIGHT:
      {
        while (y+count <= BOARD_MAX || x+count <= BOARD_MAX)
        {
          moves.push_back(std::pair<uint8_t, uint8_t>{y+count, x+count});
          if (board[y+count][x+count] != -1)
          {
            break;
          }
          count++;
        }
        break;
      }
      case Direction::DOWN:
      {
        while (y+count <= BOARD_MAX)
        {
          moves.push_back(std::pair<uint8_t, uint8_t>{y+count, x});
          if (board[y+count][x] != -1)
          {
            break;
          }
          count++;
        }
        break;
      }
      case Direction::DOWN_LEFT:
      {
        while (y+count >= BOARD_MIN || x-count >= BOARD_MAX)
        {
          moves.push_back(std::pair<uint8_t, uint8_t>{y+count, x-count});
          if (board[y+count][x-count] != -1)
          {
            break;
          }
          count++;
        }
        break;
      }
      case Direction::LEFT:
      {
        while (x-count >= BOARD_MIN)
        {
          moves.push_back(std::pair<uint8_t, uint8_t>{y, x-count});
          if (board[y][x-count] != -1)
          {
            break;
          }
          count++;
        }
        break;
      }
      case Direction::UP_LEFT:
      {
        while (y-count >= BOARD_MIN || x-count >= BOARD_MIN)
        {
          moves.push_back(std::pair<uint8_t, uint8_t>{y-count, x-count});
          if (board[y-count][x-count] != -1)
          {
            break;
          }
          count++;
        }
        break;
      }
      default:
        break;
    }
    
    return moves;
  }
  
  virtual PairsList calculate_possible_moves(const std::vector<std::vector<int8_t>>& board) = 0;

protected:
  glm::vec2 position_;
  glm::vec2 size_;
  Color game_color_;
  Texture2D texture_;
  glm::vec3 color_;
};

#endif /* piece_hpp */
