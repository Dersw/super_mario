#pragma once

#include "coat_of_water_box.hpp"
#include "console_ui_obj_rect_adapter.hpp"

namespace drw {
	class ConsoleCoatOfWaterBox : public CoatOfWaterBox, public ConsoleUIObjectRectAdapter {
		public:
			ConsoleCoatOfWaterBox(
				const Coord& top_left, 
				const int width, const int height,
				UIFactory* ui_factory
			);
			
			char get_brush() const noexcept override;
	};
}
