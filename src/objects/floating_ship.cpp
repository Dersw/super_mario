#include "floating_ship.hpp"

using drw::FloatingShip;

FloatingShip::FloatingShip(const Coord& top_left, const int width, const int height) 
	: RectMapMovableAdapter(top_left, width, height), 
		base_x(top_left.x) {
	vspeed = 0;
	hspeed = 0.2f;
}

void FloatingShip::move_horizontally() noexcept {
	// Катаемся вправо-влево в пределах своего участка.
	if (top_left.x <= base_x - PATROL_RANGE) {
		top_left.x = base_x - PATROL_RANGE;
		hspeed = 0.2f;
	} else if (top_left.x >= base_x + PATROL_RANGE) {
		top_left.x = base_x + PATROL_RANGE;
		hspeed = -0.2f;
	}
	top_left.x += hspeed;
}

void FloatingShip::move_vertically() noexcept {
	// Плавающая платформа держится на уровне воды и не падает под действием гравитации.
}

void FloatingShip::move_map_left() noexcept {
	top_left.x -= MapMovable::MAP_STEP;
	base_x -= MapMovable::MAP_STEP;
}

void FloatingShip::move_map_right() noexcept {
	top_left.x += MapMovable::MAP_STEP;
	base_x += MapMovable::MAP_STEP;
}
