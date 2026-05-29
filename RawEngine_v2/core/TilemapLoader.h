#pragma once

#include <vector>
#include <string>
#include <tinyxml2.h>

namespace core {

    struct TilemapData {
        int width;
        int height;
        std::vector<unsigned short> tiles;
    };

    struct TilesetData
    {
        int tileWidth;
        int tileHeight;
        int tilesPerRow;
        int tilesPerCol;
        std::string imagePath;
    };

    class TilemapLoader {
    public:
        // Static function you can call from anywhere
        static TilemapData loadTilemapFromTMX(const std::string& path);
        static TilesetData loadTilesetFromTSX(const std::string& path);
        static std::string resolveRelativePath(const std::string& basePath, const std::string& relativePath);

    private:
        TilemapLoader() = default; // prevent instantiation
    };

}
