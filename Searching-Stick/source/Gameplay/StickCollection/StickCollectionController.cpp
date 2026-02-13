#include "Gameplay/StickCollection/StickCollectionController.h"
#include "Gameplay/StickCollection/StickCollectionModel.h"
#include "Gameplay/StickCollection/StickCollectionView.h"
#include "Gameplay/StickCollection/Stick.h"
#include "Gameplay/GameplayService.h"
#include "Global/ServiceLocator.h"
#include "Sound/SoundService.h"
#include <iostream>
#include <random>

using namespace std;

namespace Gameplay
{
	using namespace Global;
	using namespace UI::UIElement;
	using namespace Graphics;

	namespace StickCollection
	{
		StickCollectionController::StickCollectionController()
		{
			stick_collection_view = new StickCollectionView();
			stick_collection_model = new StickCollectionModel();
			initializeSticksArray();
		}

		StickCollectionController::~StickCollectionController()
		{
			destroy();
		}

		void StickCollectionController::initialize()
		{
			stick_collection_model->initialize();
			initializeSticks();
			reset();;
		}

		void StickCollectionController::update()
		{
			processSearchThreadState();

			stick_collection_view->update();

			for (int i = 0; i < sticks.size(); i++)
				sticks[i]->stick_view->update();
		}

		void StickCollectionController::render()
		{
			stick_collection_view->render();

			for (int i = 0; i < sticks.size(); i++)
				sticks[i]->stick_view->render();

		}

		void StickCollectionController::reset()
		{
			current_operation_delay = 0;

			if(search_thread.joinable())search_thread.join();

			shuffleSticks();
			updateSticksPosition();
			resetSticksColor();
			resetSearchStick();
			resetVariables();
		}

		void StickCollectionController::searchElement(StickCollection::SearchType search_type)
		{
			this->search_type = search_type;
			switch (search_type)
			{
			case SearchType::LINEAR:
				current_operation_delay = stick_collection_model->linear_search_delay;
				search_thread = std::thread(&StickCollectionController::processLinearSearch, this);
				break;

			case SearchType::BINARY:
				//processBinarySearch();
				break;

			default:
				printf("Invalid search type");
				return;
			}
		}

		void StickCollectionController::resetSearchStick()
		{
			stick_to_search = sticks[rand() % sticks.size()];
			stick_to_search->stick_view->setFillColor(stick_collection_model->search_element_color);
		}

		void StickCollectionController::resetVariables()
		{
			number_of_array_access = 0;
			number_of_comparisons = 0;
		}

		void StickCollectionController::resetSticksColor()
		{
			for (int i = 0; i < sticks.size(); i++)
			{
				sticks[i]->stick_view->setFillColor(stick_collection_model->element_color);
			}
		}

		void StickCollectionController::processLinearSearch()
		{
			Sound::SoundService* sound_service = Global::ServiceLocator::getInstance()->getSoundService();

			for(int i = 0; i < sticks.size(); i++)
			{
				number_of_array_access += 1;
				number_of_comparisons++;

				sound_service->playSound(Sound::SoundType::COMPARE_SFX);

				if(sticks[i] == stick_to_search)
				{
					sticks[i]->stick_view->setFillColor(stick_collection_model->found_element_color);
					stick_to_search = nullptr;
					return;
				}
				else
				{
					// Set the color of the currently processing stick to visualize the search process
					sticks[i]->stick_view->setFillColor(stick_collection_model->processing_element_color);

					// Sleep for the specified delay to visualize the search process
					std::this_thread::sleep_for(std::chrono::milliseconds(current_operation_delay));

					// Reset the color of the stick back to default after processing
					sticks[i]->stick_view->setFillColor(stick_collection_model->element_color);
				}
			}

		}

		void StickCollectionController::shuffleSticks()
		{
			std::random_device device;
			std::mt19937 random_engine(device());

			std::shuffle(sticks.begin(), sticks.end(), random_engine);
		}

		void StickCollectionController::joinThreads()
		{
			search_thread.join();
		}

		void StickCollectionController::processSearchThreadState()
		{
			if (search_thread.joinable() && stick_to_search == nullptr)
			{
				joinThreads();
			}
		}
		
		void StickCollectionController::initializeSticks()
		{
			float rectangle_width = calculateStickWidth();

			for (int i = 0; i < stick_collection_model->number_of_elements; i++)
			{
				float rectangle_height = calculateStickHeight(i);
				sf::Vector2f rectangle_size = sf::Vector2f(rectangle_width, rectangle_height);
				sticks[i]->stick_view->initialize(rectangle_size, sf::Vector2f(0, 0), 0, stick_collection_model->element_color);
			}
		}

		void StickCollectionController::initializeSticksArray()
		{
			for (int i = 0; i < stick_collection_model->number_of_elements; i++)
			{
				sticks.push_back(new Stick(i));
			}
		}

		float StickCollectionController::calculateStickWidth()
		{
			float total_space = static_cast<float>(ServiceLocator::getInstance()->getGraphicService()->getGameWindow()->getSize().x);

			float toatal_spacing = stick_collection_model->space_percentage * total_space;

			float space_between = toatal_spacing / (stick_collection_model->number_of_elements - 1);

			stick_collection_model->setElementsSpacing(space_between);

			float remaining_space = total_space - toatal_spacing;

			float rectangle_width = remaining_space / stick_collection_model->number_of_elements; 
			
			return rectangle_width;
		}

		float StickCollectionController::calculateStickHeight(int array_pos)
		{
			return (static_cast<float>(array_pos + 1) / stick_collection_model->number_of_elements) * stick_collection_model->max_element_height;
		}

		void StickCollectionController::updateSticksPosition()
		{
			for (int i = 0; i < sticks.size(); i++)
			{
				float x_position = i * (sticks[i]->stick_view->getSize().x + ( stick_collection_model->elements_spacing));
				float y_position = stick_collection_model->element_y_position - sticks[i]->stick_view->getSize().y;
				sticks[i]->stick_view->setPosition(sf::Vector2f(x_position, y_position));
			}
		}

		void StickCollectionController::destroy()
		{
			if (search_thread.joinable())
				search_thread.join();

			for (int i = 0; i < sticks.size(); i++) delete(sticks[i]);
			sticks.clear();

			delete (stick_collection_view);
			delete (stick_collection_model);
		}

		SearchType StickCollectionController::getSearchType()
		{
			return search_type;
		}

		int StickCollectionController::getNumberOfSticks()
		{
			return stick_collection_model->number_of_elements;
		}

		int StickCollectionController::getNumberOfArrayAccess()
		{
			return number_of_array_access;
		}

		int StickCollectionController::getNumberOfComparisons()
		{
			return number_of_comparisons;
		}

		int StickCollectionController::getDelayMilliseconds()
		{
			return current_operation_delay;
		}

	}
}