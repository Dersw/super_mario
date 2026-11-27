#pragma once

#include "enemy.hpp"

namespace drw {
	// Прыгающий на месте враг. Стоит на платформе и всё время подпрыгивает,
	// не перемещаясь по горизонтали.
	class JumpableEnemy : public Enemy {
		private:
			static constexpr float JUMP_V_SPEED = -0.5f;
			
			bool is_grounded = true;

		public:
			JumpableEnemy(const Coord& top_left, const int width, const int height);

			void move_vertically() noexcept override;
			void process_vertical_static_collision(Rect* obj) noexcept override;
	};
}
