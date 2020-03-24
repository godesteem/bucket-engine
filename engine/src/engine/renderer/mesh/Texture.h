/**
 * File              : Texture.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 25.02.2020
 * Last Modified Date: 25.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once
#include <string>
#include "engine/core/Core.h"

namespace Engine {
  class Texture
  {
  public:
    virtual ~Texture() = default;

    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;
    virtual void Bind(uint32_t slot = 0) const = 0;
  };

  class Texture2D: public Texture
  {
  public:
    static Ref<Texture2D> Create(const std::string& path);
  };
}
