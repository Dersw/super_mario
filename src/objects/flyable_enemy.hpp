#pragma once

#include "collisionable.hpp"
#include "movable.hpp"
#include "rect.hpp"
#include "rect_map_movable_adapter.hpp"
#include "speed.hpp"

namespace drw {
	// Летающий враг. Не подчиняется гравитации: парит в воздухе,
	// покачиваясь вверх-вниз и патрулируя в пределах своего участка.
	class FlyableEnemy : public RectMapMovableAdapter, public Movable, public Collisionable {
		private:
			static constexpr float PATROL_RANGE = 8.0f;
			static constexpr float FLIGHT_RANGE = 3.0f;
			
			float base_x;
			float base_y;

		public:
			FlyableEnemy(const Coord& top_left, const int width, const int height);

			Rect get_rect() const noexcept override;
			Speed get_speed() const noexcept override;

			void move_horizontally() noexcept override;
			void move_vertically() noexcept override;
			void move_map_left() noexcept override;
			void move_map_right() noexcept override;

			void process_horizontal_static_collision(Rect*) noexcept override;
			void process_mario_collision(Collisionable*) noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;
	};
}
