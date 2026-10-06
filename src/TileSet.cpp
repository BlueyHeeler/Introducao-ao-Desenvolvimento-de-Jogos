#include "TileSet.h"
#include <stdexcept>

TileSet::TileSet(int tileWidth, int tileHeight, std::string file)
    : tileSet(file), tileWidth(tileWidth), tileHeight(tileHeight), tileCount(0) 
{
    if (tileWidth <= 0 || tileHeight <= 0)
        throw std::invalid_argument("Dimensoes do tile devem ser positivas.");
    if (!tileSet.IsOpen())
        throw std::runtime_error("Nao foi possivel abrir o tileset: " + file);

    // Aqui o Sprite ainda tem 1x1 frame: getters retornam a imagem inteira.
    const int width = tileSet.GetWidth();
    const int height = tileSet.GetHeight();
    if (width % tileWidth != 0 || height % tileHeight != 0)
        throw std::runtime_error("Tileset nao e divisivel pelo tamanho dos tiles.");
    const int columns = width / tileWidth;
    const int rows = height / tileHeight;
    tileCount = columns * rows;
    tileSet.SetFrameCount(columns, rows);
    tileSet.SetFrame(0);
}

void TileSet::RenderTile(unsigned index, float x, float y) 
{
    if (index >= static_cast<unsigned>(tileCount)) return;
    tileSet.SetFrame(static_cast<int>(index));
    tileSet.Render(static_cast<int>(x), static_cast<int>(y), tileWidth, tileHeight);
}

int TileSet::GetTileWidth() 
{ 
	return tileWidth; 
}

int TileSet::GetTileHeight() 
{ 
	return tileHeight; 
}
