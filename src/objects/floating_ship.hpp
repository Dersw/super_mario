#pragma once

#include "map_movable.hpp"
#include "movable.hpp"
#include "rect_map_movable_adapter.hpp"

namespace drw {
	// Платформа, которая сама ездит над морем туда-сюда.
	// Марио может запрыгнуть на неё и перемещаться вместе с ней.
	class FloatingShip : public RectMapMovableAdapter, public Movable {
		private:
			static constexpr float PATROL_RANGE = 6.0f;
			
			float base_x;

		public:
			FloatingShip(const Coord& top_left, const int width, const int height);

			void move_horizontally() noexcept override;
			void move_vertically() noexcept override;
			void move_map_left() noexcept override;
			void move_map_right() noexcept override;
	};
}
