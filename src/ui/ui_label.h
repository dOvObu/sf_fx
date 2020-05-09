#ifndef INCLUDED_UI_LABEL_H
#define INCLUDED_UI_LABEL_H
#include "i_ui_item.h"
#include <SFML/Graphics/Text.hpp>

namespace qw
{
	struct UiLabel : public IUiItem
	{
		UiLabel(::sf::String text, char const* font);
		~UiLabel() override = default;

		void SetPosition(::sf::Vector2f const& position) override;
		::sf::Vector2f GetPosition() override;

		void SetRotation(float angle) override;
		float GetRotation() override;

		std::vector<IUiItem*>& GetChilds() override;
		void AddChild(IUiItem* new_ui_item) override;

		void Draw() override;
	private:
		::sf::Text _text;
	};
}

#endif // !INCLUDED_UI_LABEL_H
