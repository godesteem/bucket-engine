/**
 * File              : Layer.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 17.02.2020
 * Last Modified Date: 17.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "engine/Core.h"
#include "engine/events/Event.h"

namespace Engine {
  
  class BE_API Layer
  {
    public:
      Layer(const std::string& name = "Layer");
      virtual ~Layer();

      virtual void OnAttach() {};
      virtual void OnDetach() {};
      virtual void OnUpdate() {};
      virtual void OnEvent(Event& event) {};

      inline const std::string& GetName() const {return m_DebugName; };
    protected:
      std::string m_DebugName;
  };

}
