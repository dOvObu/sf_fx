#include "ui_label.h"
#include "../fonts_provider.h"
#include <iostream>

namespace qw
{
UiLabel::UiLabel(sf::String text, char const* font)
	:_text(text,FontsProvider::GetFont(font))
{
}


void UiLabel::SetPosition(sf::Vector2f const& position)
{
	_text.setPosition(position);
}


sf::Vector2f UiLabel::GetPosition()
{
	return _text.getPosition();
}


std::vector<IUiItem*>& UiLabel::GetChilds()
{
	return std::vector<IUiItem*>();
}


void UiLabel::AddChild(IUiItem* new_ui_item)
{}


void UiLabel::Draw()
{
	_pw->draw(_text);
}
}
