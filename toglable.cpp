#include "toglable.h"
#include "extentions.h"
#include "sfml_extentions.h"


sf::RenderWindow* qw::Toglable::pw{ nullptr };


qw::Toglable::Toglable()
{
	Toglable& ref = *this;
	bool& selected = _selected;
	float& rotation_drag_start = _rotation_drag_start;
	sf::Vector2f& mouse_drag_start = _mouse_drag_start;
	sf::Vector2f& pos_drag_start = _position_drag_start
	          , & scale_drag_start = _scale_drag_start;


	Mouse::OnMousePressed[this] = [&ref, &pos_drag_start, &scale_drag_start, &rotation_drag_start, &mouse_drag_start]()
	{
		auto mp = Mouse::GetMousePosition();
		if (ref.Contains(mp))
		{
			mouse_drag_start = Mouse::GetMousePosition();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			{
				pos_drag_start = ref.GetPosition();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				scale_drag_start = ref.GetScale();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				auto mp = Mouse::GetMousePosition();
				mp -= ref.GetPosition();
				rotation_drag_start = ref.GetRotation() - atan2f(mp.y, mp.x);
			}
			ref.Select();
		}
	};

	Mouse::OnMouseReleased[this] = [&selected, &pos_drag_start, &scale_drag_start, &rotation_drag_start, &mouse_drag_start]()
	{
		selected = false;
		pos_drag_start = scale_drag_start = mouse_drag_start = { 0.f,0.f };
		rotation_drag_start = 0.f;
	};

	Mouse::OnMouseDown[this] = [&ref, &selected, &pos_drag_start, &scale_drag_start, &rotation_drag_start, &mouse_drag_start]()
	{
		if (selected)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			{
				auto mp = Mouse::GetMousePosition();
				mp -= mouse_drag_start;
				const auto& pos = pos_drag_start + mp;
				ref.SetPosition(pos.x, pos.y);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				auto mp = Mouse::GetMousePosition();
				mp -= mouse_drag_start;
				auto scl = rotate(scale_drag_start + mp, ref.GetRotation());
				ref.SetScale(scl.x, scl.y);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				auto mp = Mouse::GetMousePosition();
				mp = mp - ref.GetPosition();
				ref.SetRotation(rotation_drag_start + atan2f(mp.y, mp.x));
			}
		}
	};
}


qw::Toglable::~Toglable()
{
	Mouse::OnMousePressed -= this;
	Mouse::OnMouseReleased -= this;
	Mouse::OnMouseDown -= this;
}


void qw::Toglable::SetActive(bool active)
{
	Toglable::_active = active;
}


void qw::Toglable::Draw()
{
	if (_active)
	{
		_v[0].position = { -1.f,-1.f }, _v[1].position = { 1.f,-1.f };
		_v[2].position = { 1.f, 1.f }, _v[3].position = { -1.f, 1.f };
		Transform();
		pw->draw(_v, 4, sf::Quads);
	}
}


void qw::Toglable::SetPosition(float x, float y) { _positionX = x, _positionY = y; }
void qw::Toglable::SetScale(float x, float y) { _scaleX = x, _scaleY = y; }
void qw::Toglable::SetRotation(float angle) { _angle = angle; }


sf::Vector2f qw::Toglable::GetPosition() { return { _positionX, _positionY }; }
sf::Vector2f qw::Toglable::GetScale() { return { _scaleX, _scaleY }; }
float qw::Toglable::GetRotation() { return _angle; }


void qw::Toglable::Select()
{
	_selected = true;
	for (auto& p : _v) p.color = sf::Color(255, 224, 155);
}


bool qw::Toglable::Contains(sf::Vector2f const& p)
{
	return is_inside(_v, 4, p);
}


void qw::Toglable::Init(sf::RenderWindow& rw)
{
	pw = &rw;
}

 //===O===\\
// private \\
\\_________//
void qw::Toglable::Transform()
{
	for (auto& it : _v)
	{
		rotate(it.position *= {_scaleX, _scaleY}, _angle) += {_positionX, _positionY};
	}
}
