#ifndef Common_H
#define Common_H
#include <vector>
#include <algorithm>

namespace common
{
	template <typename T>
	void remove(std::vector<T>& vec, const T elem)
	{
		vec.erase(std::remove(vec.begin(), vec.end(), elem));
	}

}
namespace colors
{

	inline SDL_Color color(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha)
	{
		SDL_Color color;
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = alpha;
		return color;
	}
	inline SDL_Color black()
	{
		return color(0, 0, 0, 0);
	}
	inline SDL_Color white()
	{
		return color(255, 255, 255, 0);
	}

}
#endif // Common_H

