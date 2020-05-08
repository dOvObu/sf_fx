#include "toglable.h"
#include "extentions.h"
#include "sfml_extentions.h"
#include "textures_provider.h"

sf::RenderWindow* qw::Toglable::pw{ nullptr };
std::vector<std::shared_ptr<qw::Toglable>> qw::Toglable::_spawned;
std::vector<std::shared_ptr<qw::Toglable>> qw::Toglable::_package;
bool qw::Toglable::_select_some{ false };
std::list<qw::Toglable::Action> qw::Toglable::_actions;


qw::Toglable::Toglable()
{
	_Init();
}


qw::Toglable::Toglable(char const* name, float x = 0.f, float y = 0.f)
	:_positionX(x)
	,_positionY(y)
{
	_states.texture = &TexturesProvider::GetTexture(name);
	auto size = _states.texture->getSize();
	_v[0].texCoords = sf::Vector2f( 0.f,0.f );
	_v[1].texCoords = sf::Vector2f( size.x,0.f );
	_v[2].texCoords = sf::Vector2f( size.x,size.y );
	_v[3].texCoords = sf::Vector2f( 0.f,size.y );
	_Init();
}


qw::Toglable::Toglable(float x, float y)
	:_positionX(x)
	,_positionY(y)
{
	_Init();
}


qw::Toglable::~Toglable()
{
	Mouse::OnMouseLeftButtonPressed -= this;
	Mouse::OnMouseLeftButtonReleased -= this;
	Mouse::OnMouseLeftButtonDown -= this;
}


void qw::Toglable::SetActive(bool active)
{
	Toglable::_active = active;
}


void qw::Toglable::Draw()
{
	if (_active)
	{
		_v[0].position = { -1.f,-1.f }, _v[1].position = {  1.f,-1.f };
		_v[2].position = {  1.f, 1.f }, _v[3].position = { -1.f, 1.f };
		
		_Transform();
		pw->draw(_v, 4, sf::Quads, _states);

		OnDraw();
	}
}


void qw::Toglable::SetPosition(float x, float y) { _positionX = x, _positionY = y; OnSetPosition(); }
void qw::Toglable::SetScale(float x, float y) { _scaleX = x, _scaleY = y; }
void qw::Toglable::SetOrigin(float x, float y) { _originX = x, _originY = y; }
void qw::Toglable::SetRotation(float angle) { _angle = angle; }
void qw::Toglable::SetColor(sf::Color color) { _color = color; for (auto& v : _v) v.color = color; }
void qw::Toglable::SetDrawableAsSpawned(bool drawable) { _drawable_as_spawned = drawable; }
bool qw::Toglable::IsDrawableAsSpawned() { return _drawable_as_spawned; }

sf::Vector2f qw::Toglable::GetPosition() { return { _positionX, _positionY }; }
sf::Vector2f qw::Toglable::GetScale() { return { _scaleX, _scaleY }; }
sf::Vector2f qw::Toglable::GetOrigin() { return { _originX, _originY }; }
float qw::Toglable::GetRotation() { return _angle; }


void qw::Toglable::Select(bool selected)
{
	_select_some = _selected = selected;
	
	for (auto& v : _v)
	{
		v.color = !selected ? _color : sf::Color::Yellow;
	}
}


bool qw::Toglable::Contains(sf::Vector2f const& p)
{
	return is_inside(_v, 4, p);
}


void qw::Toglable::SelectToDrag()
{
	Select();
	PushAction(Action::SET_POSITION);
}


void qw::Toglable::KeepOneSelected()
{
	bool first{ true };
	for (auto it = _spawned.rbegin(); it != _spawned.rend(); ++it)
	{
		if ((*it)->_selected)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				(*it)->Select(false);
			}
		}
	}
}


void qw::Toglable::PushAction(qw::Toglable::Action action)
{
	_actions.push_back(action);
	if (_actions.size() > 10)
	{
		_actions.pop_front();
	}
}


qw::Toglable::Action qw::Toglable::PopAction()
{
	auto action = _actions.back();
	_actions.pop_back();
	return action;
}


void qw::Toglable::Init(sf::RenderWindow& rw)
{
	pw = &rw;
}


void qw::Toglable::DrawSpawned()
{
	for (auto& it : _spawned)
	{
		if (it->_drawable_as_spawned)
		{
			it->Draw();
		}
	}
}

qw::Toglable* qw::Toglable::Spawn(sf::Vector2f p)
{
	qw::Toglable* last_spawned{ nullptr };
	_spawned.push_back(std::shared_ptr<Toglable>{ last_spawned = new Toglable() });
	last_spawned->SetPosition(p.x, p.y);
	PushAction(Action::SPAWNED);
	return last_spawned;
}

qw::Toglable* qw::Toglable::Spawn(Toglable* toglable)
{
	_spawned.push_back(std::shared_ptr<Toglable>{ toglable });
	PushAction(Action::SPAWNED);
	return toglable;
}

qw::Toglable* qw::Toglable::Spawn(char const* name, sf::Vector2f p)
{
	qw::Toglable* last_spawned{ nullptr };
	_spawned.push_back(std::shared_ptr<Toglable>{ last_spawned = new Toglable(name) });
	last_spawned->SetPosition(p.x, p.y);
	PushAction(Action::SPAWNED);
	return last_spawned;
}

qw::Toglable* qw::Toglable::PushToPackage(sf::Vector2f p)
{
	qw::Toglable* last_spawned{ nullptr };
	_package.push_back(std::shared_ptr<Toglable>{ last_spawned = new Toglable() });
	last_spawned->SetPosition(p.x, p.y);
	PushAction(Action::SPAWNED);
	return last_spawned;
}

void qw::Toglable::PackPackage()
{
	_spawned.insert(std::end(_spawned), std::rbegin(_package), std::rend(_package));
	_package.clear();
}

void qw::Toglable::Delete(qw::Toglable* toglable)
{
	toglable->OnDelete();
	_spawned.erase(std::remove_if(std::begin(_spawned), std::end(_spawned), [&toglable](std::shared_ptr<Toglable>& sp) { return sp.get() == toglable; }));
}

 //===O===\\
// private \\
\\_________//

void qw::Toglable::_Init()
{
	Toglable& ref = *this;
	bool& selected = _selected;
	float& rotation_drag_start = _rotation_drag_start;
	sf::Vector2f& mouse_drag_start = _mouse_drag_start;
	sf::Vector2f& pos_drag_start = _position_drag_start;
	sf::Vector2f& scale_drag_start = _scale_drag_start;
	sf::Vector2f& origin_drag_start = _origin_drag_start;

	Mouse::OnMouseLeftButtonPressed[this] = [&ref, &pos_drag_start, &scale_drag_start, &rotation_drag_start, &origin_drag_start, &mouse_drag_start]()
	{
		auto mp = Mouse::GetMousePosition();
		if (ref.Contains(mp))
		{
			mouse_drag_start = mp;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				scale_drag_start = ref.GetScale();
				rotation_drag_start = -ref.GetRotation();
				ref.PushAction(Action::SET_SCALE);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				auto mp = Mouse::GetMousePosition();
				mp -= ref.GetPosition();
				rotation_drag_start = ref.GetRotation() - atan2f(mp.y, mp.x);
				ref.PushAction(Action::SET_ANGLE);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			{
				origin_drag_start = ref.GetOrigin();
				rotation_drag_start = -ref.GetRotation();
				ref.PushAction(Action::SET_ANCORE);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				PushAction(Action::DELETED);
			}
			else
			{
				pos_drag_start = ref.GetPosition();
				ref.PushAction(Action::SET_POSITION);
			}
			ref.Select();
			ref.OnClick();
		}
	};

	Mouse::OnMouseLeftButtonReleased[this] = [&ref, &selected, &pos_drag_start, &scale_drag_start, &rotation_drag_start, &origin_drag_start, &mouse_drag_start]()
	{
		selected = false;
		origin_drag_start = pos_drag_start = scale_drag_start = mouse_drag_start = { 0.f,0.f };
		rotation_drag_start = 0.f;
		ref.Select(false);
	};

	auto& actions = _actions;
	Mouse::OnMouseLeftButtonDown[this] = [&ref, &selected, &actions, &pos_drag_start, &scale_drag_start, &rotation_drag_start, &origin_drag_start, &mouse_drag_start]()
	{
		if (_select_some)
		{
			ref.KeepOneSelected();
			_select_some = false;
		}
		if (selected)
		{
			auto& last_action = actions.back();

			if (last_action == Action::SET_SCALE && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				auto mp = Mouse::GetMousePosition() - mouse_drag_start;
				auto scl = scale_drag_start + rotate(mp, rotation_drag_start);

				ref.SetScale(scl.x, scl.y);
			}
			else if (last_action == Action::SET_ANGLE && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				auto mp = Mouse::GetMousePosition();
				mp = mp - ref.GetPosition();
				ref.SetRotation(rotation_drag_start + atan2f(mp.y, mp.x));
			}
			else if (last_action == Action::SET_ANCORE && sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			{
				auto mp = Mouse::GetMousePosition() - mouse_drag_start;
				auto orig = origin_drag_start + rotate(mp, rotation_drag_start);
				ref.SetOrigin(-orig.x,-orig.y);
			}
			else if (last_action == Action::DELETED && sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				Delete(&ref);
			}
			else if (last_action == Action::SET_POSITION)
			{
				auto mp = Mouse::GetMousePosition();
				mp -= mouse_drag_start;
				const auto& pos = pos_drag_start + mp;
				ref.SetPosition(pos.x, pos.y);
				ref.OnDrag();
			}
		}
	};

	std::cout << "new Toglable\n";
}


void qw::Toglable::_Transform()
{
	for (auto& it : _v)
	{
		rotate((it.position += {_originX, _originY}) *= {_scaleX, _scaleY}, _angle) += {_positionX, _positionY};
	}
}
