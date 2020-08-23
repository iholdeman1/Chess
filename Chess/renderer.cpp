//
//  renderer.cpp
//  Chess
//
//  Created by Ian Holdeman on 8/2/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

// Local Includes
#include "renderer.hpp"

Renderer::Renderer()
{
  float vertices[] = {
    // Position // Texture
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
  };
  
  unsigned int vbo;
  
  // Generate objects
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo);

  // Bind the data
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Enable both attributes in the VAO
  glBindVertexArray(vao_);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
  
  // Un-bind our objects
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

Renderer::~Renderer()
{
  glDeleteVertexArrays(1, &vao_);
}

void Renderer::render_basic_object(const glm::vec2& position, const glm::vec2& size,
                                   const glm::vec4& color, const float rotate)
{
  // Disable texture attribute
  glBindVertexArray(vao_);
  glDisableVertexAttribArray(1);
  
  // Create model matrix
  const glm::mat4 model = generate_model_matrix(position, size, rotate);
  
  // Set up the shader
  ResourceManager::get_shader("board").use();
  ResourceManager::get_shader("board").set_matrix4("model", model);
  ResourceManager::get_shader("board").set_vector4f("color", color);
  
  // Render
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void Renderer::render_textured_object(const Texture2D& texture, const glm::vec2& position,
                                      const glm::vec2& size, const glm::vec3& color, const float rotate)
{
  // Enable texture attribute
  glBindVertexArray(vao_);
  glEnableVertexAttribArray(1);
  
  // Create model matrix
  const glm::mat4 model = generate_model_matrix(position, size, rotate);

  // Set up the shader
  ResourceManager::get_shader("texture").use();
  ResourceManager::get_shader("texture").set_matrix4("model", model);
  ResourceManager::get_shader("texture").set_vector3f("spriteColor", color);

  // Set texture
  glActiveTexture(GL_TEXTURE0);
  texture.bind();

  // Render
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

glm::mat4 Renderer::generate_model_matrix(const glm::vec2& position, const glm::vec2& size, const float rotate)
{
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(position, 0.0f));
  model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
  model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
  model = glm::scale(model, glm::vec3(size, 1.0f));
  
  return model;
}
