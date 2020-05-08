#ifndef INCLUDED_FONTS_PROVIDER_H
#define INCLUDED_FONTS_PROVIDER_H
#include <SFML/Graphics/Font.hpp>
#include <string>
#include <map>

namespace qw
{
	struct FontsProvider
	{
		static sf::Font& GetFont(char const* name);
		static void LoadFonts(char const* path);
	private:
		static std::map<std::string, sf::Font> _fonts;
	};
}

#endif // !INCLUDED_FONTS_PROVIDER_H
