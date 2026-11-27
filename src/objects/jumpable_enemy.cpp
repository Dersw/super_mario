#include "jumpable_enemy.hpp"

using drw::JumpableEnemy;

JumpableEnemy::JumpableEnemy(const Coord& top_left, const int width, const int height) 
	: Enemy(top_left, width, height) {
	// Враг прыгает на месте, поэтому по горизонтали не двигается.
	hspeed = 0;
}

void JumpableEnemy::move_vertically() noexcept {
	// Прыгаем только оттолкнувшись от платформы, а не в верхней точке полёта.
	if (is_grounded) {
		is_grounded = false;
		vspeed = JUMP_V_SPEED;
	}
	Movable::move_vertically();
}

void JumpableEnemy::process_vertical_static_collision(Rect* obj) noexcept {
	Enemy::process_vertical_static_collision(obj);
	// Снова оказались на платформе - готовы к следующему прыжку.
	if (vspeed == 0) {
		is_grounded = true;
	}
}
