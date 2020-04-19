#include "spawn_button.h"
#include "mouse.h"
#define INIT(Name) qw :: Name :: Init(w)

#define QW_INIT \
	INIT(SpawnButton); INIT(Toglable); INIT(Mouse);


int main()
{
	sf::RenderWindow w({ 800,600 }, "T_T");
	QW_INIT

	qw::SpawnButton button;
	button.SetPosition(400.f, 400.f);
	button.SetScale(100.f, 50.f);
	bool is_mouse_down{ false };

	while (w.isOpen())
	{
		sf::Event e;
		while (w.pollEvent(e))
		{
			if (e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) w.close();
			else if (e.type == sf::Event::MouseButtonPressed)
			{
				if (e.mouseButton.button == sf::Mouse::Button::Left) qw::Mouse::OnMouseLeftButtonPressed();
				is_mouse_down = true;
			}
			else if (e.type == sf::Event::MouseButtonReleased)
			{
				if (e.mouseButton.button == sf::Mouse::Button::Left) qw::Mouse::OnMouseLeftButtonReleased();
				is_mouse_down = false;
			}
		}
		if (is_mouse_down) qw::Mouse::OnMouseLeftButtonDown();
		

		w.clear();
		qw::Toglable::DrawSpawned();
		button.Draw();
		w.display();
	}
}
