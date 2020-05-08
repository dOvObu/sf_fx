#ifndef INCLUDED_I_UI_WIDGET_H
#define INCLUDED_I_UI_WIDGET_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

namespace qw
{
	struct IUiItem
	{
		virtual void Position(sf::Vector2f const& position) = 0;
		virtual sf::Vector2f Position() = 0;
		virtual std::vector<IUiItem*>& Childs() = 0;
		virtual void AddChild(IUiItem* new_ui_item) = 0;

		virtual void Draw() = 0;
		static void Init(sf::RenderWindow& rw);
	protected:
		static sf::RenderWindow* _pw;
	};
}

#endif // !INCLUDED_I_UI_WIDGET_H
