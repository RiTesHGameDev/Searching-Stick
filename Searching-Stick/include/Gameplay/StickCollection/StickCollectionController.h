#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace Gameplay
{
	namespace StickCollection
	{
		class StickCollectionModel;
		class StickCollectionView;
		enum class SearchType;
		struct Stick;

		class StickCollectionController
		{
		private:
			StickCollectionView* stick_collection_view;
			StickCollectionModel* stick_collection_model;

			std::vector<Stick*> sticks;
			StickCollection::SearchType search_type;

			void initializeSticks();
			float calculateStickWidth();

			void updateSticksPosition();
			void resetSticksColor();
			void initializeSticksArray();
			float calculateStickHeight(int array_pos);
			void destroy();
		public:
			StickCollectionController();
			~StickCollectionController();
			void initialize();
			void update();
			void render();
			void reset();

			SearchType getSearchType();
			int getNumberOfSticks();
		};
	}
}