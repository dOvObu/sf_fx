#ifndef INCLUDED_EVENT_H
#define INCLUDED_EVENT_H
#include <functional>
#include <vector>
#include <string>
#include <map>

namespace qw
{
	using Func = std::function<void(void)>;
	struct Event
	{
		void operator()() { for (auto& cb : m) cb.second(); for (auto& cb : v) cb(); }
		Event& operator-=(void* key) { m.erase(key); return *this; }
		Func& operator[](void* key) { return m[key]; }
		Event& operator+=(Func const& f) { v.push_back(f); return *this; }
		Event& operator+=(std::pair<void*, Func> const& pr) { m.insert(pr); return *this; }
		std::string to_string() { return "qw::Event { m.size() -> " + std::to_string(m.size()) + ", v.size() -> " + std::to_string(v.size()) + " }"; }
	private:
		std::map<void*, Func> m;
		std::vector<Func> v;
	};
}


#endif // !INCLUDED_EVENT_H

