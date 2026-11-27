#pragma once

namespace drw {
	class GameMap {
		public:
			static constexpr int WATER_HEIGHT = 3;

		protected:
			const int height;
			const int width;
			
		protected:
			GameMap(const int height, const int width);
		
		public:
			int get_water_level() const noexcept;
			bool is_below_map(const int y) const noexcept;
			bool is_on_map(const int x, const int y) const noexcept;
			
			virtual void clear() noexcept = 0;
			virtual void refresh() noexcept = 0;
			virtual void remove_objs() = 0;
			virtual void show() const noexcept = 0;
	};
}
