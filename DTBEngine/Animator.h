#pragma once


#include "libs.h"
#include "AssetManager.h"

class Animator
{
public:
	struct Animation
	{
		std::string mName;
		std::string mTextureName;
		std::vector<sf::IntRect> mFrames;
		sf::Time mDuration;
		bool m_looping;

		Animation(std::string const &name, std::string const &texture_name,
			sf::Time const &duration, bool looping)
			: mName(name), mTextureName(texture_name),
			mDuration(duration), m_looping(looping)
		{}

		void addFrames(sf::Vector2i const &start_from,
			sf::Vector2i const &framesize, unsigned int frames)
		{
			sf::Vector2i current = start_from;
			for (unsigned int i = 0; i < frames; i++)
			{
				mFrames.push_back(sf::IntRect(current.x, current.y, framesize.x, framesize.y));
				current.x += framesize.x;
			}
		}
	};

	Animator(sf::Sprite &sprite): m_sprite(sprite),
		m_current_time(), m_current_animation(nullptr) {}

	Animator::Animation &createAnimation(std::string const &name,
		std::string const &texture_name, sf::Time const &duration,
		bool loop = false)
	{
		m_animations.push_back(Animator::Animation(name, texture_name, duration, loop));
		if (m_current_animation == nullptr)
			switchAnimation(&m_animations.back());
		return m_animations.back();
	}

	void update(sf::Time const &dt)
	{
		if (m_current_animation == nullptr)
			return;

		m_current_time += dt;

		float scaled_time = (m_current_time.asSeconds() / m_current_animation->mDuration.asSeconds());
		int num_frames = m_current_animation->mFrames.size();
		int current_frame = static_cast<int>(scaled_time * num_frames);

		if (m_current_animation->m_looping)
			current_frame %= num_frames;
		else if (current_frame >= num_frames)
			current_frame = num_frames - 1;

		m_sprite.setTextureRect(m_current_animation->mFrames[current_frame]);
	}

	bool switchAnimation(std::string const &name)
	{
		auto animation = findAnimation(name);
		if (animation != nullptr)
		{
			switchAnimation(animation);
			return true;
		}
		return false;
	}

	std::string getCurrentAnimationName() const
	{
		if (m_current_animation != nullptr)
			return m_current_animation->mName;
		return "";
	}

private:
	Animator::Animation *findAnimation(std::string const &name)
	{
		for (auto it = m_animations.begin();
			it != m_animations.end(); ++it)
		{
			if (it->mName == name)
				return &*it;
		}
		return nullptr;
	}

	void switchAnimation(Animator::Animation *animation)
	{
		if (animation != nullptr)
		{
			m_sprite.setTexture(AssetManager::GetTexture(animation->mTextureName));
		}
		m_current_animation = animation;
		m_current_time = sf::Time::Zero;
	}

	sf::Sprite &m_sprite;
	sf::Time m_current_time;
	std::list<Animator::Animation> m_animations;
	Animator::Animation *m_current_animation;
};