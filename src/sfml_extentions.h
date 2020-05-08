#ifndef INCLUDED_SFML_EXTENTIONS_H
#define INCLUDED_SFML_EXTENTIONS_H
#include <SFML/Graphics.hpp>

// SFML extentions
inline float length(const sf::Vector2f& v) { return sqrtf(v.x * v.x + v.y * v.y); }
inline sf::Vector2f& operator*=(sf::Vector2f& a, sf::Vector2f const& b) { a.x *= b.x; a.y *= b.y; return a; }
inline sf::Vector2f& operator+=(sf::Vector2f& a, sf::Vector2f const& b) { a.x += b.x; a.y += b.y; return a; }
inline sf::Vector2f& rotate(sf::Vector2f& a, float ang) { ang += atan2f(a.y, a.x); auto const l = length(a); a.x = l * cosf(ang); a.y = l * sinf(ang); return a; }
//_SFML extentions_

#endif // !INCLUDED_SFML_EXTENTIONS_H

