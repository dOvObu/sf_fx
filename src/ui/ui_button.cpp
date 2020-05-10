#include "ui_button.h"
#include "../extentions.h"
#include "../fonts_provider.h"
#include "../sfml_extentions.h"
namespace qw
{
	UiButton::UiButton(char const* font, unsigned char_size, sf::String text, sf::Color text_color, sf::Vector2f position, sf::Vector2f size, sf::Color color, bool drawAsSpawned)
		:_str(text)
		,_text(text, FontsProvider::GetFont(font), char_size)
		,_position(position)
		,_bkgColor(color)
		,_toglable(drawAsSpawned ? Toglable::Spawn(_position) : Toglable::PushToPackage(_position))
	{
		_text.setFillColor(text_color);
		auto textBounds = _text.getLocalBounds();
		_text.setOrigin(.5f * textBounds.width, .75f * textBounds.height);

		_toglable->SetDrawableAsSpawned(drawAsSpawned);
		_toglable->SetColor(_bkgColor);
		_toglable->SetScale(.5f * size.x, .5f * size.y);
		if (drawAsSpawned)
		{
			Toglable::PackPackage();
		}

		auto& toglable = _toglable;
		auto& ref = *this;
		auto& pos = _position;
		auto& ang = _angle;


		_toglable->OnDrag[this] = [&ref, &toglable, &pos]()
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
			{
				ref.SetPosition(toglable->GetPosition());
			}
			else
			{
				ref.SetPosition(pos);
			}
		};


		_toglable->OnRotate[this] = [&ref, &toglable, &ang]()
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
			{
				ref.SetRotation(toglable->GetRotation());
			}
			else
			{
				ref.SetRotation(ang);
			}
		};


		_toglable->OnDelete[this] = [&ref, &toglable]()
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


	UiButton::~UiButton()
	{
		_DetachFromParent();

		if (_toglable != nullptr)
		{
			auto toglable = _toglable;
			_toglable = nullptr;
			Toglable::Delete(toglable);
		}
	}


	IUiItem* UiButton::SetPosition(sf::Vector2f const& position)
	{
		_position = position;
		if (_toglable != nullptr)
		{
			_toglable->SetPosition(position.x, position.y);
			_text.setPosition(position);
		}
		return this;
	}


	sf::Vector2f UiButton::GetPosition()
	{
		return _toglable != nullptr ? _toglable->GetPosition() : sf::Vector2f{};
	}


	IUiItem* UiButton::SetSize(sf::Vector2f const& size)
	{
		if (_toglable != nullptr)
		{
			_toglable->SetScale(size.x, size.y);
		}
		return this;
	}


	sf::Vector2f UiButton::GetSize()
	{
		return _toglable != nullptr ? _toglable->GetScale() : sf::Vector2f{};
	}


	IUiItem* UiButton::SetRotation(float angle)
	{
		_angle = angle;
		if (_toglable != nullptr)
		{
			_toglable->SetRotation(angle);
			_text.setRotation(angle * QW_RAD_TO_DEG);
		}
		return this;
	}


	float UiButton::GetRotation()
	{
		return _toglable != nullptr ? _toglable->GetRotation() : 0.f;
	}


	std::vector<IUiItem*>* UiButton::GetChilds()
	{
		return nullptr;
	}


	IUiItem* UiButton::AddChild(IUiItem* new_ui_item)
	{
		return this;
	}


	void UiButton::Draw()
	{
		if (_toglable != nullptr)
		{
			if (!_toglable->IsDrawableAsSpawned()) _toglable->Draw();
			_pw->draw(_text);
		}
	}


	UiButton* UiButton::AddCallback(std::function<void(void)> cb)
	{
		if (_toglable != nullptr)
		{
			_toglable->OnClick += cb;
		}
		return this;
	}
}
