#ifndef INCLUDED_EXTENTIONS_H
#define INCLUDED_EXTENTIONS_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <map>

// CPP extentions

// str
template<char delimiter> class __word_delimited_by : public std::string {};
template<char ch> inline std::vector<std::string> split(std::string s) { std::istringstream iss{ s.c_str() }; return std::vector<std::string> {(std::istream_iterator<__word_delimited_by<ch>>(iss)), std::istream_iterator<__word_delimited_by<ch>>()}; }
template<typename T> inline std::string typename_of(T* p) { return split<' '>(typeid(T).name())[1]; }
template<typename T> inline std::string typename_of() { return split<' '>(typeid(T).name())[1]; }

// len
template<typename T> inline size_t len(const T& i) { return 1; }
template<typename T> inline size_t len(const std::vector<T>& v) { return v.size(); }
template<typename T, size_t N> inline size_t len(T(&A)[N]) { return N; }
template<typename T, typename Y> inline size_t len(const std::map<T, Y>& m) { return m.size(); }
inline size_t len(const std::string& s) { return s.size(); }
inline size_t len(const std::wstring& ws) { return ws.size(); }

// push
template<typename T> inline void operator+=(std::vector<T>& l, T& r) { l.push_back(r); }
template<typename T, typename Y> inline void operator+=(std::map<T, Y>& l, const std::pair<T, Y>& r) { l.emplace(r); }

// print
template<class T> inline void print(const T& val) { std::cout << val.to_string() << '\n'; } // std::string to_string()
template<typename T> inline void print(const T*& val) { std::cout << val << '\n'; }
template<> inline void print(const std::string& val) { std::cout << val << '\n'; }
template<> inline void print(const double& val) { std::cout << val << '\n'; }
template<> inline void print(const size_t& val) { std::cout << val << '\n'; }
template<> inline void print(const float& val) { std::cout << val << '\n'; }
template<> inline void print(const char& val) { std::cout << val << '\n'; }
template<> inline void print(const int& val) { std::cout << val << '\n'; }
template<typename T, typename Y> inline void print(const std::pair<T, Y>& pr) { std::cout << pr.first << " : " << pr.second << '\n'; }
template<typename T> inline void print(const std::vector<T>& v) { std::cout << '['; bool first{ true }; for (auto& it : v) first ? first = false, std::cout << it : std::cout << ", " << it; std::cout << "]\n"; }
template<typename T, typename Y> inline void print(const std::map<T, Y>& m) { std::cout << '{'; bool first{ true }; for (auto& it : m) first ? first = false, std::cout << it.first << " : " << it.second : std::cout << ", " << it.first << " : " << it.second; std::cout << "}\n"; }
template<size_t N> inline void print(std::string(&A)[N]) { std::cout << '['; bool first{ true }; for (size_t idx = 0; N > idx; ++idx) first ? first = false, std::cout << A[idx] : std::cout << ", " << A[idx]; std::cout << "]\n"; }
template<size_t N> inline void print(const char(&A)[N]) { std::cout << '['; bool first{ true }; for (size_t idx = 0; N > idx; ++idx) first ? first = false, std::cout << A[idx] : std::cout << ", " << A[idx]; std::cout << "]\n"; }
template<size_t N> inline void print(double(&A)[N]) { std::cout << '['; bool first{ true }; for (size_t idx = 0; N > idx; ++idx) first ? first = false, std::cout << A[idx] : std::cout << ", " << A[idx]; std::cout << "]\n"; }
template<size_t N> inline void print(size_t(&A)[N]) { std::cout << '['; bool first{ true }; for (size_t idx = 0; N > idx; ++idx) first ? first = false, std::cout << A[idx] : std::cout << ", " << A[idx]; std::cout << "]\n"; }
template<size_t N> inline void print(float(&A)[N]) { std::cout << '['; bool first{ true }; for (size_t idx = 0; N > idx; ++idx) first ? first = false, std::cout << A[idx] : std::cout << ", " << A[idx]; std::cout << "]\n"; }
template<size_t N> inline void print(bool(&A)[N]) { std::cout << '['; bool first{ true }; for (size_t idx = 0; N > idx; ++idx) first ? first = false, std::cout << (A[idx]) : std::cout << ", " << (A[idx]); std::cout << "]\n"; }
template<size_t N> inline void print(int(&A)[N]) { std::cout << '['; bool first{ true }; for (size_t idx = 0; N > idx; ++idx) first ? first = false, std::cout << A[idx] : std::cout << ", " << A[idx]; std::cout << "]\n"; }
template<typename T, size_t N> inline void print(T(&A)[N]) { std::cout << '['; bool first{ true }; for (size_t idx = 0; N > idx; ++idx) first ? first = false, std::cout << A[idx].to_string() : std::cout << ", " << A[idx].to_string(); std::cout << "]\n"; }

//~glsl math
inline bool is_odd(const int& c) { return c & 1; }
inline int fract(const int v, const int min, const int max) { return (v + min) % max; }

// geometry
enum class Orientation { COLINEAR, CLOCKWISE, COUNTER_CLOCKWISE };
inline bool is_in_aabb(std::pair<sf::Vector2f, sf::Vector2f> aabb, sf::Vector2f p) { return (p.x <= std::max(aabb.first.x, aabb.second.x) && p.x >= std::min(aabb.first.x, aabb.second.x) && p.y <= std::max(aabb.first.y, aabb.second.y) && p.y >= std::min(aabb.first.y, aabb.second.y)); }
Orientation orientation(std::pair<sf::Vector2f, sf::Vector2f> line, sf::Vector2f point);
bool are_intersects(std::pair<sf::Vector2f, sf::Vector2f> line1, std::pair<sf::Vector2f, sf::Vector2f> line2);
bool is_inside(sf::Vertex polygon[], int n, sf::Vector2f p);

//_CPP extentions_


#endif // !INCLUDED_EXTENTIONS_H
