#pragma once

#include "libs.h"
#include <assert.h>

#define TEXTURES_DIR "bin/content/textures/"

class AssetManager
{
public:
	AssetManager();

	static sf::Texture & GetTexture(std::string const &);
	static sf::SoundBuffer & GetSoundBuffer(std::string const &);
	static sf::Font & GetFont(std::string const &);
private:
	std::map<std::string, sf::SoundBuffer> m_SoundBuffers;
	std::map<std::string, sf::Font> m_Fonts;
	std::map<std::string, sf::Texture> m_Textures;
	std::map<std::string, std::unique_ptr<sf::Shader>> m_Shaders;

	static AssetManager *sInstance;
};