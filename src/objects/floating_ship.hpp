#pragma once

#include "map_movable.hpp"
#include "moving_platform.hpp"
#include "movable.hpp"
#include "rect_map_movable_adapter.hpp"

namespace drw {
	// Платформа, которая сама ездит над морем туда-сюда.
	// Марио может запрыгнуть на неё и прокатиться.
	class FloatingShip : public RectMapMovableAdapter, public Movable, public MovingPlatform {
		private:
			static constexpr float PATROL_RANGE = 6.0f;
			
			float base_x;

		public:
			FloatingShip(const Coord& top_left, const int width, const int height);

			Rect get_rect() const noexcept;
			Speed get_speed() const noexcept override;

			void move_horizontally() noexcept override;
			void move_vertically() noexcept override;
			void move_map_left() noexcept override;
			void move_map_right() noexcept override;
	};
}
