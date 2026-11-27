#pragma once

#include "coat_of_water.hpp"
#include "console_ui_obj_rect_adapter.hpp"

namespace drw {
	class ConsoleCoatOfWater : public CoatOfWater, public ConsoleUIObjectRectAdapter {
		public:
			ConsoleCoatOfWater(const Coord& top_left, const int width, const int height);

			char get_brush() const noexcept override;
	};
}
