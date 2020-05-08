#ifndef INCLUDED_APP_H
#define INCLUDED_APP_H
#include <SFML/Graphics/RenderWindow.hpp>

namespace qw
{
	struct App
	{
		static void Init(sf::RenderWindow& w);
		static void MainLoop();

	private:
		static sf::RenderWindow* pw;
		static bool is_left_mouse_down;
		static bool is_middle_mouse_down;
		static bool is_right_mouse_down;

		static void HandleEvents();
		static void Handle_MouseButtonPressed(sf::Mouse::Button const& btn);
		static void Handle_MouseButtonReleased(sf::Mouse::Button const& btn);
		static void Handle_MouseButtonDown();
	};
}

#endif // !INCLUDED_APP_H
