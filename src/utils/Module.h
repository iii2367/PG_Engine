#ifndef MODULE_DLL_H
#define MODULE_DLL_H

#include <stdexcept>
#include <string>
#include <windows.h>

namespace Utils {
template <class Type> class Module {
public:
  Module() = default;
  ~Module() { unload(); }

  Module(const Module &) = delete;
  Module &operator=(const Module &) = delete;
  Module(Module &&) = default;
  Module &operator=(Module &&) = default;
  Type* operator->() { if (!instance) { throw std::runtime_error("Instance is not created"); } return instance; }

  bool load(const std::string &dllPath, const std::string &createName,
            const std::string &destroyName) {
    if (dll_is_load) {
      throw std::runtime_error("DLL already loaded: " + dllPath);
    }

    hDll = LoadLibraryA(dllPath.c_str());
    if (!hDll) {
      DWORD err = GetLastError();
      LPSTR msgBuf = nullptr;
      FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                         FORMAT_MESSAGE_FROM_SYSTEM,
                     NULL, err, 0, (LPSTR)&msgBuf, 0, NULL);
      printf("Failed to load DLL: %s\nError %lu: %s\n", dllPath.c_str(), err,
             msgBuf);
      LocalFree(msgBuf);
      throw std::runtime_error("Failed to load DLL: " + dllPath);
    }

    createFunc =
        reinterpret_cast<Type *(*)()>(GetProcAddress(hDll, createName.c_str()));
    if (!createFunc) {
      unload();
      throw std::runtime_error("Failed to load function: " + createName);
    }

    destroyFunc = reinterpret_cast<void (*)(Type *)>(
        GetProcAddress(hDll, destroyName.c_str()));
    if (!destroyFunc) {
      unload();
      throw std::runtime_error("Failed to load function: " + destroyName);
    }

    instance = createFunc();
    if (!instance) {
      unload();
      throw std::runtime_error("Failed to create instance");
    }

    dll_is_load = true;
    pathDllNow = dllPath;
    return true;
  }

  void unload() {
    if (!dll_is_load) {
      return;
    }

    if (instance && destroyFunc) {
      destroyFunc(instance);
      instance = nullptr;
    }

    if (hDll) {
      FreeLibrary(hDll);
      hDll = nullptr;
    }

    destroyFunc = nullptr;
    createFunc = nullptr;
    dll_is_load = false;
    pathDllNow.clear();
  }

  bool isLoaded() const { return dll_is_load; }
  Type *getInstance() const { return instance; }

private:
  HMODULE hDll = nullptr;
  bool dll_is_load = false;
  std::string pathDllNow;

  Type *instance = nullptr;
  Type *(*createFunc)() = nullptr;
  void (*destroyFunc)(Type *) = nullptr;
};
} // namespace Utils

#endif
