#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>

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

			Stick* stick_to_search;

			std::thread search_thread;

			sf::String time_complexity;

			int number_of_array_access;
			int number_of_comparisons;

			int current_operation_delay;

			void initializeSticks();
			void initializeSticksArray();

			float calculateStickWidth();
			float calculateStickHeight(int array_pos);

			void updateSticksPosition();

			void resetSticksColor();
			void resetSearchStick();
			void resetVariables();

			void processLinearSearch();
			void shuffleSticks();

			void joinThreads();
			void processSearchThreadState();

			void destroy();

		public:
			StickCollectionController();
			~StickCollectionController();
			void initialize();
			void update();
			void render();
			void reset();

			void searchElement(StickCollection::SearchType search_type);

			SearchType getSearchType();
			int getNumberOfSticks();

			int getNumberOfArrayAccess();
			int getNumberOfComparisons();

			int getDelayMilliseconds();

			sf::String getTimeComplexity();

		};
	}
}