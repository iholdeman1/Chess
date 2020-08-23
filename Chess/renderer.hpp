//
//  renderer.hpp
//  Chess
//
//  Created by Ian Holdeman on 8/2/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#ifndef renderer_hpp
#define renderer_hpp

// Library Includes
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

// Local Includes
#include "resource_manager.hpp"

class Renderer
{
public:
  Renderer();
  ~Renderer();
  
  void render_basic_object(const glm::vec2& position, const glm::vec2& size,
                           const glm::vec4& color, const float rotate);
  
  void render_textured_object(const Texture2D& texture, const glm::vec2& position,
                              const glm::vec2& size, const glm::vec3& color, const float rotate);
  
private:
  glm::mat4 generate_model_matrix(const glm::vec2& position, const glm::vec2& size, const float rotate);
  
  uint32_t vao_ = 0;
};

#endif /* renderer_hpp */
