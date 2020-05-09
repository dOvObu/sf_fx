#ifndef INCLUDED_UI_FIELD_H
#define INCLUDED_UI_FIELD_H
#include "i_ui_item.h"
#include "../toglable.h"
#include <vector>

namespace qw
{
	struct UiField : public IUiItem
	{
		UiField(sf::Vector2f position = {0.f,0.f}, sf::Vector2f size = { 100.f,100.f }, sf::Color backgound_color = sf::Color::White, std::vector<IUiItem*> const& childs = {}, bool draw_as_spawned = false);
		~UiField();

		void SetPosition(sf::Vector2f const& position);
		sf::Vector2f GetPosition();

		void SetRotation(float angle) override;
		float GetRotation() override;

		std::vector<IUiItem*>& GetChilds() override;
		void AddChild(IUiItem* new_ui_item) override;

		void Draw() override;
	private:
		sf::Vector2f _position;
		float _angle{ 0.f };
		sf::Color _bkgColor;
		Toglable* _toglable{ nullptr };
		std::vector<IUiItem*> _childs;
	};
}

#endif // !INCLUDED_UI_FIELD_H
