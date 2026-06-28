#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "../ports/GFXPort/GFXPort.h"

class ResourceManager
{
public:
    explicit ResourceManager(IGFXPort& gfx) : gfx(gfx) {}

    ~ResourceManager() { unloadAll(); }

    int loadTexture(const std::string& path)
    {
        auto it = textures.find(path);
        if (it != textures.end()) { return it->second; }

        int id = gfx.loadImage(path);
        if (id >= 0) { textures[path] = id; }

        return id;
    }

    bool unloadTexture(const std::string& path)
    {
        auto it = textures.find(path);
        if (it == textures.end()) { return false; }

        gfx.unloadImage(it->second);
        textures.erase(it);

        return true;
    }

    void unloadAllTextures()
    {
        for (auto& [path, id] : textures) { gfx.unloadImage(id); }

        textures.clear();
    }

    int loadFont(const std::string& path, int size)
    {
        FontKey key{path, size};

        auto it = fonts.find(key);
        if (it != fonts.end()) { return it->second; }

        int id = gfx.loadFont(path, size);

        if (id >= 0) { fonts.emplace(std::move(key), id); }

        return id;
    }
    
    bool unloadFont(const std::string& path, int size)
    {
        FontKey key{path, size};

        auto it = fonts.find(key);
        if (it == fonts.end()) { return false; }

        gfx.unloadFont(it->second);
        fonts.erase(it);

        return true;
    }

    void unloadAllFonts()
    {
        for (auto& [key, id] : fonts) { gfx.unloadFont(id); }

        fonts.clear();
    }

    void unloadAll()
    {
        unloadAllTextures();
        unloadAllFonts();
    }

private:
    IGFXPort& gfx;

    struct FontKey
    {
        std::string path;
        int size;

        bool operator==(const FontKey& other) const
        {
            return path == other.path && size == other.size;
        }
    };

    struct FontKeyHash
    {
        std::size_t operator()(const FontKey& key) const
        {
            std::size_t h1 = std::hash<std::string>{}(key.path);
            std::size_t h2 = std::hash<int>{}(key.size);

            return h1 ^ (h2 << 1);
        }
    };

    std::unordered_map<std::string, int> textures;
    std::unordered_map<FontKey, int, FontKeyHash> fonts;
};

#endif
