#include "GamePlayScreen.h"
#include <NeroEngine/ScreenList.h>
#include <iostream>
GamePlayScreen::GamePlayScreen()
{
}


GamePlayScreen::~GamePlayScreen()
{
}

int GamePlayScreen::getNextScreenIndex() const
{
	return SCREEN_INEDX_NO_SCREEN;
}

int GamePlayScreen::getPreviousScreenIndex() const
{
	return SCREEN_INEDX_NO_SCREEN;
}

void GamePlayScreen::build()
{
	std::cout << "build" << std::endl;
}

void GamePlayScreen::destroy()
{
	std::cout << "ondestroy" << std::endl;
}

void GamePlayScreen::onEntry()
{
	std::cout << "onentry" << std::endl;
}

void GamePlayScreen::onExit()
{
	std::cout << "onexit" << std::endl;
}

void GamePlayScreen::update()
{
	std::cout << "update" << std::endl;
}

void GamePlayScreen::draw()
{
	std::cout << "draw" << std::endl;
}
