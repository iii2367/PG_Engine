#ifndef WINDOWHANDLE_H
#define WINDOWHANDLE_H

enum class TypeWindowHandle
{
    SDL3,
};

struct WindowHandle
{
    void* handle;
    TypeWindowHandle type;
    int width;
    int height;
};

#endif 
