#include "Level.h"

#include <NeroEngine\Errors.h>
#include <fstream>
#include <iostream>
#include <NeroEngine\ResourceManager.h>
#include <sstream>

Level::Level(const std::string& fileName)
{

	std::ifstream file;
	file.open(fileName);

	if (file.fail()){
		NeroEngine::fatalError("地图数据读取失败" + fileName);
	}
	else{
		std::cout << "地图数据读取成功:" + fileName << std::endl;
	}
	std::string tmp;
	

	file >> tmp;// >> _numHumans;
	_numHumans = atoi(tmp.substr(6).c_str());

	//std::cout << _numHumans;
	std::getline(file, tmp);
	while (std::getline(file, tmp)){
		_levelData.push_back(tmp);
	}

	_spriteBatch.init();
	_spriteBatch.begin();
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	NeroEngine::Color whiteColor;
	whiteColor.a = 255;
	whiteColor.r = 50;
	whiteColor.g = 50;
	whiteColor.b = 50;
	for (int y = 0; y < _levelData.size();y++){
		for (int x = 0; x < _levelData[y].size();x++){
			char tile = _levelData[y][x];

			glm::vec4 destRect(x*TILE_WIDTH, y*TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			switch (tile)
			{
			case 'R':
				_spriteBatch.draw(destRect,
								  uvRect,
								  NeroEngine::ResourceManager::getTexture("Textures/qiang.png").id,
								  0.0f,
								  whiteColor);
				break;
			case 'G':
				_spriteBatch.draw(destRect,
					uvRect,
					NeroEngine::ResourceManager::getTexture("Textures/grass.png").id,
					0.0f,
					whiteColor);
				break;
			case 'L':
				_spriteBatch.draw(destRect,
					uvRect,
					NeroEngine::ResourceManager::getTexture("Textures/qiang2.png").id,
					0.0f,
					whiteColor);
				break;
			case 'Q':
				_spriteBatch.draw(destRect,
					uvRect,
					NeroEngine::ResourceManager::getTexture("Textures/qiang1.png").id,
					0.0f,
					whiteColor);
				break;
			case '@':
				_spriteBatch.draw(destRect,
					uvRect,
					NeroEngine::ResourceManager::getTexture("Textures/ground.png").id,
					0.0f,
					whiteColor);
				_levelData[y][x] = '.';
				_startPlayerPos.x = x*TILE_WIDTH;
				_startPlayerPos.y = y*TILE_WIDTH;
				break;
			case 'Z':
				_spriteBatch.draw(destRect,
					uvRect,
					NeroEngine::ResourceManager::getTexture("Textures/ground.png").id,
					0.0f,
					whiteColor);
				_levelData[y][x] = '.';
				_zombiesStartPositions.emplace_back(x*TILE_WIDTH, y*TILE_WIDTH);
				break;
			case '.':
				_spriteBatch.draw(destRect,
					uvRect,
					NeroEngine::ResourceManager::getTexture("Textures/ground.png").id,
					0.0f,
					whiteColor);
				break;
			default:
				break;
			}
		}
	}

	_spriteBatch.end();


}
void Level::draw(){
	_spriteBatch.renderBatch();
}

Level::~Level()
{
}