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

		std::vector<IUiItem*>* GetChilds() override;
		IUiItem* AddChild(IUiItem* new_ui_item) override;

		UiLabel* Scroll(int step); // step > 0 --> scrolling down, 0 > step --> scrolling up

		void Draw() override;
	private:
		::sf::Text _text;

		sf::String _str;
		float _charWidth{ 0.f };
		float _charHeight{ 0.f };
		size_t _width{ 0 };
		size_t _height{ 0 };
		bool _scrollable{ true };
		size_t _scrollPos{ 0 };

		void _SetSize(size_t width, size_t height);
		void _RecalculateCharSize();
	};
}

#endif // !INCLUDED_UI_LABEL_H
