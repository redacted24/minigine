#ifndef CAMERA_H
#define CAMERA_H

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

  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
         float pitch = PITCH);
  Camera(float poX, float posY, float posZ, float upX, float upY, float upZ,
         float yaw, float pitch);

  /**
   * @brief Returns view matrix calculated with Euler Angles and LookAt Matrix
   */
  glm::mat4 GetViewMatrix();

  /**
   * @brief Process keyboard inputs
   *
   * @param direction An element from the CameraMovement enum, indicating the
   * direction of movement
   * @param deltaTime time elapsed since last processed frame
   */
  void ProcessKeyboard(CameraMovement direction, float deltaTime);

  /**
   * @brief Process mouse inputs and change yaw and pitch based on input.
   *
   * @param xoffset the amount moved in x, relative to the last mouse position
   * @param yoffset the amount moved in y, relative to the last mouse position
   * @param constrainPitch whether to lock the pitch to feet and ceiling.
   */
  void ProcessMouseMovement(float xoffset, float yoffset,
                            GLboolean constrainPitch = true);

  /**
   * @brief Process mouse scroll action.
   *
   * @param yoffset Y position offset since last mouse position
   */
  void ProcessMouseScroll(float yoffset);

private:
  /**
   * @brief Calculate front vector from Camera's updated Euler Angles
   */
  void updateCameraVectors();
};

#endif // CAMERA_CLASS_H
