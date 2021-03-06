#pragma once

#include "bepch.h"

#include "Core.h"
#include "events/Event.h"

namespace Engine {
  
  struct WindowProps {
    std::string Title;
    unsigned int Width;
    unsigned int Height;

    // TODO: Game settings
    WindowProps(const std::string &title = "Bucket Engine",
                const unsigned int width = 1280,
                const unsigned int height = 720)
        : Title(title), Width(width), Height(height) {}
  };

  class BE_API Window
  {
    public:
      using EventCallbackFn = std::function<void(Event&)>;

      virtual ~Window() = default;
      virtual void OnUpdate() const = 0;

      virtual unsigned int GetWidth() const = 0;
      virtual unsigned int GetHeight() const = 0;

      virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

      virtual void SetFullScreen() = 0;
      virtual void Resize(WindowProps props) = 0;

      virtual void SetVSync(bool enabled) = 0;
      virtual bool IsVSync() const = 0;

      virtual void* GetNativeWindow() const = 0;

      static Window* Create(const WindowProps& props = WindowProps());
  };

}
