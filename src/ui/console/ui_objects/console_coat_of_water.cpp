#include "console_coat_of_water.hpp"

using drw::ConsoleCoatOfWater;

ConsoleCoatOfWater::ConsoleCoatOfWater(
	const Coord& top_left, const int width, const int height
) : CoatOfWater(top_left, width, height) {}

char ConsoleCoatOfWater::get_brush() const noexcept {
	return 'w';
}
