#include "coat_of_water.hpp"

#include "mario.hpp"

using drw::CoatOfWater;

CoatOfWater::CoatOfWater(const Coord& top_left, const int width, const int height) 
	: RectMapMovableAdapter(top_left, width, height) {
	vspeed = 0;
	hspeed = 0;
}

drw::Rect CoatOfWater::get_rect() const noexcept {
	return {top_left, width, height};
}

drw::Speed CoatOfWater::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void CoatOfWater::process_horizontal_static_collision(Rect* obj) noexcept {
	hspeed = -hspeed;
	move_horizontally();
}

void CoatOfWater::process_mario_collision(Collisionable* obj) noexcept {
	if (Mario* mario = dynamic_cast<Mario*>(obj)) {
		mario->set_coat_of_water(true);
	}
	kill();
}

void CoatOfWater::process_vertical_static_collision(Rect* obj) noexcept {
	if (vspeed > 0) {
		top_left.y -= vspeed;
		vspeed = 0;
	}
}
