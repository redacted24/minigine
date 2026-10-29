#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>

#include "camera.h"
#include "stb_image/stb_image.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
      MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
  Position = position;
  WorldUp = up;
  Yaw = yaw;
  Pitch = pitch;
  updateCameraVectors();
  spdlog::debug(
      "Initialized camera through vectors with position ({}, {}, {}). ",
      position.x, position.y, position.z);
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY,
               float upZ, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
      MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
  Position = glm::vec3(posX, posY, posZ);
  WorldUp = glm::vec3(upX, upY, upZ);
  Yaw = yaw;
  Pitch = pitch;
  updateCameraVectors();
  spdlog::debug(
      "Initialized camera through floats with position x:{}, y:{}, z:{}", posX,
      posY, posZ);
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

void Camera::ProcessKeyboard(const bool *state, float deltaTime) {
  glm::vec3 velocity_vector = glm::vec3(0);
  float speed = MovementSpeed * deltaTime;
  if (state[SDL_SCANCODE_W]) {
    velocity_vector += Front;
  };
  if (state[SDL_SCANCODE_S]) {
    velocity_vector -= Front;
  };
  if (state[SDL_SCANCODE_A]) {
    velocity_vector -= Right;
  };
  if (state[SDL_SCANCODE_D]) {
    velocity_vector += Right;
  };
  if (state[SDL_SCANCODE_LSHIFT]) {
    velocity_vector -= WorldUp;
  };
  if (state[SDL_SCANCODE_SPACE]) {
    velocity_vector += WorldUp;
  }
  if (glm::length(velocity_vector) != 0) {
    Position += glm::normalize(velocity_vector) * speed;
  }
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset,
                                  GLboolean constrainPitch) {
  xoffset *= MouseSensitivity;
  yoffset *= MouseSensitivity;

  Yaw += xoffset;
  Pitch += yoffset;

  // make sure that when pitch is out of bounds, screen doesn't get flipped
  if (constrainPitch) {
    if (Pitch > 89.0f)
      Pitch = 89.0f;
    if (Pitch < -89.0f)
      Pitch = -89.0f;
  }

  // update Front, Right and Up Vectors using the updated Euler angles
  updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
  Zoom -= (float)yoffset;
  if (Zoom < 1.0f)
    Zoom = 1.0f;
  if (Zoom > 45.0f)
    Zoom = 45.0f;
}
