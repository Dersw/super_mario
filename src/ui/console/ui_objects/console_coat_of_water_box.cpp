#include "console_coat_of_water_box.hpp"

using drw::ConsoleCoatOfWaterBox;

ConsoleCoatOfWaterBox::ConsoleCoatOfWaterBox(
	const Coord& top_left, 
	const int width, const int height,
	UIFactory* ui_factory
) : CoatOfWaterBox(top_left, width, height, ui_factory) {}

char ConsoleCoatOfWaterBox::get_brush() const noexcept {
	if (is_active_) {
		return 'W';
	} else {
		return '-';
	}
}
