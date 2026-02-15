#include "UI/GameplayUI/GameplayUIController.h"
#include "Global/ServiceLocator.h"
#include "Main/GameService.h"
#include "Sound/SoundService.h"
#include "Global/Config.h"

namespace UI
{
	namespace GameplayUI
	{
		using namespace Interface;
		using namespace UIElement;
		using namespace Gameplay;
		using namespace Global;
		using namespace Main;
		using namespace Sound;
		GameplayUIController::GameplayUIController()
		{
			createButtons();
			createTexts();
		}

		GameplayUIController::~GameplayUIController()
		{
			destroy();
		}

		void GameplayUIController::initialize()
		{
			initializeTexts();
			initializeButtons();
		}

		void GameplayUIController::update()
		{
			updateTexts();
			menu_button->update();
		}

		void GameplayUIController::render()
		{
			seach_type->render();
			number_of_comparisons->render();
			number_of_array_access->render();
			num_sticks->render();
			delay->render();
			time_complexity->render();
			menu_button->render();
		}

		void GameplayUIController::show()
		{
			seach_type->show();
			number_of_comparisons->show();
			number_of_array_access->show();
			num_sticks->show();
			delay->show();
			time_complexity->show();
			menu_button->show();
		}

		void GameplayUIController::createTexts()
		{
			seach_type = new TextView();
			number_of_comparisons = new TextView();
			number_of_array_access = new TextView();
			num_sticks = new TextView();
			delay = new TextView();
			time_complexity = new TextView();
		}

		void GameplayUIController::createButtons()
		{
			menu_button = new ButtonView();
		}

		void GameplayUIController::initializeTexts()
		{
			seach_type->initialize("Search Type: Linear", sf::Vector2f(search_type_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size);
			number_of_comparisons->initialize("Comparisons: 0", sf::Vector2f(comparisons_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size);
			number_of_array_access->initialize("Array Access: 0", sf::Vector2f(array_access_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size);
			num_sticks->initialize("Num Sticks: 0", sf::Vector2f(num_sticks_x_position, text_y_pos2), FontType::BUBBLE_BOBBLE, font_size);
			delay->initialize("Delay: 0 ms", sf::Vector2f(delay_x_position, text_y_pos2), FontType::BUBBLE_BOBBLE, font_size);
			time_complexity->initialize("Time Complexity: 0(n)", sf::Vector2f(time_complexity_x_position, text_y_pos2), FontType::BUBBLE_BOBBLE, font_size);
		}

		void GameplayUIController::initializeButtons()
		{
			menu_button->initialize("Menu",Config::menu_button_texture_path, button_width, button_height, sf::Vector2f(button_x_position, button_y_position));
			registerButtonCallbacks();
		}

		void GameplayUIController::updateTexts()
		{
			updateSearchTypeText();
			updateNumberOfComparisonsText();
			updateNumberOfArrayAccessText();
			updateNumSticksText();
			updateDelayText();
			updateTimeComplexityText();
		}

		void GameplayUIController::updateSearchTypeText()
		{
			Gameplay::StickCollection::SearchType current_search_type = ServiceLocator::getInstance()->getGameplayService()->getCurrentSearchType();

			switch (current_search_type)
			{
			case Gameplay::StickCollection::SearchType::LINEAR:
				seach_type->setText("Search Type: Linear");
				break;

			case Gameplay::StickCollection::SearchType::BINARY:
				seach_type->setText("Search Type: Binary");
				break;
			default:
				break;
			}
		}

		void GameplayUIController::updateNumberOfComparisonsText()
		{
			std::string comparisons_str = "Comparisons: " + std::to_string(ServiceLocator::getInstance()->getGameplayService()->getNumberOfComparisons());
			number_of_comparisons->setText(comparisons_str);
			number_of_comparisons->update();
		}

		void GameplayUIController::updateNumberOfArrayAccessText()
		{
			std::string array_access_str = "Array Access: " + std::to_string(ServiceLocator::getInstance()->getGameplayService()->getNumberOfArrayAccess());
			number_of_array_access->setText(array_access_str);
			number_of_array_access->update();
		}

		void GameplayUIController::updateNumSticksText()
		{
			std::string num_sticks_str = "Num Sticks: " + std::to_string(ServiceLocator::getInstance()->getGameplayService()->getNumberOfSticks());
			num_sticks->setText(num_sticks_str);
			num_sticks->update();
		}

		void GameplayUIController::updateDelayText()
		{
			std::string delay_str = "Delay: " + std::to_string(ServiceLocator::getInstance()->getGameplayService()->getDelayMilliseconds()) + " ms";
			delay->setText(delay_str);
			delay->update();
		}

		void GameplayUIController::updateTimeComplexityText()
		{
			std::string time_complexity_str = "Time Complexity: " + ServiceLocator::getInstance()->getGameplayService()->getTimeComplexity();
			time_complexity->setText(time_complexity_str);
			time_complexity->update();
		}


		void GameplayUIController::menuButtonCallback()
		{
			ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
			ServiceLocator::getInstance()->getGameplayService()->reset();
			GameService::setGameState(GameState::MAIN_MENU);
		}

		void GameplayUIController::registerButtonCallbacks()
		{
			menu_button->registerCallbackFuntion(std::bind(&GameplayUIController::menuButtonCallback, this));
		}

		void GameplayUIController::destroy()
		{
			delete seach_type;
			delete number_of_comparisons;
			delete number_of_array_access;
			delete num_sticks;
			delete delay;
			delete time_complexity;
			delete menu_button;
		}
	}

}
