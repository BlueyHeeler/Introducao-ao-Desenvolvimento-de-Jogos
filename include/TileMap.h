#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "Component.h"
#include "TileSet.h"
#include <memory>
#include <string>
#include <vector>

class TileMap : public Component 
{
public:

    TileMap(GameObject& associated, std::string file, TileSet* tileSet);
    void Load(std::string file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z = 0);
    void Update(float dt) override;
    void Render() override;
    void RenderLayer(int layer);
    int GetWidth();
    int GetHeight();
    int GetDepth();

private:
    std::vector<int> tileMatrix;
    std::unique_ptr<TileSet> tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;
};
#endif
