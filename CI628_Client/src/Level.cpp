#include "Level.h"
#include "MyGame.h"
#include "TextureManager.h"
#include<string>
#include <cmath>




Level::Level(SDL_Renderer* renderer)
{
	

    createLevelFromString(levelText);
}

void Level::createLevelFromString(std::string level)
{
    int myArray[NUM_ROWS][NUM_COLS];

    int index = 0;
    for (int row = 0; row < NUM_ROWS; ++row) {
        for (int col = 0; col < NUM_COLS; ++col) {
            map[row][col] = level[index] - '0'; // Convert character to integer
            index++;
        }
    }

}

void Level::drawMap(SDL_Renderer* renderer)
{
	int mapTileType = 0;

	for (int row = 0; row < NUM_ROWS; row++)
	{
		for (int col = 0; col < NUM_COLS; col++)
		{
			mapTileType = map[row][col];
			dest.x = col * MAP_TILE_SIZE;
			dest.y = row * MAP_TILE_SIZE;
			dest.w = MAP_TILE_SIZE;
			dest.h = MAP_TILE_SIZE;

			switch (mapTileType)
			{
			case 0:
				break;
			case 1:
				/*TextureManager::Draw(wall, src, dest);*/
				TextureManager::Draw(renderer, wall, dest);
				break;
			case 2:
				TextureManager::Draw(renderer, brick, dest);
				break;
			case 3:
				TextureManager::Draw(renderer, bomb, dest);
				break;
			default:
				break;
			}
		}
	}
}

void Level::updateMap(int sentX, int sentY, int newTileType)
{
	for (int row = 0; row < NUM_ROWS; row++)
	{
		for (int col = 0; col < NUM_COLS; col++)
		{
			// If updating existing tiles
			if (sentX == col * MAP_TILE_SIZE && sentY == row * MAP_TILE_SIZE) map[row][col] = newTileType;

			// If creating a new tile
			else
			{
				map[sentY / MAP_TILE_SIZE][sentX / MAP_TILE_SIZE] = newTileType;
			}
			
		}
	}
}



void Level::bombExplosion(int bombX, int bombY, int bombRadius)
{
	int bombPosX = bombX / MAP_TILE_SIZE;
	int bombPosY = bombY / MAP_TILE_SIZE;

	// Clear out bomb texture
	map[bombPosY][bombPosX] = 0;

	for (int explosionCircle = 0; explosionCircle < bombRadius; explosionCircle++)
	{
		for (int row = 0; row < NUM_ROWS; row++)
		{
			for (int col = 0; col < NUM_COLS; col++)
			{
				

			}
		}
	}

}
