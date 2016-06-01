#include "App.h"


App::App()
{
}


App::~App()
{
}
void App::onInit(){
}
void App::addScreen(){
	_gamescreen = std::make_unique<GamePlayScreen>();
	_screenList->addScreen(_gamescreen->get());
	_screenList->setScreen(_gamescreen->getScreenIndex());

}
void App::onExit(){

}
