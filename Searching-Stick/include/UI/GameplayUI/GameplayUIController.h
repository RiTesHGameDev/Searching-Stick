#pragma once
#include "UI/Interface/IUIController.h"
#include "UI/UIElement/TextView.h"
#include "UI/UIElement/ButtonView.h"
#include "UI/UIElement/ImageView.h"
#include "Gameplay/GameplayService.h"

namespace UI
{
	namespace GameplayUI
	{
		using namespace Interface;
		using namespace UIElement;
		using namespace Gameplay;
		class GameplayUIController : public IUIController
		{
		private:
			TextView* seach_type;
			TextView* number_of_comparisons;
			TextView* number_of_array_access;
			TextView* num_sticks;
			TextView* delay;
			TextView* time_complexity;

			ButtonView* menu_button;

			const float font_size = 40.0f;

			const float text_y_position = 20.0f;
			const float text_y_pos2 = 80.0f;

			const float search_type_x_position = 60.0f;
			const float comparisons_x_position = 680.0f;
			const float array_access_x_position = 1250.0f;
			const float num_sticks_x_position = 60.0f;
			const float delay_x_position = 680.0f;
			const float time_complexity_x_position = 1250.0f;

			const float button_width = 200.0f;
			const float button_height = 100.0f;

			const float button_x_position = 1670.0f;
			const float button_y_position = 33.0f;

			void createTexts();
			void createButtons();

			void initializeTexts();
			void initializeButtons();

			void updateTexts();
			void updateSearchTypeText();
			void updateNumberOfComparisonsText();
			void updateNumberOfArrayAccessText();
			void updateNumSticksText();
			void updateDelayText();
			void updateTimeComplexityText();

			void menuButtonCallback();
			void registerButtonCallbacks();

			void destroy();
		public:
			GameplayUIController();
			~GameplayUIController();
			void initialize() override;
			void update() override;
			void render() override;
			void show() override;
		};
	}
}