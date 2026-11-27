#include "jumpable_enemy.hpp"

using drw::JumpableEnemy;

JumpableEnemy::JumpableEnemy(const Coord& top_left, const int width, const int height) 
	: RectMapMovableAdapter(top_left, width, height) {
	// Враг прыгает на месте, поэтому по горизонтали не двигается.
	vspeed = 0;
	hspeed = 0;
}

drw::Rect JumpableEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

drw::Speed JumpableEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void JumpableEnemy::move_vertically() noexcept {
	// Прыгаем только оттолкнувшись от платформы, а не в верхней точке полёта.
	if (is_grounded) {
		is_grounded = false;
		vspeed = JUMP_V_SPEED;
	}
	Movable::move_vertically();
}

void JumpableEnemy::process_horizontal_static_collision(Rect* obj) noexcept {}

void JumpableEnemy::process_mario_collision(Collisionable* mario) noexcept {
	if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
		kill();
	} else {
		mario->kill();
	}
}

void JumpableEnemy::process_vertical_static_collision(Rect* obj) noexcept {
	// Особенность модели вертикального передвижения в игре.
	if (vspeed > 0) {
		top_left.y -= vspeed;
		vspeed = 0;
		// Снова оказались на платформе - готовы к следующему прыжку.
		is_grounded = true;
	} else if (vspeed < 0) {
		top_left.y -= vspeed;
		vspeed = 0;
	}
}
