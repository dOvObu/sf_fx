#include "ui_label.h"
#include "../fonts_provider.h"
#include "../extentions.h"

namespace qw
{
UiLabel::UiLabel(sf::String text, char const* font)
	:_text(text,FontsProvider::GetFont(font))
{}


void UiLabel::SetPosition(sf::Vector2f const& position)
{
	_text.setPosition(position);
}


sf::Vector2f UiLabel::GetPosition()
{
	return _text.getPosition();
}


void UiLabel::SetRotation(float angle)
{
	_text.setRotation(angle * QW_RAD_TO_DEG);
}


float UiLabel::GetRotation()
{
	return _text.getRotation() * QW_DEG_TO_RAD;
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
