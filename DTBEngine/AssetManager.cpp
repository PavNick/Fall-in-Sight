#include "AssetManager.h"

AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager()
{
	assert(sInstance == nullptr);
	sInstance = this;
}

sf::Texture & AssetManager::GetTexture(std::string const &fname)
{
	std::string name = TEXTURES_DIR + fname;
	auto &map = sInstance->m_Textures;
	auto pair_founded = map.find(name);

	if (pair_founded != map.end())
	{
		return pair_founded->second;
	}
	else
	{
		auto &resource = map[name];
		resource.loadFromFile(name);
		return resource;
	}
}

sf::SoundBuffer & AssetManager::GetSoundBuffer(std::string const &name)
{
	auto &map = sInstance->m_SoundBuffers;
	auto pair_founded = map.find(name);

	if (pair_founded != map.end())
	{
		return pair_founded->second;
	}
	else
	{
		auto &resource = map[name];
		resource.loadFromFile(name);
		return resource;
	}
}

sf::Font & AssetManager::GetFont(std::string const &name)
{
	auto &map = sInstance->m_Fonts;
	auto pair_founded = map.find(name);

	if (pair_founded != map.end())
	{
		return pair_founded->second;
	}
	else
	{
		auto &resource = map[name];
		resource.loadFromFile(name);
		return resource;
	}
}

