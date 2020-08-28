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
  BLACK = 0,
  WHITE = 1
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
  
  glm::vec2 get_position() const
  {
    return position_;
  }
  
  glm::vec2 get_size() const
  {
    return size_;
  }
  
  Color get_game_piece_color() const
  {
    return game_color_;
  }
  
  bool get_is_king() const
  {
    return is_king_;
  }
  
  bool get_is_pawn() const
  {
    return is_pawn_;
  }
  
  void update_position(const glm::vec2& position)
  {
    position_ = position;
    has_moved_ = true;
  }
  
  bool colors_are_different(const uint8_t owner_id, const uint8_t target_id) const
  {
    return (owner_id <= 15) ^ (target_id <= 15);
  }
  
  PairsList calcules_moves_in_a_direction(PairsList moves, Direction dir, const int x,
                                          const int y, const std::vector<std::vector<int8_t>>& board)
  {
    uint8_t count = 1;
    const uint8_t BOARD_MIN = 0;
    const uint8_t BOARD_MAX = board.size()-1;
    
    switch (dir)
    {
      case Direction::UP:
      {
        while (y-count >= BOARD_MIN)
        {
          if (board[y-count][x] == -1)
          {
            moves.push_back(std::pair<uint8_t, uint8_t>{y-count, x});
          }
          else
          {
            if (colors_are_different(board[y][x], board[y-count][x]))
            {
              moves.push_back(std::pair<uint8_t, uint8_t>{y-count, x});
            }
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
          if (board[y-count][x+count] == -1)
          {
            moves.push_back(std::pair<uint8_t, uint8_t>{y-count, x+count});
          }
          else
          {
            if (colors_are_different(board[y][x], board[y-count][x+count]))
            {
              moves.push_back(std::pair<uint8_t, uint8_t>{y-count, x+count});
            }
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
          if (board[y][x+count] == -1)
          {
            moves.push_back(std::pair<uint8_t, uint8_t>{y, x+count});
          }
          else
          {
            if (colors_are_different(board[y][x], board[y][x+count]))
            {
              moves.push_back(std::pair<uint8_t, uint8_t>{y, x+count});
            }
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
          if (board[y+count][x+count] == -1)
          {
            moves.push_back(std::pair<uint8_t, uint8_t>{y+count, x+count});
          }
          else
          {
            if (colors_are_different(board[y][x], board[y+count][x+count]))
            {
              moves.push_back(std::pair<uint8_t, uint8_t>{y+count, x+count});
            }
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
          if (board[y+count][x] == -1)
          {
            moves.push_back(std::pair<uint8_t, uint8_t>{y+count, x});
          }
          else
          {
            if (colors_are_different(board[y][x], board[y+count][x]))
            {
              moves.push_back(std::pair<uint8_t, uint8_t>{y+count, x});
            }
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
          if (board[y+count][x-count] == -1)
          {
            moves.push_back(std::pair<uint8_t, uint8_t>{y+count, x-count});
          }
          else
          {
            if (colors_are_different(board[y][x], board[y+count][x-count]))
            {
              moves.push_back(std::pair<uint8_t, uint8_t>{y+count, x-count});
            }
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
          if (board[y][x-count] == -1)
          {
            moves.push_back(std::pair<uint8_t, uint8_t>{y, x-count});
          }
          else
          {
            if (colors_are_different(board[y][x], board[y][x-count]))
            {
              moves.push_back(std::pair<uint8_t, uint8_t>{y, x-count});
            }
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
          if (board[y-count][x-count] == -1)
          {
            moves.push_back(std::pair<uint8_t, uint8_t>{y-count, x-count});
          }
          else
          {
            if (colors_are_different(board[y][x], board[y-count][x-count]))
            {
              moves.push_back(std::pair<uint8_t, uint8_t>{y-count, x-count});
            }
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
  
  virtual PairsList calculate_possible_moves(const std::vector<std::vector<int8_t>>& board, const uint8_t turn) = 0;

protected:
  glm::vec2 position_;
  glm::vec2 size_;
  Color game_color_;
  Texture2D texture_;
  glm::vec3 color_;
  bool is_king_ = false;
  bool is_pawn_ = false;
  bool has_moved_ = false;
};

#endif /* piece_hpp */
