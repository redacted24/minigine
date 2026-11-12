#ifndef LIGHT_H
#define LIGHT_H

#include "object.h"
#include "renderable.h"

class Light : public Object, public Renderable {

  // Renderable
  void render() override;
  int render_setup() override;
};

#endif // LIGHT_H
