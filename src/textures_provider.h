#ifndef INCLUDED_TEXTURES_PROVIDER_H
#define INCLUDED_TEXTURES_PROVIDER_H
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <map>

namespace qw
{
	struct TexturesProvider
	{
		static sf::Texture& GetTexture(char const* name);
		static void LoadTextures(char const* path);
	private:
		static std::map<std::string, sf::Texture> _textures;
	};
}

#endif // !INCLUDED_TEXTURES_PROVIDER_H
