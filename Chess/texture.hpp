//
//  texture.hpp
//  Chess
//
//  Created by Ian Holdeman on 8/2/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

#ifndef texture_hpp
#define texture_hpp

// Library Includes
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

class Texture2D
{
public:
  Texture2D(const int width = 0, const int height = 0);
  
  void generate(unsigned char *data);
  void bind();

  void set_alpha_format();

  unsigned int get_id() const { return id_; };
  unsigned int& get_id_ref() { return id_; };
  
private:
  // Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
  unsigned int id_;
  
  // Texture image dimensions
  int width_;
  int height_;
  
  // Texture Format
  unsigned int image_format_ = GL_RGB; // Format of loaded image
  unsigned int internal_format_ = GL_RGB; // Format of texture object
};

#endif /* texture_hpp */
