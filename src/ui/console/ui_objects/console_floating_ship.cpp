#include "console_floating_ship.hpp"

using drw::ConsoleFloatingShip;

ConsoleFloatingShip::ConsoleFloatingShip(
	const Coord& top_left, const int width, const int height
) : FloatingShip(top_left, width, height) {}

char ConsoleFloatingShip::get_brush() const noexcept {
	return '#';
}
