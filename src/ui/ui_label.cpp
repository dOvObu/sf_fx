#include "ui_label.h"
#include "../fonts_provider.h"
#include <iostream>
#include "../sfml_extentions.h"

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
	_text.setRotation(angle);
}


float UiLabel::GetRotation()
{
	return _text.getRotation();
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
															auto v = sf::Vector2f(300, 0);
															sf::Vertex vx[] = { {GetPosition(),sf::Color::Green}, {GetPosition() + rotate(v, GetRotation()),sf::Color::Green} };
															_pw->draw(vx, 2, sf::LineStrip);
}
}