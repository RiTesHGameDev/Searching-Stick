#include "Gameplay/GameplayService.h"
#include "Gameplay/GameplayController.h"

namespace Gameplay
{
	GameplayService::GameplayService()
	{
		gameplay_controller = new GameplayController();
		stick_collection_controller = new StickCollectionController();
	}

	GameplayService::~GameplayService()
	{
		delete gameplay_controller;
		delete stick_collection_controller;
	}

	void GameplayService::initialize()
	{
		initializeRandomSeeds();
		gameplay_controller->initialize();
		stick_collection_controller->initialize();
	}

	void GameplayService::update()
	{
		gameplay_controller->update();
		stick_collection_controller->update();
	}

	void GameplayService::render()
	{
		gameplay_controller->render();
		stick_collection_controller->render();
	}

	void GameplayService::reset()
	{
		gameplay_controller->reset();
		stick_collection_controller->reset();
	}

	void GameplayService::initializeRandomSeeds()
	{
		srand(static_cast<unsigned int>(time(nullptr)));
	}
}