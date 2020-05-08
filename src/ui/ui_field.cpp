#include "ui_field.h"
#include "../toglable.h"


qw::UiField::UiField(sf::Vector2f position, sf::Vector2f size, sf::Color color)
	:_position(position), _bkgColor(color), _toglable(Toglable::Spawn(_position))
{
	_toglable->SetColor(_bkgColor);
	auto toglable = _toglable;
	auto& ref = *this;
	
	_toglable->OnDrag += [&ref, toglable]()
	{
		ref.SetPosition(toglable->GetPosition());
	};
}


void qw::UiField::SetPosition(sf::Vector2f const& position)
{
	_position = position;
}


sf::Vector2f qw::UiField::GetPosition()
{
	return _position;
}


std::vector<qw::IUiItem*>& qw::UiField::Childs()
{
	return _childs;
}


void qw::UiField::AddChild(IUiItem* new_ui_item)
{
	_childs.push_back(new_ui_item);
}
