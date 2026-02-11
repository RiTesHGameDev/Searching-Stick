#pragma once
#include "Gameplay/StickCollection/StickCollectionModel.h"

namespace Gameplay
{
	namespace StickCollection
	{
		class StickCollectionController;
		class StickCollectionView
		{
		private:
			StickCollectionModel* model;
			StickCollectionController* controller;
			void initializeBackgroundImage();
		public:
			StickCollectionView();
			~StickCollectionView();
			void initialize(StickCollectionController* controller);
			void update();
			void render();
		};
	}
}