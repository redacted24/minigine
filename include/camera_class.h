#ifndef PERLIN_INCLUDE_CAMERA_CLASS_H
#define PERLIN_INCLUDE_CAMERA_CLASS_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT };

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
 public:
  // Camera Attributes
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Right;
  glm::vec3 WorldUp;
  // Euler Angles
  float Yaw;
  float Pitch;
  // Camera Options
  float MovementSpeed;
  float MouseSensitivity;
  float Zoom;

  // Constructor with Vectors
  Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);

  // Constructor with scalar values
  Camera(float poX, float posY, float posZ, float upX, float upY, float upZ,
         float yaw, float pitch);

  // Returns view matrix calculated with Euler Angles and LookAt Matrix
  glm::mat4 GetViewMatrix();

  // Process keyboard inputs
  void ProcessKeyboard(CameraMovement direction, float deltaTime);

  // Process mouse inputs
  void ProcessMouseMovement(float xoffset, float yoffset,
                            GLboolean constrainPitch);

  // Process mouse scrolling
  void ProcessMouseScroll(float yoffset);

 private:
  // Calculate front vector from Camera's updated Euler Angles
  void updateCameraVectors();
};

#endif  // PERLIN_INCLUDE_CAMERA_CLASS_H
