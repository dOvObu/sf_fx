#include "ui_field.h"
#include "../sfml_extentions.h"
#include "../toglable.h"

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

		_toglable->OnDrag += [&ref, &toglable]()
		{
			ref.SetPosition(toglable->GetPosition());
		};

		_toglable->OnRotate += [&ref, &toglable]()
		{
			ref.SetRotation(toglable->GetRotation());
		};

		_toglable->OnDelete += [&ref,&toglable]()
		{
			if (toglable != nullptr)
			{
				toglable->OnDrag -= &ref;
				toglable->OnRotate -= &ref;
				toglable->OnDraw -= &ref;
				toglable->OnDelete -= &ref;
				toglable = nullptr;
			}
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
		for (auto& item : _childs)
		{
			item->SetParent(nullptr);
			std::cout << "rm childs" << std::endl;
			delete item;
		}

		if (GetParent() != nullptr)
		{
			auto childs = GetParent()->GetChilds();
			auto ptr = this;
			std::cout << "parent childs :: " << childs.size() << std::endl;
			//childs.insert(std::begin(_childs), std::end(_childs), std::end(childs));
			std::remove_if(std::begin(childs), std::end(childs), [ptr](auto item) { return item == ptr; });
			childs.pop_back();
			std::cout << "parent childs inserted :: " << childs.size() << std::endl;
			_childs.clear();
		}

		if (_toglable != nullptr)
		{
			Toglable::CollectGarbage(_toglable);
		}
	}


	void UiField::SetPosition(sf::Vector2f const& position)
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
	}


	sf::Vector2f UiField::GetPosition()
	{
		return _toglable != nullptr ? _toglable->GetPosition() : sf::Vector2f{};
	}


	void UiField::SetRotation(float angle)
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
	}


	float UiField::GetRotation()
	{
		return _toglable != nullptr ? _toglable->GetRotation() : 0.f;
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
