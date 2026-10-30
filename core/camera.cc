#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>

#include "camera.h"
#include "stb_image/stb_image.h"

Camera::Camera(glm::vec3 p_position, glm::vec3 p_up, float p_yaw, float p_pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
      MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
  Position = p_position;
  WorldUp = p_up;
  Yaw = p_yaw;
  Pitch = p_pitch;
  updateCameraVectors();
  spdlog::debug(
      "Initialized camera through vectors with position ({}, {}, {}). ",
      p_position.x, p_position.y, p_position.z);
}

Camera::Camera(float p_pos_x, float p_pos_y, float p_pos_z, float p_up_x,
               float p_up_y, float p_up_z, float p_yaw, float p_pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
      MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
  Position = glm::vec3(p_pos_x, p_pos_y, p_pos_z);
  WorldUp = glm::vec3(p_up_x, p_up_y, p_up_z);
  Yaw = p_yaw;
  Pitch = p_pitch;
  updateCameraVectors();
  spdlog::debug(
      "Initialized camera through floats with position x:{}, y:{}, z:{}",
      p_pos_x, p_pos_y, p_pos_z);
}

void Camera::updateCameraVectors() {
  // Calculate new Front Vector
  glm::vec3 front;
  front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  front.y = sin(glm::radians(Pitch));
  front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  Front = glm::normalize(front);
  // recalculate Right and Up vectors
  Right = glm::normalize(glm::cross(Front, WorldUp));
  Up = glm::normalize(glm::cross(Right, Front));
}

glm::mat4 Camera::GetViewMatrix() {
  return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(const bool *p_state, float p_delta_time) {
  glm::vec3 velocity_vector = glm::vec3(0);
  float speed = MovementSpeed * p_delta_time;
  if (p_state[SDL_SCANCODE_W]) {
    velocity_vector += Front;
  };
  if (p_state[SDL_SCANCODE_S]) {
    velocity_vector -= Front;
  };
  if (p_state[SDL_SCANCODE_A]) {
    velocity_vector -= Right;
  };
  if (p_state[SDL_SCANCODE_D]) {
    velocity_vector += Right;
  };
  if (p_state[SDL_SCANCODE_LSHIFT]) {
    velocity_vector -= WorldUp;
  };
  if (p_state[SDL_SCANCODE_SPACE]) {
    velocity_vector += WorldUp;
  }
  if (glm::length(velocity_vector) != 0) {
    Position += glm::normalize(velocity_vector) * speed;
  }
}

void Camera::ProcessMouseMovement(float p_xoffset, float p_yoffset,
                                  GLboolean p_constrain_pitch) {
  p_xoffset *= MouseSensitivity;
  p_yoffset *= MouseSensitivity;

  Yaw += p_xoffset;
  Pitch += p_yoffset;

  // make sure that when pitch is out of bounds, screen doesn't get flipped
  if (p_constrain_pitch) {
    if (Pitch > 89.0f) {
      Pitch = 89.0f;
    }
    if (Pitch < -89.0f) {
      Pitch = -89.0f;
    }
  }

  // update Front, Right and Up Vectors using the updated Euler angles
  updateCameraVectors();
}

void Camera::ProcessMouseScroll(float p_yoffset) {
  Zoom -= (float)p_yoffset;
  if (Zoom < 1.0f) {
    Zoom = 1.0f;
  }
  if (Zoom > 45.0f) {
    Zoom = 45.0f;
  }
}
