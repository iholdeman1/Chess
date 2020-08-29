//
//  text_renderer.hpp
//  Chess
//
//  Created by Ian Holdeman on 8/28/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#ifndef text_renderer_hpp
#define text_renderer_hpp

// Library Includes
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include "glm.hpp"

// System Includes
#include <map>

// Local Includes
#include "resource_manager.hpp"
#include "shader.hpp"
#include "texture.hpp"

class TextRenderer {
public:
  TextRenderer();
  ~TextRenderer();
  
  void load(const std::string font, const uint8_t font_size);
  void render_text(const std::string text, float x, const float y,
                   const float scale, const glm::vec4& color = glm::vec4(1.0f));

private:
  
  struct Character {
    uint32_t texture_id;
    glm::ivec2 size;
    glm::ivec2 bearing;
    long advance;
  };
  
  uint32_t vao_;
  uint32_t vbo_;
  std::map<char, Character> characters_;
};


#endif /* text_renderer_hpp */
