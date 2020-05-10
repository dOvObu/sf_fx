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
	auto childs = item->GetChilds();
	if (childs != nullptr)
	{
		for (auto ptr : *childs)
		{
			CollectGarbage(ptr);
		}
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
