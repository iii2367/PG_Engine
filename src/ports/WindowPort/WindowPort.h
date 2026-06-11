#ifndef WINDOWPORT
#define WINDOWPORT

#include <string>

struct WindowConfig {
  int width = 0;
  int height = 0;
  std::string title;
};

struct IWindowPort {
  virtual ~IWindowPort() = default;

  // Створення вікна
  virtual void createWindow(const WindowConfig &config) = 0;

  // Основний цикл рендерингу
  virtual void RenderFrame() = 0;

  // Обробка подій
  virtual bool PollEvents() = 0;

  // Закриття вікна
  virtual void CloseWindow() = 0;
};

#endif // WINDOWPORT-макрос
