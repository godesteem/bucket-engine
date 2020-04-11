#pragma once
#include "Event.h"

namespace Engine {
  class BE_API WindowResizeEvent: public Event
  {
    public:
      WindowResizeEvent(unsigned int width, unsigned int height)
        : m_Width(width), m_Height(height) {}

      inline unsigned int GetWidth() const {return m_Width; }
      inline unsigned int GetHeight() const {return m_Height;}

      std::string ToString() const override {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << GetWidth() << ", " << GetHeight();
        return ss.str();
      }

      EVENT_CLASS_TYPE(WindowResize)
      EVENT_CLASS_CATEGORY(EventCategory::Application)
    private:
      unsigned int m_Width, m_Height;
  };

  class BE_API WindowCloseEvent: public Event
  {
    public:
      WindowCloseEvent() {}

      EVENT_CLASS_TYPE(WindowClose)
      EVENT_CLASS_CATEGORY(EventCategory::Application)
  };
  class BE_API WindowMovedEvent: public Event
  {
    public:
      WindowMovedEvent() {}

      EVENT_CLASS_TYPE(WindowMoved)
      EVENT_CLASS_CATEGORY(EventCategory::Application)
  };

  class BE_API WindowFocusEvent: public Event
  {
    public:
      WindowFocusEvent() {}

      EVENT_CLASS_TYPE(WindowFocus)
      EVENT_CLASS_CATEGORY(EventCategory::Application)
  };

  class BE_API WindowLostFocusEvent: public Event
  {
    public:
      WindowLostFocusEvent() {}

      EVENT_CLASS_TYPE(WindowLostFocus)
      EVENT_CLASS_CATEGORY(EventCategory::Application)
  };


  class BE_API AppTickEvent: public Event
  {
    public:
      AppTickEvent() {}

      EVENT_CLASS_TYPE(AppTick)
      EVENT_CLASS_CATEGORY(EventCategory::Application)
  };

  class BE_API AppUpdateEvent: public Event
  {
    public:
      AppUpdateEvent() {}

      EVENT_CLASS_TYPE(AppUpdate)
      EVENT_CLASS_CATEGORY(EventCategory::Application)
  };

  class BE_API AppRenderEvent: public Event
  {
    public:
      AppRenderEvent() {}

      EVENT_CLASS_TYPE(AppRender)
      EVENT_CLASS_CATEGORY(EventCategory::Application)
  };
}
