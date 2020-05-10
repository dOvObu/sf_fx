#include "ui_label.h"
#include "../fonts_provider.h"
#include "../extentions.h"

namespace qw
{
UiLabel::UiLabel(sf::String text, char const* font, unsigned char_size)
	:_str(text)
	,_text(text,FontsProvider::GetFont(font), char_size)
{
	std::cout << "_text char width :: " << _text.getCharacterSize() << ", " << (_text.findCharacterPos(1).x - _text.findCharacterPos(0).x) << "\n";
}


IUiItem* UiLabel::SetPosition(sf::Vector2f const& position)
{
	_text.setPosition(position);
	return this;
}


sf::Vector2f UiLabel::GetPosition()
{
	return _text.getPosition();
}


IUiItem* UiLabel::SetSize(sf::Vector2f const& size)
{
	size_t width{ 0 }, height{ 0 };
	{
		sf::Text tmp("ab", *_text.getFont(), _text.getCharacterSize());
		float d = tmp.findCharacterPos(1).x - tmp.findCharacterPos(0).x;
		width = size.x / d;
		tmp.setString("a\nb");
		d = tmp.findCharacterPos(2).y - tmp.findCharacterPos(0).y;
		height = size.y / d;
		std::cout << "height ::: " << height << std::endl;
	}
	sf::String tmp = _str;
	size_t last_space{ width };
	if (width > 1)
	{
		for (size_t idx{ 0 }, count{ 0 }; tmp.getSize() > idx; ++idx)
		{
			auto ch = tmp[idx];
			if (ch == ' ' || ch == '\t' || ch == '\n') last_space = idx + 1;
			if (ch == '\n') count = 0;
			if (count >= width)
			{
				count = 0;
				tmp.insert(last_space, '\n');
				idx = last_space;
				last_space += width + 1;
			}
			else
			{
				++count;
			}

			std::cout << tmp[idx] << std::endl;
			if (tmp[idx] == '\n')
			{
				--height;
				if (height == 0)
				{
					tmp = tmp.substring(0, idx);
				}
			}
		}
	}
	else
	{
		for (size_t idx = 1; tmp.getSize() > idx; idx += 2)
		{
			tmp.insert(idx, '\n');
			--height;
			if (height == 0)
			{
				tmp = tmp.substring(0, idx);
			}
		}
	}

	_text.setString(tmp);
	return this;
}


sf::Vector2f UiLabel::GetSize()
{
	return _text.getPosition();
}


IUiItem* UiLabel::SetRotation(float angle)
{
	_text.setRotation(angle * QW_RAD_TO_DEG);
	return this;
}


float UiLabel::GetRotation()
{
	return _text.getRotation() * QW_DEG_TO_RAD;
}


std::vector<IUiItem*>& UiLabel::GetChilds()
{
	return std::vector<IUiItem*>();
}


IUiItem* UiLabel::AddChild(IUiItem* new_ui_item)
{ return this; }


void UiLabel::Draw()
{
	_pw->draw(_text);
}
}
