#include "qw.h"
#include <SFML/Graphics.hpp>

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

		while (pw->isOpen())
		{
			HandleEvents();
			Handle_MouseButtonDown();

			pw->clear();
			qw::Toglable::DrawSpawned();
			//button.Draw();
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
