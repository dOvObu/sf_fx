#ifndef INCLUDED_TOGLABLE_H
#define INCLUDED_TOGLABLE_H
#include "mouse.h"
#include <memory>
#include <set>
#include <list>


namespace qw
{
	struct Toglable
	{
		Toglable();
		Toglable(char const* name, float x, float y);
		Toglable(float x, float y);
		~Toglable();

		Event OnSetPosition{"OnSetPosition"};
		Event OnClick      {"OnClick      "};
		Event OnDrag       {"OnDrag       "};
		Event OnRotate     {"OnRotate     "};
		Event OnDraw       {"OnDraw       "};
		Event OnDelete     {"OnDelete     "};

		void SetActive(bool active);
		void Draw();
		void SetPosition(float x, float y);
		void SetScale(float x, float y);
		void SetOrigin(float x, float y);
		void SetRotation(float a);
		void SetColor(sf::Color color=sf::Color::White);
		void SetDrawableAsSpawned(bool drawable);
		bool IsDrawableAsSpawned();
		sf::Vector2f GetPosition();
		sf::Vector2f GetScale();
		sf::Vector2f GetOrigin();
		float GetRotation();

		void Select(bool selected = true);
		bool Contains(sf::Vector2f const& p);
		void SelectToDrag();

		static void Init(sf::RenderWindow& rw);
		static void DrawSpawned();
		static Toglable* Spawn(sf::Vector2f p);
		static Toglable* Spawn(Toglable* toglable);
		static Toglable* Spawn(char const* name, sf::Vector2f p);
		static Toglable* PushToPackage(sf::Vector2f p);
		static void PackPackage();
		static void Delete(Toglable* toglable);
		static void CollectGarbage(Toglable* toglable);
		static void ClearGarbage();
		static void KeepOneSelected();

		enum class Action { SPAWNED, DELETED, SET_POSITION, SET_SCALE, SET_ANCORE, SET_ANGLE };
		static void PushAction(Action a);
		static Action PopAction();
	private:
		sf::Vertex _v[4]{ sf::Vector2f{-1.f,-1.f}, sf::Vector2f{1.f,-1.f}, sf::Vector2f{1.f,1.f}, sf::Vector2f{-1.f,1.f} };
		sf::Vector2f _mouse_drag_start{ 0.f, 0.f };
		sf::Vector2f _position_drag_start{ 0.f,0.f }, _scale_drag_start{ 0.f,0.f }, _origin_drag_start{ 0.f, 0.f };
		float _rotation_drag_start{ 0.f };

		float _angle{ 0.f };
		float _scaleX{ 1.f }, _scaleY{ 1.f };
		float _positionX{ 0.f }, _positionY{ 0.f };
		float _originX{ 0.f }, _originY{ 0.f };
		bool _active{ true };
		bool _selected{ false };
		bool _drawable_as_spawned{ true };
		sf::Color _color{ sf::Color::White };
		sf::RenderStates _states;

		void _Transform();
		void _Init();

		static sf::RenderWindow* pw;
		static std::vector<std::shared_ptr<Toglable>> _spawned;
		static std::vector<std::shared_ptr<Toglable>> _package;
		static std::set<Toglable*> _garbage;
		static bool _select_some;
		static std::list<Action> _actions;
	};
}


#endif // !INCLUDED_TOGLABLE_H
