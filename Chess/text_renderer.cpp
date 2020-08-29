//
//  text_renderer.cpp
//  Chess
//
//  Created by Ian Holdeman on 8/28/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#include "text_renderer.hpp"

// Library Includes
#include <ft2build.h>
#include FT_FREETYPE_H

// System Includes
#include <iostream>

TextRenderer::TextRenderer()
{
  // Generate objects
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);

  // Bind the data
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

  // Enable both attributes in the VAO
  glBindVertexArray(vao_);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  // Un-bind our objects
  glBindVertexArray(0);
}

TextRenderer::~TextRenderer()
{
  glDeleteVertexArrays(1, &vao_);
}

void TextRenderer::load(const std::string font, const uint8_t font_size)
{
  characters_.clear();
  
  FT_Library ft;
  if (FT_Init_FreeType(&ft))
  {
    std::cerr << "Error::FreeType: Could not initialize FreeType library\n";
  }
  
  // Load font as face
  FT_Face face;
  if (FT_New_Face(ft, font.c_str(), 0, &face))
  {
    std::cerr << "Error::FreeType: Failed to load font: " << font << "\n";
  }
  
  // Set size to load glyphs as
  FT_Set_Pixel_Sizes(face, 0, font_size);
  
  // Disable byte-alignment restriction
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  
  // Then for the first 128 ASCII characters, pre-load/compile their characters and store them
  for (GLubyte c = 0; c < 128; c++)
  {
    // Load character glyph
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
      std::cerr << "Error::FreeType: Failed to load Glyph\n";
      continue;
    }

    // Generate texture
    uint32_t texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                 face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                 face->glyph->bitmap.buffer);
    
    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   
    // Now store character for later use
    Character character{
      texture,
      glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
      glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
      face->glyph->advance.x
    };
    characters_.insert(std::pair<char, Character>(c, character));
  }
  glBindTexture(GL_TEXTURE_2D, 0);
  
  // Destroy FreeType once we're finished
  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}

void TextRenderer::render_text(const std::string text, float x, const float y,
                               const float scale, const glm::vec4& color)
{
  // Activate corresponding render state
  ResourceManager::get_shader("font").use();
  ResourceManager::get_shader("font").set_vector3f("textColor", color);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(vao_);

  // Iterate through all characters
  std::string::const_iterator c;
  for (c = text.begin(); c != text.end(); c++)
  {
    Character ch = characters_[*c];

    const float xpos = x + ch.bearing.x * scale;
    const float ypos = y + (characters_['H'].bearing.y - ch.bearing.y) * scale;

    const float w = ch.size.x * scale;
    const float h = ch.size.y * scale;
    
    // Update VBO for each character
    float vertices[6][4] = {
      { xpos,     ypos + h,   0.0f, 1.0f },
      { xpos + w, ypos,       1.0f, 0.0f },
      { xpos,     ypos,       0.0f, 0.0f },

      { xpos,     ypos + h,   0.0f, 1.0f },
      { xpos + w, ypos + h,   1.0f, 1.0f },
      { xpos + w, ypos,       1.0f, 0.0f }
     };

    // Render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.texture_id);
    
    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    // Now advance cursors for next glyph
    // Bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
    x += (ch.advance >> 6) * scale;
  }

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}
