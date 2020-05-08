#include "ui_field.h"
#include "../toglable.h"


namespace qw
{
	UiField::UiField(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::vector<IUiItem*> const& _childs, bool drawAsSpawned)
		:_position(position)
		,_bkgColor(color)
		,_toglable(drawAsSpawned ? Toglable::Spawn(_position) : Toglable::PushToPackage(_position))
		,_childs(_childs)
	{
		_toglable->SetDrawableAsSpawned(drawAsSpawned);
		_toglable->SetColor(_bkgColor);
		_toglable->SetScale(.5f * size.x, .5f * size.y);
		if (drawAsSpawned)
		{
			Toglable::PackPackage();
		}

		auto& toglable = _toglable;
		auto& ref = *this;
		for (auto item : _childs)
		{
			item->SetParent(this);
		}

		_toglable->OnDrag += [&ref, &toglable]()
		{
			ref.SetPosition(toglable->GetPosition());
		};

		_toglable->OnDelete += [&toglable]()
		{
			toglable = nullptr;
		};

		_toglable->OnDraw += [&ref, &toglable]()
		{
			if (toglable->IsDrawableAsSpawned())
			{
				ref.Draw();
			}
		};
	}


	UiField::~UiField()
	{
		if (_toglable != nullptr)
		{
			delete _toglable;
		}
		for (auto& item : _childs)
		{
			delete item;
		}
	}


	void UiField::SetPosition(sf::Vector2f const& position)
	{
		_toglable->SetPosition(position.x, position.y);
		if (!_childs.empty())
		{
			sf::Vector2f buff = _position;
			_position = position;

			for (auto item : _childs)
			{
				item->SetPosition(item->GetPosition() + (_position - buff));
			}
		}
	}


	sf::Vector2f UiField::GetPosition()
	{
		return _toglable->GetPosition();
	}


	std::vector<IUiItem*>& UiField::GetChilds()
	{
		return _childs;
	}


	void UiField::AddChild(IUiItem* new_ui_item)
	{
		_childs.push_back(new_ui_item);
	}


	void UiField::Draw()
	{
		if (!_toglable->IsDrawableAsSpawned())
		{
			_toglable->Draw();
		}

		for (auto item : _childs)
		{
			item->Draw();
		}
	}
}
