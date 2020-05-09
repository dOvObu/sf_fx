#include "i_ui_item.h"

sf::RenderWindow* qw::IUiItem::_pw;
std::vector<qw::IUiItem*> qw::IUiItem::_garbage;


void qw::IUiItem::Init(sf::RenderWindow& rw)
{
	_pw = &rw;
}


void qw::IUiItem::CollectGarbage(IUiItem* item)
{
	_garbage.push_back(item);
	for (auto ptr : item->GetChilds())
	{
		CollectGarbage(ptr);
	}
}


void qw::IUiItem::ClearGarbage()
{
	while (!_garbage.empty())
	{
		auto garbage = _garbage.back();
		_garbage.pop_back();
		delete garbage;
	}
}
