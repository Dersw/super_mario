#pragma once

#include "rect.hpp"
#include "speed.hpp"

namespace drw {
	// Абстракция платформы, которая движется самостоятельно.
	// Марио может запрыгнуть на такую платформу и перемещаться вместе с ней.
	class MovingPlatform : virtual public Rect {
		public:
			virtual Speed get_speed() const noexcept = 0;
	};
}
