/**
 * File              : X11Window.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 16.02.2020
 * Last Modified Date: 18.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "engine/Window.h"
#include "engine/renderer/GraphicsContext.h"

namespace Engine {
  
  class X11Window: public Window {
  
    public:
      X11Window(const WindowProps& props);
      virtual ~X11Window();

      void OnUpdate() const override;

      inline unsigned int GetWidth() const override { return m_Data.Width; };
      inline unsigned int GetHeight() const override { return m_Data.Height; };

      inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; };
      virtual void SetFullScreen() override;
      virtual void Resize(WindowProps props) override;
      void SetVSync(bool enabled) override;
      bool IsVSync() const override;

      inline void* GetNativeWindow() const override { return m_Window; };
    private:
      virtual void Init(const WindowProps& props);
      virtual void ShutDown();

      GLFWwindow* m_Window;
      GraphicsContext* m_Context;

      struct WindowData {
        std::string Title;
        unsigned int Height, Width;
        bool VSync;

        EventCallbackFn EventCallback;
      };

      WindowData m_Data;
  };

}
