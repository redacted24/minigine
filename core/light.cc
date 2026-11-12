#include "light.h"
#include "glad/glad.h"

Light::Light() { glGenVertexArrays(1, &VAO); }
void Light::render() { return; }
