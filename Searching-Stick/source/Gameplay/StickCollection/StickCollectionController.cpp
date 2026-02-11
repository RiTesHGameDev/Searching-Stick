#include "Gameplay/StickCollection/StickCollectionController.h"
#include "Gameplay/StickCollection/StickCollectionView.h"
#include

namespace Gameplay
{
	namespace StickCollection
	{
		StickCollectionController::StickCollectionController()
		{
			stick_collection_view = new StickCollectionView();
			stick_collection_model = new StickCollectionModel();
		}
		StickCollectionController::~StickCollectionController()
		{
			destroy();
		}
		void StickCollectionController::initialize()
		{
			initializeSticks();
			stick_collection_view->initialize(this);
			stick_collection_model->initialize();
		}
		void StickCollectionController::update()
		{
			updateSticksPosition();
			stick_collection_view->update();
			stick_collection_model->update();
		}
		void StickCollectionController::render()
		{
			stick_collection_view->render();
		}

		void StickCollectionController::reset()
		{
			resetSticksColor();
			initializeSticksArray();
			updateSticksPosition();
		}
		void StickCollectionController::destroy()
		{
		}
		float StickCollectionController::calculateStickWidth()
		{
		}
		void StickCollectionController::updateSticksPosition()
		{
		}
		void StickCollectionController::resetSticksColor()
		{
		}
		void StickCollectionController::initializeSticksArray()
		{
		}
		float StickCollectionController::calculateStickHeight(int array_pos)
		{
		}
		void StickCollectionController::initializeSticks()
		{

		}
		SearchType StickCollectionController::getSearchType()
		{
			return search_type;
		}
		int StickCollectionController::getNumberOfSticks()
		{
			return stick_collection_model->number_of_elements;
		}
	}
}