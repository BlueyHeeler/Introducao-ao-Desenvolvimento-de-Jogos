#include "TileMap.h"
#include "GameObject.h"
#include "Camera.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iterator>
#include <sstream>
#include <stdexcept>

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet)
    : Component(associated), tileSet(tileSet), mapWidth(0), mapHeight(0), mapDepth(0) 
{
    if (!tileSet) 
    	throw std::invalid_argument("TileMap precisa de um TileSet.");
    Load(file);
}

void TileMap::Load(std::string file) 
{
    std::ifstream input(file);
    if (!input) 
    	throw std::runtime_error("Nao foi possivel abrir o mapa: " + file);
    std::string text((std::istreambuf_iterator<char>(input)),
                     std::istreambuf_iterator<char>());
                     
    std::replace(text.begin(), text.end(), ',', ' ');
    std::istringstream values(text);
    int width, height, depth;
    if (!(values >> width >> height >> depth) || width <= 0 || height <= 0 || depth <= 0)
        throw std::runtime_error("Dimensoes invalidas no mapa: " + file);
    std::vector<int> matrix;
    const std::size_t w = static_cast<std::size_t>(width);
    const std::size_t h = static_cast<std::size_t>(height);
    const std::size_t d = static_cast<std::size_t>(depth);
    if (w > matrix.max_size() / h || w * h > matrix.max_size() / d)
        throw std::runtime_error("Mapa grande demais.");
    const std::size_t count = w * h * d;
    matrix.reserve(count);
    for (std::size_t i = 0; i < count; ++i) {
        int tile;
        if (!(values >> tile) || tile < -1)
            throw std::runtime_error("Mapa incompleto ou tile invalido: " + file);
        matrix.push_back(tile);
    }
    values >> std::ws;
    if (!values.eof()) throw std::runtime_error("Dados extras no mapa: " + file);
    tileMatrix.swap(matrix);
    mapWidth = width;
    mapHeight = height;
    mapDepth = depth;
    parallax.assign(mapDepth, 1.0f);
    associated.box.w = static_cast<float>(mapWidth) * tileSet->GetTileWidth();
    associated.box.h = static_cast<float>(mapHeight) * tileSet->GetTileHeight();
}

void TileMap::SetTileSet(TileSet* newTileSet) {
    if (!newTileSet) 
    	throw std::invalid_argument("TileSet nao pode ser nulo.");
    if (newTileSet != tileSet.get()) 
    	tileSet.reset(newTileSet);
    associated.box.w = static_cast<float>(mapWidth) * tileSet->GetTileWidth();
    associated.box.h = static_cast<float>(mapHeight) * tileSet->GetTileHeight();
}

int& TileMap::At(int x, int y, int z) {
    if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight || z < 0 || z >= mapDepth)
        throw std::out_of_range("Coordenada fora do TileMap.");
    const std::size_t index = (static_cast<std::size_t>(z) * mapHeight + y) * mapWidth + x;
    return tileMatrix.at(index);
}

void TileMap::Update(float) {}

void TileMap::Render() 
{
    for (int layer = 0; layer < mapDepth; ++layer) RenderLayer(layer);
}

bool TileMap::Is(std::string type)
{
    return type == "TileMap";
}

void TileMap::RenderLayer(int layer) 
{
    if (layer < 0 || layer >= mapDepth) 
    	return;
    // Sprite::Render subtrai Camera::pos uma vez. Esta compensacao deixa
    // o deslocamento final igual a -Camera::pos * fator da camada.
    const float offsetX = Camera::pos.x * (1.0f - parallax[layer]);
    const float offsetY = Camera::pos.y * (1.0f - parallax[layer]);
    for (int y = 0; y < mapHeight; ++y) 
    {
        for (int x = 0; x < mapWidth; ++x) 
        {
            const int tile = At(x, y, layer);
            if (tile == -1) continue;
            tileSet->RenderTile(static_cast<unsigned>(tile),
                associated.box.x + static_cast<float>(x) * tileSet->GetTileWidth() + offsetX,
                associated.box.y + static_cast<float>(y) * tileSet->GetTileHeight() + offsetY);
        }
    }
}

void TileMap::SetParallax(int layer, float factor)
{
    if (layer < 0 || layer >= mapDepth)
        throw std::out_of_range("Camada fora do TileMap.");
    if (!std::isfinite(factor) || factor < 0.0f)
        throw std::invalid_argument("Fator de parallax deve ser finito e nao negativo.");
    parallax[layer] = factor;
}

int TileMap::GetWidth() 
{ 
	return mapWidth; 
}

int TileMap::GetHeight() 
{ 
	return mapHeight; 
}

int TileMap::GetDepth() 
{ 
	return mapDepth; 
}


