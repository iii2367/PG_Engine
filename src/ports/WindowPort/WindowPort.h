#include <SDL3/SDL.h>
#include <string>

struct WindowConfig {
  int width;
  int height;
  std::string title;
};

class IWindowPort {

public:
  virtual ~IWindowPort() = default;

  // Створення вікна
  virtual void CreateWindow(const WindowConfig &config) = 0;

  // Основний цикл рендерингу
  virtual void RenderFrame() = 0;

  // Обробка подій
  virtual bool PollEvents() = 0;

  // Закриття вікна
  virtual void CloseWindow() = 0;
};
