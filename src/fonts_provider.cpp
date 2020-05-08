#include "fonts_provider.h"
#include <iostream>

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>


std::map<std::string, sf::Font> qw::FontsProvider::_fonts;


sf::Font& qw::FontsProvider::GetFont(char const* name)
{
	return _fonts[name];
}


void qw::FontsProvider::LoadFonts(char const* path)
{
	std::experimental::filesystem::path pth{ path };

	for (auto& it : std::experimental::filesystem::directory_iterator(pth))
	{
		auto& p = it.path();
		auto const& extension = p.extension();
		if (extension == ".otf" || extension == ".ttf")
		{
			(_fonts[p.filename().replace_extension().string()] = sf::Font()).loadFromFile(p.string());
		}
	}
}
