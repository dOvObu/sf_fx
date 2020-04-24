#include "textures_provider.h"
#include <iostream>

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

std::map<std::string, sf::Texture> TexturesProvider::_textures;



void TexturesProvider::LoadTextures(char const* path)
{
	std::experimental::filesystem::path pth{ path };
	
	for (auto& it : std::experimental::filesystem::directory_iterator(pth))
	{
		auto& p = it.path();

		if (p.extension() == ".png")
		{
			(_textures[p.filename().replace_extension().string()] = sf::Texture()).loadFromFile(p.string());
		}
	}
}
