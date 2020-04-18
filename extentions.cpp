#include "extentions.h"


Orientation orientation(std::pair<sf::Vector2f, sf::Vector2f> line, sf::Vector2f point)
{
	float const val = (line.second.y - line.first.y) * (point.x - line.second.x) -
		(line.second.x - line.first.x) * (point.y - line.second.y);

	if (0.01f >= abs(val)) return Orientation::COLINEAR;
	return (val > 0.f) ? Orientation::CLOCKWISE : Orientation::COUNTER_CLOCKWISE;
}


bool are_intersects(std::pair<sf::Vector2f, sf::Vector2f> line1, std::pair<sf::Vector2f, sf::Vector2f> line2)
{
	auto o1 = orientation(line1, line2.first);
	auto o2 = orientation(line1, line2.second);
	auto o3 = orientation(line2, line1.first);
	auto o4 = orientation(line2, line1.second);

	// General case
	return (o1 != o2 && o3 != o4)
		// Special Cases
		|| (o1 == Orientation::COLINEAR && is_in_aabb(line1, line2.first))
		|| (o2 == Orientation::COLINEAR && is_in_aabb(line1, line2.second))
		|| (o3 == Orientation::COLINEAR && is_in_aabb(line2, line1.first))
		|| (o4 == Orientation::COLINEAR && is_in_aabb(line2, line1.second));
}


bool is_inside(sf::Vertex polygon[], int n, sf::Vector2f p)
{
	sf::Vector2f extreme = { 1.e+20f, p.y };

	int count_intersections = 0; // p---extreme, with sides of polygon
	int i = 0;
	do
	{
		int next = fract(i + 1, 0, n);

		if (are_intersects({ polygon[i].position, polygon[next].position }, { p, extreme }))
		{
			// If the point 'p' is colinear with line segment 'i-next', then check if it lies on segment
			if (orientation({ polygon[i].position, polygon[next].position }, p) == Orientation::COLINEAR)
			{
				return is_in_aabb({ polygon[i].position, polygon[next].position }, p);
			}

			count_intersections++;
		}
		i = next;
	} while (i != 0);

	return is_odd(count_intersections);
}
