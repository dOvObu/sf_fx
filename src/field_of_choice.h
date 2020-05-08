#ifndef INCLUDED_FIELD_OF_CHOICE_H
#define INCLUDED_FIELD_OF_CHOICE_H
#include <SFML/Graphics/RenderWindow.hpp>

namespace qw
{
	struct FieldOfChoice
	{
		FieldOfChoice();
		~FieldOfChoice();
		static void Init(sf::RenderWindow& w);
	private:
		static sf::RenderWindow* _pw;
	};
}


#endif // !INCLUDED_FIELD_OF_CHOICE_H
