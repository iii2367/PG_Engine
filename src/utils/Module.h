#ifndef MODULE_H
#define MODULE_H

#include <stdexcept>
#include <string>
#include <windows.h>

namespace Utils
{
    template <class Type> 
    class Module 
    {
    public:
        Module() = default;
        ~Module() { unload(); }

        Module(const Module&) = delete;
        Module &operator=(const Module&) = delete;

        Module(Module&& other) noexcept { *this = std::move(other); }

        Module& operator=(Module&& other) noexcept
        {
            if (this != &other)
            {
                unload();

                hDll_ = other.hDll_;
                instance_ = other.instance_;
                createFunc_ = other.createFunc_;
                destroyFunc_ = other.destroyFunc_;
                loaded_ = other.loaded_;

                other.hDll_ = nullptr;
                other.instance_ = nullptr;
                other.createFunc_ = nullptr;
                other.destroyFunc_ = nullptr;
                other.loaded_ = false;
            }
            return *this;
        } 

        bool load(const std::string& dllPath, const std::string& createName, const std::string& destroyName)
        {
            if (loaded_) { throw std::runtime_error("Module already loaded: " + dllPath); }

            hDll_ = LoadLibraryA(dllPath.c_str());
            if (!hDll_) { DWORD err = GetLastError(); throw std::runtime_error("Failed to load DLL: " + dllPath + " (error " + std::to_string(err) + ")"); }          

            createFunc_ = reinterpret_cast<Type*(*)()>(GetProcAddress(hDll_, createName.c_str()));
            if (!createFunc_) { unload(); throw std::runtime_error("Failed to find create function: " + createName); }

            destroyFunc_ = reinterpret_cast<void(*)(Type*)>(GetProcAddress(hDll_, destroyName.c_str()));
            if (!destroyFunc_) { unload(); throw std::runtime_error("Failed to find destroy function: " + destroyName); }

            instance_ = createFunc_();
            if (!instance_) { unload(); throw std::runtime_error("Failed to create module instance"); }

            loaded_ = true;
            return true;
        }

        void unload() 
        {
            if (!loaded_) { return; }
            if (instance_ && destroyFunc_) { destroyFunc_(instance_); instance_ = nullptr; }
            if (hDll_) { FreeLibrary(hDll_); hDll_ = nullptr; }

            destroyFunc_ = nullptr;
            createFunc_ = nullptr;
            loaded_ = false;
        }

        bool isLoaded() const { return loaded_; }
        Type* get() const { return instance_; }
        Type& operator*() const {
        if (!instance_) { throw std::runtime_error("Module not initialized");} return *instance_; }
        Type* operator->() const { if (!instance_) { throw std::runtime_error("Module not initialized"); } return instance_; }

    private:
        HMODULE hDll_ = nullptr;
        bool loaded_ = false;

        Type* instance_ = nullptr;
        Type* (*createFunc_)() = nullptr;
        void (*destroyFunc_)(Type *) = nullptr;
    };
}

#endif
