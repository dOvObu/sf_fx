#include "mouse.h"


qw::Event qw::Mouse::OnMouseLeftButtonPressed ("OnMouseLeftButtonPressed ");
qw::Event qw::Mouse::OnMouseLeftButtonReleased("OnMouseLeftButtonReleased");
qw::Event qw::Mouse::OnMouseLeftButtonDown    ("OnMouseLeftButtonDown    ");

qw::Event qw::Mouse::OnMouseMiddleButtonPressed ("OnMouseMiddleButtonPressed ");
qw::Event qw::Mouse::OnMouseMiddleButtonReleased("OnMouseMiddleButtonReleased");
qw::Event qw::Mouse::OnMouseMiddleButtonDown    ("OnMouseMiddleButtonDown    ");

qw::Event qw::Mouse::OnMouseRightButtonPressed ("OnMouseRightButtonPressed ");
qw::Event qw::Mouse::OnMouseRightButtonReleased("OnMouseRightButtonReleased");
qw::Event qw::Mouse::OnMouseRightButtonDown    ("OnMouseRightButtonDown    ");

sf::RenderWindow* qw::Mouse::pw{ nullptr };
