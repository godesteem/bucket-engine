/**
 * Usage:
 *  - define EventType
 *  - define EventCategory
 *  - inherit Event
 *  - implement virtual's
 *  - add EVENT_CLASS_TYPE, EVENT_CLASS_CATEGORY
 *  - initialize event callback
 *  -
 */
#pragma once

#include "engine/core/Core.h"
#include "bepch.h"

namespace Engine {

  // Non buffered Event
  //
  enum class EventType {
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
    BodyEntered, BodyExited
  };

  enum class EventCategory
  {
    None = 0,
    Application = BIT(0),
    Input = BIT(1),
    Keyboard = BIT(2),
    Mouse = BIT(3),
    MouseButton = BIT(4),
    Collision = BIT(5)
  };
  ENABLE_BITMASK_OPERATORS(EventCategory)

#ifndef EVENT_CLASS_TYPE
  #define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){return Engine::EventType::type; }\
      virtual EventType GetEventType() const override {return GetStaticType();} \
      virtual const char* GetName() const override {return #type;}
#endif
#ifndef EVENT_CLASS_CATEGORY
  #define EVENT_CLASS_CATEGORY(category) virtual EventCategory GetCategoryFlags() const override {return category;}
#endif
  class BE_API Event
  {
    friend class EventDispatcher;
  public:
    virtual EventType GetEventType() const = 0;
    virtual const char *GetName() const = 0;
    virtual EventCategory GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return GetName(); }

    inline bool IsInCategory(EventCategory category){
      return static_cast<bool>(GetCategoryFlags() & category);
    }
    bool Handled = false;

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
        m_Event.Handled = func(*(T*)&m_Event);
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
