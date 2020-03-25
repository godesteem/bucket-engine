/**
 * File              : LayerStack.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 17.02.2020
 * Last Modified Date: 17.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "LayerStack.h"

namespace Engine {
  
  LayerStack::LayerStack(){
  }
  LayerStack::~LayerStack(){
    for(Layer* layer: m_Layers){
      delete layer;
    }
  }
  void LayerStack::PushLayer(Layer* layer){
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
    m_LayerInsertIndex++;
  }
  void LayerStack::PushOverlay(Layer* overlay){
    m_Layers.emplace_back(overlay);
  }
  void LayerStack::PopLayer(Layer* layer){
   auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

    if(it != m_Layers.end()){
      m_Layers.erase(it);
      m_LayerInsertIndex--;
    }
  }
  void LayerStack::PopOverlay(Layer* overlay){
   auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
    if(it != m_Layers.end()){
      m_Layers.erase(it);
    }
  }

}