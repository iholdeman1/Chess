//
//  main.cpp
//  Chess
//
//  Created by Ian Holdeman on 8/1/20.
//  Copyright © 2020 Marvin LLC. All rights reserved.
//

// Library Includes
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

// System Includes
#include <iostream>

// Local Includes
#include "game.hpp"

// Constants
const uint32_t SCREEN_WIDTH = 800;
const uint32_t SCREEN_HEIGHT = 800;

// Callbacks
void frame_buffer_size_callback(GLFWwindow *window, const int width, const int height);
void key_callback(GLFWwindow *window, const int key, const int scancode, const int action, const int mods);
void mouse_callback(GLFWwindow *window, const int button, const int action, const int mods);

// Make the game
Game chess(SCREEN_WIDTH, SCREEN_HEIGHT);

// Kill function
void kill_glfw()
{
  glfwTerminate();
}

int main()
{
  // Initialize GLFW
  if (!glfwInit())
  {
    std::cerr << "GLFW failed to initialize! Quitting program...\n";
    return -1;
  }
  
  // Setup windows
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, false);
  
  GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess", nullptr, nullptr);
  
  if (window == nullptr)
  {
    std::cerr << "Failed to create GLFW window\n";
    kill_glfw();
    return -1;
  }
  
  glfwMakeContextCurrent(window);
  
  // Set Callbacks
  glfwSetKeyCallback(window, key_callback);
  glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
  glfwSetMouseButtonCallback(window, mouse_callback);

  // Set the viewport (handles retina display)
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  // Enable stuff
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  // Initialize the game
  chess.init();

  // Time variables
  float delta_time = 0.0;
  float last_frame = 0.0;
  
  // Game loop
  while (!glfwWindowShouldClose(window))
  {
    // Timing logic
    const float current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;
    
    // Handle inputs
    glfwPollEvents();
    
    // Update
    chess.update(delta_time);
    
    // Reset color buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Render
    chess.render();
    
    glfwSwapBuffers(window);
  }

  // Kill program
  glfwDestroyWindow(window);
  kill_glfw();
  return 0;
}

// Callback to handle resizing the window
void frame_buffer_size_callback(GLFWwindow *window, const int width, const int height)
{
  glViewport(0, 0, width, height);
}

// Callback to handle key input
void key_callback(GLFWwindow *window, const int key, const int scancode,
                  const int action, const int mods)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
}

// Callback to handle mouse input
void mouse_callback(GLFWwindow *window, const int button, const int action, const int mods)
{
  if (button == GLFW_MOUSE_BUTTON_LEFT)
  {
    switch (action)
    {
      case GLFW_PRESS:
        chess.handle_mouse_down();
        break;
      case GLFW_RELEASE:
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        if (x != NULL && y != NULL)
        {
          chess.handle_mouse_up(x, y);
        }
        break;
      default:
        break;
    }
  }
}
