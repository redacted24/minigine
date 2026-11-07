#ifndef RENDERABLE_H
#define RENDERABLE_H

/**
 * @class Renderable
 * @brief Mixin for anything that can be rendered to the screen.
 *
 */
class Renderable {
public:
  virtual void render() = 0;
  virtual int render_setup() = 0;
};

#endif // RENDERABLE_H
