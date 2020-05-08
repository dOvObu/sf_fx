#include "ui_field.h"
#include "../sfml_extentions.h"
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

		_toglable->OnRotate += [&ref, &toglable]()
		{
			ref.SetRotation(toglable->GetRotation());
		};

		_toglable->OnDelete += [&ref, &toglable]()
		{
			toglable = nullptr;
			toglable->OnDrag -= (void*)&ref;
			toglable->OnDraw -= (void*)&ref;
			toglable->OnRotate -= (void*)&ref;
			toglable->OnDelete -= (void*)&ref;
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


	void UiField::SetRotation(float angle)
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
				rotate(v, d);
				item->SetRotation(item->GetRotation() + d);
				item->SetPosition(pos + v);
			}
		}
	}


	float UiField::GetRotation()
	{
		return _toglable->GetRotation();
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

																	auto v = sf::Vector2f(300.f, 0.f);
																	sf::Vertex vx[] = { {GetPosition(),sf::Color::Red}, {GetPosition() + rotate(v, GetRotation()),sf::Color::Red} };
																	_pw->draw(vx, 2, sf::LineStrip);

		for (auto item : _childs)
		{
			item->Draw();
		}
	}
}
