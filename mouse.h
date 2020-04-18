#ifndef INCLUDED_MOUSE_H
#define INCLUDED_MOUSE_H
#include <SFML/Graphics.hpp>
#include "event.h"

namespace qw
{
	struct Mouse
	{
		static Event OnMousePressed;
		static Event OnMouseReleased;
		static Event OnMouseDown;

		static sf::Vector2f const& GetMousePosition()
		{
			return sf::Vector2f(sf::Mouse::getPosition(*pw));
		}
		static void Init(sf::RenderWindow& rw) { pw = &rw; }
	private:
		static sf::RenderWindow* pw;
	};
}

#endif // !INCLUDED_MOUSE_H
