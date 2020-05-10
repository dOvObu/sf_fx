#include "qw.h"
#include <SFML/Graphics.hpp>
#include "ui/ui_field.h"
#include "ui/ui_label.h"

namespace qw
{
	sf::RenderWindow* App::pw{ nullptr };

	bool App::is_left_mouse_down{ false };
	bool App::is_middle_mouse_down{ false };
	bool App::is_right_mouse_down{ false };



	void App::Init(sf::RenderWindow& w)
	{
		pw = &w;
	}


	void App::MainLoop()
	{
		//qw::SpawnButton button("example");
		//button.SetPosition(400.f, 400.f);
		//button.SetScale(100.f, 50.f);
		UiField item({ 200,200 }, { 300,200 }, { 100, 150, 200 },
			{
				new UiField({}, { 250,150 }, { 20, 70, 120 },
					{
						new UiLabel(L"\nТестовый кек", "JB_Mono")
					,
						new UiField({}, { 17,17 }, { 120, 70, 120 },
							{
								(new UiLabel("Testing test test test testing test test test\nTesting test testing test testing test test test testing test...", "JB_Mono"))
								-> SetPosition(sf::Vector2f(-8.5f,-8.5f))
								-> SetSize({ 70.f,37.f })
								-> SetRotation(3.1415926535858f/2.f)
							})
					}),
			},
			true);

		//Toglable::Spawn("example", { 300,300 })->SetScale(150,150);

		while (pw->isOpen())
		{
			HandleEvents();
			Handle_MouseButtonDown();
			Toglable::ClearGarbage();

			pw->clear();
			Toglable::DrawSpawned();
			pw->display();
		}
	}


	void App::HandleEvents()
	{
		sf::Event e;
		while (pw->pollEvent(e))
		{
			if (e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				pw->close();
			}
			else if (e.type == sf::Event::MouseButtonPressed)
			{
				Handle_MouseButtonPressed(e.mouseButton.button);
			}
			else if (e.type == sf::Event::MouseButtonReleased)
			{
				Handle_MouseButtonReleased(e.mouseButton.button);
			}
		}
	}


	void App::Handle_MouseButtonPressed(sf::Mouse::Button const& btn)
	{
		if (btn == sf::Mouse::Button::Left)
		{
			qw::Mouse::OnMouseLeftButtonPressed();
			is_left_mouse_down = true;
		}
		else if (btn == sf::Mouse::Button::Middle)
		{
			qw::Mouse::OnMouseMiddleButtonPressed();
			is_middle_mouse_down = true;
		}
		else if (btn == sf::Mouse::Button::Right)
		{
			qw::Mouse::OnMouseRightButtonPressed();
			is_right_mouse_down = true;
		}
	}


	void App::Handle_MouseButtonReleased(sf::Mouse::Button const& btn)
	{
		if (btn == sf::Mouse::Button::Left)
		{
			qw::Mouse::OnMouseLeftButtonReleased();
			is_left_mouse_down = false;
		}
		else if (btn == sf::Mouse::Button::Middle)
		{
			qw::Mouse::OnMouseMiddleButtonReleased();
			is_middle_mouse_down = false;
		}
		else if (btn == sf::Mouse::Button::Right)
		{
			qw::Mouse::OnMouseRightButtonReleased();
			is_right_mouse_down = false;
		}
	}


	void App::Handle_MouseButtonDown()
	{
		if (is_left_mouse_down)
		{
			qw::Mouse::OnMouseLeftButtonDown();
		}

		if (is_middle_mouse_down)
		{
			qw::Mouse::OnMouseMiddleButtonDown();
		}

		if (is_right_mouse_down)
		{
			qw::Mouse::OnMouseRightButtonDown();
		}
	}

}
