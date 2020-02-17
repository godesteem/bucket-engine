/**
 * File              : Event.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 17.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "../Core.h"
#include "bepch.h"

namespace Engine {
  
  // Non buffered Event
  //
  enum class EventType {
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyReleased,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
  };

  enum EventCategory {
    None = 0,
    EventCategoryApplication = BIT(0),
    EventCategoryInput = BIT(1),
    EventCategoryKeyboard = BIT(2),
    EventCategoryMouse = BIT(3),
    EventCategoryMouseButton = BIT(4),
  };

#ifndef EVENT_CLASS_TYPE
  #define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){return Engine::EventType::type; }\
      virtual EventType GetEventType() const override {return GetStaticType();} \
      virtual const char* GetName() const override {return #type;}
#endif
#ifndef EVENT_CLASS_CATEGORY
  #define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}
#endif
  class BE_API Event
  {
    friend class EventDispatcher;
  public:
    virtual EventType GetEventType() const = 0;
    virtual const char *GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return GetName(); }

    inline bool IsInCategory(EventCategory category){
      return GetCategoryFlags() && category;
    }
  protected:
    bool m_Handled = false;

  };

  class EventDispatcher
  {
    template<typename T>
    using EventFn = std::function<bool(T&)>;

  public:
    EventDispatcher(Event &event)
      :m_Event(event) {}
    
    template<typename T>
    bool Dispatch(EventFn<T> func){
      if(m_Event.GetEventType() == T::GetStaticType()){
        m_Event.m_Handled = func(*(T*)&m_Event);
        return true;
      }
      return false;
    }

  private:
    Event& m_Event;
  };

  inline std::ostream& operator << (std::ostream& os, const Event& e){
    return os << e.ToString();
  }
}
