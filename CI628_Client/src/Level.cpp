#include "Level.h"
#include "MyGame.h"
#include "TextureManager.h"
#include<string>




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
	int mapTileSize = 30;

	for (int row = 0; row < NUM_ROWS; row++)
	{
		for (int col = 0; col < NUM_COLS; col++)
		{
			mapTileType = map[row][col];
			dest.x = col * mapTileSize;
			dest.y = row * mapTileSize;
			dest.w = mapTileSize;
			dest.h = mapTileSize;

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
			default:
				break;
			}
		}
	}
}