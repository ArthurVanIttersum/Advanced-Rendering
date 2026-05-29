#include "TilemapLoader.h"
#include <sstream>
#include <stdexcept>

namespace core {

    TilemapData TilemapLoader::loadTilemapFromTMX(const std::string& path)
    {
        tinyxml2::XMLDocument doc;
        if (doc.LoadFile(path.c_str()) != tinyxml2::XML_SUCCESS) throw std::runtime_error("Failed to load TMX file: " + path);
        
        auto* map = doc.FirstChildElement("map");
        if (!map) throw std::runtime_error("TMX missing <map> element");
        
        TilemapData result;
        result.width = map->IntAttribute("width");
        result.height = map->IntAttribute("height");

        auto* layer = map->FirstChildElement("layer");
        if (!layer) throw std::runtime_error("TMX missing <layer> element");

        auto* data = layer->FirstChildElement("data");
        if (!data) throw std::runtime_error("TMX missing <data> element");
        
        const char* encoding = data->Attribute("encoding");
        if (!encoding || std::string(encoding) != "csv") throw std::runtime_error("Only CSV-encoded TMX files are supported");
        
        const char* csv = data->GetText();
        if (!csv) throw std::runtime_error("TMX <data> element has no text");
        
        std::stringstream ss(csv);
        std::string item;

        result.tiles.reserve(result.width * result.height);

        while (std::getline(ss, item, ',')) {
            if (!item.empty()) {
                unsigned short gid = static_cast<unsigned short>(std::stoi(item));
                result.tiles.push_back(gid);
            }
        }

        return result;
    }

    TilesetData TilemapLoader::loadTilesetFromTSX(const std::string& path)
    {
        tinyxml2::XMLDocument doc;
        if (doc.LoadFile(path.c_str()) != tinyxml2::XML_SUCCESS) throw std::runtime_error("Failed to load TSX file: " + path);
        
        auto* tileset = doc.FirstChildElement("tileset");
        if (!tileset) throw std::runtime_error("TSX missing <tileset> element");
        
        TilesetData result;

        // Tile size in pixels
        result.tileWidth = tileset->IntAttribute("tilewidth");
        result.tileHeight = tileset->IntAttribute("tileheight");

        int tileCount = tileset->IntAttribute("tilecount");
        int columns = tileset->IntAttribute("columns");

        if (tileCount <= 0 || columns <= 0) throw std::runtime_error("Invalid tilecount/columns in TSX");
        
        result.tilesPerRow = columns;
        result.tilesPerCol = tileCount / columns;

        auto* image = tileset->FirstChildElement("image");
        const char* source = image->Attribute("source");

        
        result.imagePath = resolveRelativePath(path, source);
        
        return result;
    }

    std::string TilemapLoader::resolveRelativePath(const std::string& basePath,
        const std::string& relativePath)
    {
        size_t lastSlash = basePath.find_last_of("/\\");
        std::string directory = (lastSlash == std::string::npos)
            ? ""
            : basePath.substr(0, lastSlash + 1);

        return directory + relativePath;
    }


}
