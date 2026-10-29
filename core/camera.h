#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT, DOWN, UP };

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 7.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Right;
  glm::vec3 Up;
  glm::vec3 WorldUp;

  float Yaw;
  float Pitch;

  float MovementSpeed;
  float MouseSensitivity;
  float Zoom;

  Camera(glm::vec3 p_position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 p_up = glm::vec3(0.0f, 1.0f, 0.0f), float p_yaw = YAW,
         float p_pitch = PITCH);
  Camera(float p_po_x, float p_pos_y, float p_pos_z, float p_up_x, float p_up_y,
         float p_up_z, float p_yaw, float p_pitch);

  glm::mat4 GetViewMatrix();

  void ProcessKeyboard(const bool *p_state, float p_delta_time);

  void ProcessMouseMovement(float p_xoffset, float p_yoffset,
                            GLboolean p_constrain_pitch = true);

  void ProcessMouseScroll(float p_yoffset);

private:
  void updateCameraVectors();
};

#endif // CAMERA_CLASS_H
