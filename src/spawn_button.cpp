#include "extentions.h"
#include "spawn_button.h"
#include "sfml_extentions.h"


sf::RenderWindow* qw::SpawnButton::pw{ nullptr };



qw::SpawnButton::SpawnButton()
{	_Init(); }



qw::SpawnButton::SpawnButton(char const* name)
{	_Init(name); }



void qw::SpawnButton::_Init(std::string name)
{
	auto& ref = *this;

	Mouse::OnMouseLeftButtonPressed[this] = [&ref, name]() {
		auto mp = Mouse::GetMousePosition();
		if (ref.Contains(mp))
		{
			std::cout << "spawn" << std::endl;
			Toglable* spawned = (name.empty()) ? Toglable::Spawn(mp) : Toglable::Spawn(name.c_str(), mp);
			spawned->SetScale(100.f, 100.f);
			spawned->SelectToDrag();
		}
	};
	std::cout << "new SpawnButton\n";
}



qw::SpawnButton::~SpawnButton()
{	Mouse::OnMouseLeftButtonPressed -= this; }



void qw::SpawnButton::SetScale(float x, float y)
{
	_scaleX = x;
	_scaleY = y;
}



void qw::SpawnButton::SetPosition(float x, float y)
{
	_positionX = x;
	_positionY = y;
}



void qw::SpawnButton::Draw()
{
	if (_active)
	{
		_v[0].position = { -1.f,-1.f }, _v[1].position = {  1.f,-1.f };
		_v[2].position = {  1.f, 1.f }, _v[3].position = { -1.f, 1.f };
		Transform();
		pw->draw(_v, 4, sf::Quads);
	}
}



bool qw::SpawnButton::Contains(sf::Vector2f const& p)
{	return is_inside(_v, 4, p); }



void qw::SpawnButton::Init(sf::RenderWindow& rw)
{	pw = &rw; }



void qw::SpawnButton::Transform()
{
	for (auto& it : _v)
	{
		rotate(it.position *= {_scaleX, _scaleY}, _angle) += {_positionX, _positionY};
	}
}
