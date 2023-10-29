#pragma once

class Level
{
public:
	Level();

	constexpr int NUM_ROWS = 19;
	constexpr int NUM_COLS = 25;
	int map[NUM_ROWS][NUM_COLS];

	void loadMap();
	void drawMap();
};