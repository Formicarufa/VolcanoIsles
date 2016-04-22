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
	const double PI = 3.14159265359;
	double inline rad_to_deg(double rad)
	{
		return rad / PI * 180;
	}
	//Deletes the element with index "at", does not retain the order of the elements.
	template<typename T>
	void vector_remove(std::vector<T>& vec, std::size_t at)
	{
		vec.at(at) = vec.back();
		vec.pop_back();
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
	inline SDL_Color light_grey()
	{
		return color(200, 200, 200, 255);
	}

}
#endif // Common_H

