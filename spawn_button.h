#ifndef INCLUDED_SPAWN_BUTTON_H
#define INCLUDED_SPAWN_BUTTON_H
#include "toglable.h"

namespace qw
{
	struct SpawnButton
	{
		SpawnButton();
		~SpawnButton();
		void SetScale(float x, float y);
		void SetPosition(float x, float y);
		void Draw();
		bool Contains(sf::Vector2f const& p);
		
		static void Init(sf::RenderWindow& rw);
	private:
		sf::Vertex _v[4]{ sf::Vector2f{-1.f,-1.f}, sf::Vector2f{1.f,-1.f}, sf::Vector2f{1.f,1.f}, sf::Vector2f{-1.f,1.f} };
		float _positionX{ 0.f }, _positionY{ 0.f };
		float _scaleX{ 0.f }, _scaleY{ 0.f };
		float _angle{ 0.f };
		bool _active{ true };

		void Transform();
		static sf::RenderWindow* pw;
	};
}

#endif // !INCLUDED_SPAWN_BUTTON_H
