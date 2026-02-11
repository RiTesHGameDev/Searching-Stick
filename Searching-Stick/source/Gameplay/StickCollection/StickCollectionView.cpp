#include "Gameplay/StickCollection/StickCollectionView.h"

namespace Gameplay
{
	namespace StickCollection
	{
		StickCollectionView::StickCollectionView()
		{
			model = new StickCollectionModel();
		}
		StickCollectionView::~StickCollectionView()
		{
			delete model;
		}
		void StickCollectionView::initialize(StickCollectionController* controller)
		{
			this->controller = controller;
		}
		void StickCollectionView::update()
		{
			model->update();
		}
		void StickCollectionView::render()
		{
		}
		
	}
}