#include "i_ui_item.h"

sf::RenderWindow* qw::IUiItem::_pw;


void qw::IUiItem::Init(sf::RenderWindow& rw)
{
	_pw = &rw;
}
