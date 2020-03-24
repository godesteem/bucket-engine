/**
 * File              : LayerStack.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 17.02.2020
 * Last Modified Date: 17.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "Core.h"
#include "Layer.h"

#include <vector>

namespace Engine {
  
  class BE_API LayerStack
  {
    public:
      LayerStack();
      ~LayerStack();

      void PushLayer(Layer* layer);
      void PushOverlay(Layer* overlay);
      void PopLayer(Layer* layer);
      void PopOverlay(Layer* overlay);

      std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
      std::vector<Layer*>::iterator end() { return m_Layers.end(); }

    private:
      std::vector<Layer*> m_Layers;
      unsigned int m_LayerInsertIndex = 0;
  };

}
