//
//  piece_manager.hpp
//  Chess
//
//  Created by Ian Holdeman on 8/9/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#ifndef piece_manager_hpp
#define piece_manager_hpp

// Library Includes
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

// System Includes
#include <vector>

// Local Includes
#include "piece.hpp"
#include "bishop.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "queen.hpp"
#include "renderer.hpp"
#include "resource_manager.hpp"
#include "rook.hpp"

class PieceManager
{
public:
  PieceManager(const uint32_t piece_size);
  ~PieceManager();
  
  void render(Renderer *renderer);
  
  const std::vector<std::pair<uint8_t, uint8_t>> get_pieces_moves(const uint8_t id,
                                                                  const std::vector<std::vector<int8_t>>& board,
                                                                  const uint8_t turn) const;
  glm::vec2 get_piece_position(const uint8_t id) const;
  Color get_piece_game_color(const uint8_t id) const;
  void move_piece(const uint8_t id, const glm::vec2& position);
  void delete_piece(const uint8_t id);
  
private:
  void upgrade_pawn(const uint8_t id, const glm::vec2& position, const Color piece_color);
  
  std::vector<Piece*> pieces_;
};

#endif /* piece_manager_hpp */
