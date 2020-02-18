/**
 * File              : MouseEvent.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 18.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "Event.h"

namespace Engine {
  
  class BE_API MouseMovedEvent: public Event
  {
    public:
      MouseMovedEvent(float x, float y)
        : m_MouseX(x), m_MouseY(y) {}

      inline float GetX() const { return m_MouseX; }
      inline float GetY() const { return m_MouseY; }
      
      std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << GetX() << ", " << GetY();
        return ss.str();
      }

      EVENT_CLASS_TYPE(MouseMoved)
      EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    protected:
      float m_MouseX, m_MouseY;
  };

  class BE_API MouseScrollEvent: public Event
  {
    public:
      MouseScrollEvent(float xOffset, float yOffset)
        : m_XOffset(xOffset), m_YOffset(yOffset) {}

      inline float GetXOffset() const { return m_XOffset; }
      inline float GetYOffset() const { return m_YOffset; }

      std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseScrollEvent: " << GetXOffset() << ", " << GetYOffset();
        return ss.str();
      }

      EVENT_CLASS_TYPE(MouseScrolled)
      EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
      float m_XOffset, m_YOffset;
  };

  class BE_API MouseButtonEvent: public Event
  {
    public:
      inline int GetMouseButton() const { return m_Button; }
      
      EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)
    protected:
      MouseButtonEvent(int button)
        : m_Button(button) {}

      int m_Button;
  };

  class BE_API MouseButtonPressedEvent: public MouseButtonEvent
  {
    public:
      MouseButtonPressedEvent(int button)
        : MouseButtonEvent(button) {}

      std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_Button;
        return ss.str();
      }

      EVENT_CLASS_TYPE(MouseButtonPressed)
  };
  class BE_API MouseButtonReleasedEvent: public MouseButtonEvent
  {
    public:
      MouseButtonReleasedEvent(int button)
        : MouseButtonEvent(button) {}

      std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_Button;
        return ss.str();
      }

      EVENT_CLASS_TYPE(MouseButtonPressed)
  };


}
