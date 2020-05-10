#include "ui_field.h"
#include "../sfml_extentions.h"

namespace qw
{
	UiField::UiField(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::vector<IUiItem*> const& childs, bool drawAsSpawned)
		:_position(position)
		,_bkgColor(color)
		,_toglable(drawAsSpawned ? Toglable::Spawn(_position) : Toglable::PushToPackage(_position))
		,_childs(childs)
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



		_toglable->OnDrag[this] = [&ref, &toglable]()
		{
			ref.SetPosition(toglable->GetPosition());
		};


		_toglable->OnRotate[this] = [&ref, &toglable]()
		{
			ref.SetRotation(toglable->GetRotation());
		};


		_toglable->OnDelete[this] = [&ref,&toglable]()
		{
			if (toglable != nullptr)
			{
				if (!toglable->IsDrawableAsSpawned())
				{
					IUiItem::CollectGarbage(&ref);
				}
				toglable = nullptr;
			}
		};


		_toglable->OnDraw[this] = [&ref, &toglable]()
		{
			if (toglable != nullptr && toglable->IsDrawableAsSpawned())
			{
				ref.Draw();
			}
		};
	}


	UiField::~UiField()
	{
		_childs.clear();
		_DetachFromParent();

		if (_toglable != nullptr)
		{
			auto toglable = _toglable;
			_toglable = nullptr;
			Toglable::Delete(toglable);
		}
	}


	IUiItem* UiField::SetPosition(sf::Vector2f const& position)
	{
		if (_toglable != nullptr)
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
		return this;
	}


	sf::Vector2f UiField::GetPosition()
	{
		return _toglable != nullptr ? _toglable->GetPosition() : sf::Vector2f{};
	}


	IUiItem* UiField::SetSize(sf::Vector2f const& size)
	{
		if (_toglable != nullptr)
		{
			_toglable->SetScale(size.x, size.y);
		}
		return this;
	}


	sf::Vector2f UiField::GetSize()
	{
		return _toglable != nullptr ? _toglable->GetScale() : sf::Vector2f();
	}


	IUiItem* UiField::SetRotation(float angle)
	{
		if (_toglable != nullptr)
		{
			_toglable->SetRotation(angle);
			if (!_childs.empty())
			{
				float d = angle - _angle;
				_angle = angle;
				auto pos = GetPosition();

				for (auto item : _childs)
				{
					auto v = item->GetPosition() - pos;
					item->SetRotation(item->GetRotation() + d);
					item->SetPosition(pos + rotate(v, d));
				}
			}
		}
		return this;
	}


	float UiField::GetRotation()
	{
		return _toglable != nullptr ? _toglable->GetRotation() : 0.f;
	}


	std::vector<IUiItem*>* UiField::GetChilds()
	{
		return &_childs;
	}


	IUiItem* UiField::AddChild(IUiItem* new_ui_item)
	{
		_childs.push_back(new_ui_item);
		return this;
	}


	void UiField::Draw()
	{
		if (_toglable != nullptr && !_toglable->IsDrawableAsSpawned())
		{
			_toglable->Draw();
		}

		for (auto item : _childs)
		{
			item->Draw();
		}
	}
}
