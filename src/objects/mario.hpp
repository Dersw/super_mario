#pragma once

#include "collisionable.hpp"
#include "movable.hpp"
#include "rect.hpp"
#include "speed.hpp"

namespace drw {
	class Mario : public Movable, public Collisionable {
		private:
			bool has_coat_of_water_ = false;

		public:
			Mario(const Coord& top_left, const int width, const int height);

			Rect get_rect() const noexcept override;
			Speed get_speed() const noexcept override;

			bool has_coat_of_water() const noexcept;
			void set_coat_of_water(const bool value) noexcept;
			
			void move_map_left() noexcept;
			void move_map_right() noexcept;

			void process_horizontal_static_collision(Rect*) noexcept override;
			void process_mario_collision(Collisionable*) noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;
	};
}
