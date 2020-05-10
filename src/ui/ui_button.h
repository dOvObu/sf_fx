#ifndef INCLUDED_UI_BUTTON_H
#define INCLUDED_UI_BUTTON_H
#include "i_ui_item.h"
#include "../toglable.h"
#include <vector>
#include <SFML/Graphics/Text.hpp>

namespace qw
{
	struct UiButton : public qw::IUiItem
	{
		UiButton(char const* font, unsigned char_size = 30, sf::String text = "Button", sf::Color textColor = sf::Color::White, sf::Vector2f position = { 0.f,0.f }, sf::Vector2f size = { 100.f,100.f }, sf::Color backgound_color = sf::Color::White, bool draw_as_spawned = false);
		~UiButton();

		IUiItem* SetPosition(sf::Vector2f const& position);
		sf::Vector2f GetPosition();

		virtual IUiItem* SetSize(sf::Vector2f const& size) override;
		virtual sf::Vector2f GetSize() override;

		IUiItem* SetRotation(float angle) override;
		float GetRotation() override;

		std::vector<IUiItem*>* GetChilds() override;
		IUiItem* AddChild(IUiItem* new_ui_item) override;

		void Draw() override;

		UiButton* AddCallback(std::function<void(void)> cb);
	private:
		sf::Vector2f _position;
		float _angle{ 0.f };
		sf::Color _bkgColor;
		Toglable* _toglable{ nullptr };
		sf::Text _text;
		sf::String _str;
	};
}

#endif // !INCLUDED_UI_BUTTON_H
