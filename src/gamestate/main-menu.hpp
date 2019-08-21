#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP
#include "menu.hpp"
class MainMenu : public GameState {
	public:
		void update(sf::Time frameTime, sf::RenderWindow& window);
		void draw(sf::RenderWindow& window);
		void init();
		void clear();
		static void ButtonCallback(MainMenu* mm);
		
		sf::View getView();
		MainMenu(Game* game);
		~MainMenu();

	private:
		Menu menu;
		std::string titleText;
		sf::Clock sineWaveTimer;
};
#endif
