#include "field_of_choice.h"

sf::RenderWindow* qw::FieldOfChoice::_pw{ nullptr };


qw::FieldOfChoice::FieldOfChoice()
{
}


qw::FieldOfChoice::~FieldOfChoice()
{
}


void qw::FieldOfChoice::Init(sf::RenderWindow& w)
{
	_pw = &w;
}
