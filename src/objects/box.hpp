#pragma once

#include "rect_map_movable_adapter.hpp"

namespace drw {
	class Box : public RectMapMovableAdapter {
		public:
			Box(
				const Coord& top_left, const int width, const int height
			) : RectMapMovableAdapter(top_left, width, height) {}
	};
}
