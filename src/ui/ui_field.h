#ifndef INCLUDED_UI_FIELD_H
#define INCLUDED_UI_FIELD_H
#include "i_ui_item.h"
#include "../toglable.h"
#include <vector>

namespace qw
{
	struct UiField : public IUiItem
	{
		UiField(sf::Vector2f position, sf::Vector2f size, sf::Color backgound_color);
		void SetPosition(sf::Vector2f const& position);
		sf::Vector2f GetPosition();
		std::vector<IUiItem*>& Childs() override;
		void AddChild(IUiItem* new_ui_item) override;
	private:
		sf::Vector2f _position;
		sf::Color _bkgColor;
		Toglable* _toglable{ nullptr };
		IUiItem* _parent{ nullptr };
		std::vector<IUiItem*> _childs;
	};
}

#endif // !INCLUDED_UI_FIELD_H
