#pragma once
#include "SFML/Graphics.hpp"
#include "UI/UIElement/ImageView.h"

namespace Gameplay
{
	using namespace UI::UIElement;
    class GameplayController;

    class GameplayView
    {
    private:
		ImageView* background_image;

		const float background_alpha = 55.0f;

		GameplayController* gameplay_controller;
		sf::Font font;

		void initializeBackgroundImage();
    public:
        GameplayView();
        ~GameplayView();

        void initialize(GameplayController* gameplay_controller);
        void update();
        void render();
    };
}
