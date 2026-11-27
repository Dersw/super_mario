#include "coat_of_water_box.hpp"

using drw::CoatOfWaterBox;

CoatOfWaterBox::CoatOfWaterBox(
	const Coord& top_left, 
	const int width, const int height,
	UIFactory* ui_factory
) : Box(top_left, width, height), ui_factory(ui_factory) {}

drw::Rect CoatOfWaterBox::get_rect() const noexcept {
	return {top_left, width, height};
}

drw::Speed CoatOfWaterBox::get_speed() const noexcept {
	return {0, 0};
}

void CoatOfWaterBox::process_horizontal_static_collision(Rect* obj) noexcept {}

void CoatOfWaterBox::process_mario_collision(Collisionable* mario) noexcept {
	if (mario->get_speed().v < 0) {
		kill();
		ui_factory->create_coat_of_water({top_left.x, top_left.y - 3}, 3, 2);
	}
}

void CoatOfWaterBox::process_vertical_static_collision(Rect* obj) noexcept {}
