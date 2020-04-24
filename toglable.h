#ifndef INCLUDED_TOGLABLE_H
#define INCLUDED_TOGLABLE_H
#include "mouse.h"
#include <memory>
#include <list>


namespace qw
{
	struct Toglable
	{
		Toglable();
		~Toglable();
		void Subscribe();

		void SetActive(bool active);
		void Draw();
		void SetPosition(float x, float y);
		void SetScale(float x, float y);
		void SetRotation(float a);
		sf::Vector2f GetPosition();
		sf::Vector2f GetScale();
		float GetRotation();

		void Select(bool selected = true);
		bool Contains(sf::Vector2f const& p);
		void SelectToDrag();

		static void Init(sf::RenderWindow& rw);
		static void DrawSpawned();
		static Toglable* Spawn(sf::Vector2f p);
		static Toglable* Spawn(Toglable* toglable);
		static void KeepOneSelected();

		enum class Action { SPAWNED, SET_POSITION, SET_SCALE, SET_ANGLE };
		static void PushAction(Action a);
		static Action PopAction();
	private:
		sf::Vertex _v[4]{ sf::Vector2f{-1.f,-1.f}, sf::Vector2f{1.f,-1.f}, sf::Vector2f{1.f,1.f}, sf::Vector2f{-1.f,1.f} };
		sf::Vector2f _mouse_drag_start{ 0.f, 0.f };
		sf::Vector2f _position_drag_start{ 0.f,0.f }, _scale_drag_start{ 0.f,0.f };
		float _rotation_drag_start{ 0.f };

		float _angle{ 0.f };
		float _scaleX{ 1.f }, _scaleY{ 1.f };
		float _positionX{ 0.f }, _positionY{ 0.f };
		bool _active{ true };
		bool _selected{ false };

		void Transform();

		static sf::RenderWindow* pw;
		static std::vector<std::shared_ptr<Toglable>> _spawned;
		static bool _select_some;
		static std::list<Action> _actions;
	};
}


#endif // !INCLUDED_TOGLABLE_H
