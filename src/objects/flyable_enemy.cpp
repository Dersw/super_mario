#include "flyable_enemy.hpp"

#include "map_movable.hpp"

using drw::FlyableEnemy;

FlyableEnemy::FlyableEnemy(const Coord& top_left, const int width, const int height) 
	: RectMapMovableAdapter(top_left, width, height), 
		base_x(top_left.x), base_y(top_left.y) {
	hspeed = 0.2;
	vspeed = -0.15;
}

drw::Rect FlyableEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

drw::Speed FlyableEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void FlyableEnemy::move_horizontally() noexcept {
	if (top_left.x <= base_x - PATROL_RANGE) {
		hspeed = 0.2;
	} else if (top_left.x >= base_x + PATROL_RANGE) {
		hspeed = -0.2;
	}
	top_left.x += hspeed;
}

void FlyableEnemy::move_vertically() noexcept {
	if (top_left.y <= base_y - FLIGHT_RANGE) {
		vspeed = 0.15;
	} else if (top_left.y >= base_y + FLIGHT_RANGE) {
		vspeed = -0.15;
	}
	top_left.y += vspeed;
}

void FlyableEnemy::move_map_left() noexcept {
	top_left.x -= MapMovable::MAP_STEP;
	base_x -= MapMovable::MAP_STEP;
}

void FlyableEnemy::move_map_right() noexcept {
	top_left.x += MapMovable::MAP_STEP;
	base_x += MapMovable::MAP_STEP;
}

void FlyableEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
	hspeed = -hspeed;
	move_horizontally();
}

void FlyableEnemy::process_mario_collision(Collisionable* mario) noexcept {
	if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
		kill();
	} else {
		mario->kill();
	}
}

void FlyableEnemy::process_vertical_static_collision(Rect* obj) noexcept {
	// Летающий враг игнорирует гравитацию и платформы - он парит в воздухе.
}
