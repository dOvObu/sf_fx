#include "qw.h"
#include "textures_provider.h"


struct Textures
{
	static sf::Texture* textures;
	static size_t size;
};
sf::Texture* Textures::textures{ nullptr };
size_t Textures::size{ 0 };


int main()
{
	TexturesProvider::LoadTextures("resources/img");
	sf::RenderWindow w{{ 800,600 }, "T_T"};
	w.setFramerateLimit(60);
	QW_INIT;

	qw::SpawnButton button;
	button.SetPosition(400.f, 400.f);
	button.SetScale(100.f, 50.f);
	bool is_left_mouse_down{ false };
	bool is_middle_mouse_down{ false };
	bool is_right_mouse_down{ false };

	while (w.isOpen())
	{
		sf::Event e;
		while (w.pollEvent(e))
		{
			if (e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) w.close();
			else if (e.type == sf::Event::MouseButtonPressed)
			{
				if (e.mouseButton.button == sf::Mouse::Button::Left) { qw::Mouse::OnMouseLeftButtonPressed(); is_left_mouse_down = true; }
				else if (e.mouseButton.button == sf::Mouse::Button::Middle) { qw::Mouse::OnMouseMiddleButtonPressed(); is_middle_mouse_down = true; }
				else if (e.mouseButton.button == sf::Mouse::Button::Right) { qw::Mouse::OnMouseRightButtonPressed(); is_right_mouse_down = true; }
			}
			else if (e.type == sf::Event::MouseButtonReleased)
			{
				if (e.mouseButton.button == sf::Mouse::Button::Left) { qw::Mouse::OnMouseLeftButtonReleased(); is_left_mouse_down = false; }
				else if (e.mouseButton.button == sf::Mouse::Button::Middle) { qw::Mouse::OnMouseMiddleButtonReleased(); is_middle_mouse_down = false; }
				else if (e.mouseButton.button == sf::Mouse::Button::Right) { qw::Mouse::OnMouseRightButtonReleased(); is_right_mouse_down = false; }
			}
		}
		if (is_left_mouse_down) qw::Mouse::OnMouseLeftButtonDown();
		if (is_middle_mouse_down) qw::Mouse::OnMouseMiddleButtonDown();
		if (is_right_mouse_down) qw::Mouse::OnMouseRightButtonDown();


		w.clear();
		qw::Toglable::DrawSpawned();
		button.Draw();
		w.display();
	}
}
