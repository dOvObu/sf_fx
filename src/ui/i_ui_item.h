#ifndef INCLUDED_I_UI_WIDGET_H
#define INCLUDED_I_UI_WIDGET_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <iostream>

namespace qw
{
	struct IUiItem
	{
		virtual IUiItem* SetPosition(sf::Vector2f const& position) = 0;
		virtual sf::Vector2f GetPosition() = 0;
		virtual IUiItem* SetSize(sf::Vector2f const& position) = 0;
		virtual sf::Vector2f GetSize() = 0;
		virtual IUiItem* SetRotation(float angle) = 0;
		virtual float GetRotation() = 0;
		virtual std::vector<IUiItem*>* GetChilds() = 0;
		virtual IUiItem* AddChild(IUiItem* new_ui_item) = 0;
		virtual void Draw() = 0;
		void SetParent(IUiItem* parent) { if (parent != this) { _parent = parent; if (parent != nullptr) SetPosition(_parent->GetPosition() + GetPosition()); } }
		IUiItem* GetParent() { return _parent; }
		virtual ~IUiItem() {}

		static void Init(sf::RenderWindow& rw);
		static void CollectGarbage(IUiItem* item);
		static void ClearGarbage();
	protected:
		static sf::RenderWindow* _pw;
		static std::vector<IUiItem*> _garbage;
		IUiItem* _parent{ nullptr };
		void _DetachFromParent()
		{
			if (_parent != nullptr)
			{
				auto childs = _parent->GetChilds();
				if (childs != nullptr)
				{
					auto ptr = this;
					childs->erase(std::remove_if(std::begin(*childs), std::end(*childs),
						[ptr](auto item)
						{
							return item == ptr;
						}));
				}
			}
		}
	};
}

#endif // !INCLUDED_I_UI_WIDGET_H
