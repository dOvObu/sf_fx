#ifndef INCLUDED_UI_LABEL_H
#define INCLUDED_UI_LABEL_H
#include "i_ui_item.h"
#include <SFML/Graphics/Text.hpp>

namespace qw
{
	struct UiLabel : public IUiItem
	{
		UiLabel(::sf::String text, char const* font, unsigned char_size = 30);
		~UiLabel() override = default;

		IUiItem* SetPosition(::sf::Vector2f const& position) override;
		::sf::Vector2f GetPosition() override;

		IUiItem* SetSize(::sf::Vector2f const& position) override;
		::sf::Vector2f GetSize() override;

		IUiItem* SetRotation(float angle) override;
		float GetRotation() override;

		std::vector<IUiItem*>& GetChilds() override;
		IUiItem* AddChild(IUiItem* new_ui_item) override;

		void Draw() override;
	private:
		::sf::Text _text;

		sf::String _str;
	};
}

#endif // !INCLUDED_UI_LABEL_H
