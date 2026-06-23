#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "../ports/GFXPort/GFXPort.h"

class ResourceManager
{
public:
    explicit ResourceManager(IGFXPort& gfx) : gfx(gfx) {}

    int loadTexture(const std::string& path)
    {
        auto it = textures.find(path);
        if (it != textures.end()) { return it->second; }

        int id = gfx.loadImage(path);

        if (id >= 0) { textures[path] = id; }

        return id;
    }

private:
    IGFXPort& gfx;

    std::unordered_map<std::string, int> textures;
};

#endif
