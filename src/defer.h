#pragma once
#pragma clang diagnostic ignored "-Wc2y-extensions"

template <typename F>
struct Defer {
	Defer(F func) : f(func) {}
	~Defer() { f(); }

private:
	F f;
};

#define CONCAT_DETAIL(x, y) x##y
#define CONCAT(x, y) CONCAT_DETAIL(x, y) //NOLINT

#define DEFER(block) auto CONCAT(_defer_, __COUNTER__) = Defer([&]() block); //NOLINT
