#include "toglable.h"
#include "extentions.h"
#include "sfml_extentions.h"
#include "textures_provider.h"
#include "ui/i_ui_item.h"

using namespace qw;

sf::RenderWindow* Toglable::pw{ nullptr };
std::vector<std::shared_ptr<Toglable>> Toglable::_spawned;
std::vector<std::shared_ptr<Toglable>> Toglable::_package;
std::vector<Toglable*> Toglable::_garbage;
bool Toglable::_select_some{ false };
std::list<Toglable::Action> Toglable::_actions;


Toglable::Toglable()
{
	_Init();
}


Toglable::Toglable(char const* name, float x = 0.f, float y = 0.f)
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


Toglable::Toglable(float x, float y)
	:_positionX(x)
	,_positionY(y)
{
	_Init();
}


Toglable::~Toglable()
{
	Mouse::OnMouseLeftButtonPressed -= this;
	Mouse::OnMouseLeftButtonReleased -= this;
	Mouse::OnMouseLeftButtonDown -= this;

	Mouse::OnMouseMiddleButtonPressed -= this;
	Mouse::OnMouseMiddleButtonReleased -= this;
	Mouse::OnMouseMiddleButtonDown -= this;

	Mouse::OnMouseRightButtonPressed -= this;
	Mouse::OnMouseRightButtonReleased -= this;
	Mouse::OnMouseRightButtonDown -= this;
}


void Toglable::Draw()
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



void Toglable::SetActive(bool active)
{
	_active = active;
}

void Toglable::SetPosition(float x, float y)
{
	_positionX = x;
	_positionY = y;
	OnSetPosition();
}

void Toglable::SetScale(float x, float y)
{
	_scaleX = x;
	_scaleY = y;
}

void Toglable::SetOrigin(float x, float y)
{
	_originX = x;
	_originY = y;
}

void Toglable::SetRotation(float angle)
{
	_angle = angle;
}

void Toglable::SetColor(sf::Color color)
{
	_color = color;
	for (auto& v : _v) v.color = color;
}

void Toglable::SetDrawableAsSpawned(bool drawable)
{
	_drawable_as_spawned = drawable;
}

bool Toglable::IsDrawableAsSpawned()
{
	return _drawable_as_spawned;
}



sf::Vector2f Toglable::GetPosition()
{
	return { _positionX, _positionY };
}

sf::Vector2f Toglable::GetScale()
{
	return { _scaleX, _scaleY };
}

sf::Vector2f Toglable::GetOrigin()
{
	return { _originX, _originY };
}

float Toglable::GetRotation()
{
	return _angle;
}



void Toglable::Select(bool selected)
{
	_select_some = _selected = selected;
	
	for (auto& v : _v)
	{
		v.color = !selected ? _color : sf::Color(200,200,200);
	}
}


bool Toglable::Contains(sf::Vector2f const& p)
{
	return is_inside(_v, 4, p);
}


void Toglable::SelectToDrag()
{
	Select();
	PushAction(Action::SET_POSITION);
}


void Toglable::KeepOneSelected()
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


void Toglable::PushAction(Toglable::Action action)
{
	_actions.push_back(action);
	if (_actions.size() > 10)
	{
		_actions.pop_front();
	}
}


Toglable::Action Toglable::PopAction()
{
	auto action = _actions.back();
	_actions.pop_back();
	return action;
}


void Toglable::Init(sf::RenderWindow& rw)
{
	pw = &rw;
}


void Toglable::DrawSpawned()
{
	for (auto& it : _spawned)
	{
		if (it->_drawable_as_spawned)
		{
			it->Draw();
		}
	}
}


Toglable* Toglable::Spawn(sf::Vector2f p)
{
	Toglable* last_spawned{ nullptr };
	_spawned.push_back(std::shared_ptr<Toglable>{ last_spawned = new Toglable() });
	last_spawned->SetPosition(p.x, p.y);
	PushAction(Action::SPAWNED);
	return last_spawned;
}


Toglable* Toglable::Spawn(Toglable* toglable)
{
	_spawned.push_back(std::shared_ptr<Toglable>{ toglable });
	PushAction(Action::SPAWNED);
	return toglable;
}


Toglable* Toglable::Spawn(char const* name, sf::Vector2f p)
{
	Toglable* last_spawned{ nullptr };
	_spawned.push_back(std::shared_ptr<Toglable>{ last_spawned = new Toglable(name) });
	last_spawned->SetPosition(p.x, p.y);
	PushAction(Action::SPAWNED);
	return last_spawned;
}


Toglable* Toglable::PushToPackage(sf::Vector2f p)
{
	Toglable* last_spawned{ nullptr };
	_package.push_back(std::shared_ptr<Toglable>{ last_spawned = new Toglable() });
	last_spawned->SetPosition(p.x, p.y);
	PushAction(Action::SPAWNED);
	return last_spawned;
}


void Toglable::PackPackage()
{
	while (!_package.empty())
	{
		_spawned.push_back(_package.back());
		_package.back().reset();
		_package.pop_back();
		std::cout << "_spawned.back.use_count ::: " << _spawned.back().use_count() << std::endl;
	}
}


void Toglable::Delete(Toglable* toglable)
{
	toglable->OnDelete();
	toglable->OnClick.clear();
	toglable->OnDelete.clear();
	toglable->OnDrag.clear();
	toglable->OnDraw.clear();
	toglable->OnRotate.clear();
	toglable->OnSetPosition.clear();
	_spawned.erase(std::remove_if(std::begin(_spawned), std::end(_spawned), [toglable](auto it) { return it.get() == toglable; }));
	// ...
}


void Toglable::CollectGarbage(Toglable* toglable)
{
	if (toglable != nullptr)
	{
		toglable->OnDelete();
		toglable->OnClick.clear();
		toglable->OnDelete.clear();
		toglable->OnDrag.clear();
		toglable->OnDraw.clear();
		toglable->OnRotate.clear();
		toglable->OnSetPosition.clear();
		_garbage.push_back(toglable);
	}
}


void Toglable::ClearGarbage()
{
	while (!_garbage.empty())
	{
		auto garbage = _garbage.back();
		_garbage.pop_back();
		Delete(garbage);
		IUiItem::ClearGarbage();
		//Delete(garbage);
	}
}



 //===O===\\
// private \\
\\_________//

void Toglable::_Init()
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
				ref.OnRotate();
			}
			else if (last_action == Action::SET_ANCORE && sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			{
				auto mp = Mouse::GetMousePosition() - mouse_drag_start;
				auto orig = origin_drag_start + rotate(mp, rotation_drag_start);
				ref.SetOrigin(-orig.x,-orig.y);
			}
			else if (last_action == Action::DELETED && sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				CollectGarbage(&ref);
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


void Toglable::_Transform()
{
	for (auto& it : _v)
	{
		rotate((it.position += {_originX, _originY}) *= {_scaleX, _scaleY}, _angle) += {_positionX, _positionY};
	}
}
