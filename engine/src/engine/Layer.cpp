/**
 * File              : Layer.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 17.02.2020
 * Last Modified Date: 17.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "Layer.h"

namespace Engine {
  Layer::Layer(const std::string& name)
    : m_DebugName(name) {}

  Layer::~Layer(){}
}
