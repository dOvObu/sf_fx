#include "toglable.h"
#include "mouse.h"



int main()
{
	sf::RenderWindow w({ 800,600 }, "T_T");
	qw::Mouse::Init(w);
	qw::Toglable::Init(w);
	qw::Toglable s;
	s.SetScale(100.f, 100.f);
	bool is_mouse_down{ false };

	while (w.isOpen())
	{
		sf::Event e;
		while (w.pollEvent(e))
		{
			if (e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) w.close();
			else if (e.type == sf::Event::MouseButtonPressed) { qw::Mouse::OnMousePressed(); is_mouse_down = true; }
			else if (e.type == sf::Event::MouseButtonReleased) { qw::Mouse::OnMouseReleased(); is_mouse_down = false; }
		}
		if (is_mouse_down) qw::Mouse::OnMouseDown();

		w.clear();
		s.Draw();
		w.display();
	}
}
