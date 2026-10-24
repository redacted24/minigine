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

/**
 * @class Camera
 * @brief Class for camera.
 *
 */
class Camera {
public:
  // Camera Attributes
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Right;
  glm::vec3 Up;
  glm::vec3 WorldUp;

  // Euler Angles
  float Yaw;
  float Pitch;

  // Camera options
  float MovementSpeed;
  float MouseSensitivity;
  float Zoom;

  /**
   * @brief Constructor for Camera with vector values.
   *
   * @param position specifies the position of the camera
   * @param up specifies what the camera considers as up.
   * @param yaw
   * @param pitch
   */
  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
         float pitch = PITCH);

  /**
   * @brief Constructor for Camera with scalar values
   *
   * @param poX
   * @param posY
   * @param posZ
   * @param upX
   * @param upY
   * @param upZ
   * @param yaw
   * @param pitch
   */
  Camera(float poX, float posY, float posZ, float upX, float upY, float upZ,
         float yaw, float pitch);

  /**
   * @brief Returns view matrix calculated with Euler Angles and LookAt Matrix
   */
  glm::mat4 GetViewMatrix();

  /**
   * @brief Process keyboard inputs
   *
   * @param direction
   * @param deltaTime
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
   * @param yoffset
   */
  void ProcessMouseScroll(float yoffset);

private:
  /**
   * @brief Calculate front vector from Camera's updated Euler Angles
   */
  void updateCameraVectors();
};

#endif // PERLIN_INCLUDE_CAMERA_CLASS_H
