//
//  texture.cpp
//  Chess
//
//  Created by Ian Holdeman on 8/2/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#include "texture.hpp"

Texture2D::Texture2D(const int width, const int height)
  : width_(width), height_(height)
{
  glGenTextures(1, &id_);
}

void Texture2D::generate(unsigned char *data)
{
  // Create texture
  glBindTexture(GL_TEXTURE_2D, id_);
  glTexImage2D(GL_TEXTURE_2D, 0, internal_format_, width_, height_, 0, image_format_, GL_UNSIGNED_BYTE, data);

  // Set texture wrap and filter modes
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Unbind texture
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind() const
{
  glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture2D::set_alpha_format()
{
  image_format_ = GL_RGBA;
  internal_format_ = GL_RGBA;
}
