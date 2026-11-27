#pragma once

#include "collisionable.hpp"
#include "movable.hpp"
#include "rect.hpp"
#include "rect_map_movable_adapter.hpp"
#include "speed.hpp"

namespace drw {
	// Прыгающий на месте враг. Стоит на платформе и всё время подпрыгивает,
	// не перемещаясь по горизонтали.
	class JumpableEnemy : public RectMapMovableAdapter, public Movable, public Collisionable {
		private:
			static constexpr float JUMP_V_SPEED = -0.5f;
			
			bool is_grounded = true;

		public:
			JumpableEnemy(const Coord& top_left, const int width, const int height);

			Rect get_rect() const noexcept override;
			Speed get_speed() const noexcept override;

			void move_vertically() noexcept override;

			void process_horizontal_static_collision(Rect*) noexcept override;
			void process_mario_collision(Collisionable*) noexcept override;
			void process_vertical_static_collision(Rect* obj) noexcept override;
	};
}
