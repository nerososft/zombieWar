#pragma once
#include <string>
#include <vector>
#include <NeroEngine\SpriteBatch.h>

const float TILE_WIDTH = 32;		

class Level
{
public:
	Level(const std::string& fileName);
	~Level();
	void draw();
	int getNumHuman() const { return _numHumans; }
	int getWidth() const { return _levelData[0].size(); }
	int getHeight() const { return _levelData.size(); }

	const std::vector<std::string>& getLevelData() const{ return _levelData; }

	glm::vec2 getPlayerPos() const{ return _startPlayerPos; }
	const std::vector<glm::ivec2>& getZombiesPositions(){ return _zombiesStartPositions; }
private:
	std::vector<std::string> _levelData;

	int _numHumans;
	NeroEngine::SpriteBatch _spriteBatch;
	
	glm::ivec2 _startPlayerPos;
	std::vector<glm::ivec2> _zombiesStartPositions;
};


