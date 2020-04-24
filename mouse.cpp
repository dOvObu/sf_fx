#include "mouse.h"


qw::Event qw::Mouse::OnMouseLeftButtonPressed;
qw::Event qw::Mouse::OnMouseLeftButtonReleased;
qw::Event qw::Mouse::OnMouseLeftButtonDown;

qw::Event qw::Mouse::OnMouseMiddleButtonPressed;
qw::Event qw::Mouse::OnMouseMiddleButtonReleased;
qw::Event qw::Mouse::OnMouseMiddleButtonDown;

qw::Event qw::Mouse::OnMouseRightButtonPressed;
qw::Event qw::Mouse::OnMouseRightButtonReleased;
qw::Event qw::Mouse::OnMouseRightButtonDown;

sf::RenderWindow* qw::Mouse::pw{ nullptr };
