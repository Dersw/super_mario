#include "third_level.hpp"

using drw::ThirdLevel;

ThirdLevel::ThirdLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

bool ThirdLevel::is_final() const noexcept {
	return true;
}

drw::GameLevel* ThirdLevel::get_next() {
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void ThirdLevel::init_data() {
	ui_factory->create_mario({24, 10}, 3, 3);

	// Стартовый корабль.
	ui_factory->create_ship({20, 25}, 30, 2);
	ui_factory->create_full_box({30, 17}, 5, 3);
	ui_factory->create_jumpable_enemy({40, 22}, 3, 2);

	// Первый движущийся корабль: переправа через море.
	ui_factory->create_floating_ship({55, 22}, 12, 2);

	// Небольшой промежуточный корабль с наградой.
	ui_factory->create_ship({75, 24}, 12, 2);
	ui_factory->create_box({78, 16}, 6, 3);

	// Цепочка движущихся кораблей над пропастью.
	ui_factory->create_floating_ship({92, 21}, 10, 2);
	ui_factory->create_flyable_enemy({100, 12}, 3, 2);

	ui_factory->create_floating_ship({110, 23}, 10, 2);

	ui_factory->create_floating_ship({128, 20}, 12, 2);
	ui_factory->create_flyable_enemy({134, 10}, 3, 2);

	// Корабль-остров перед финальным рывком.
	ui_factory->create_ship({148, 25}, 20, 2);
	ui_factory->create_full_box({152, 17}, 5, 3);
	ui_factory->create_enemy({160, 22}, 3, 2);

	// Последний движущийся корабль к выходу.
	ui_factory->create_floating_ship({172, 22}, 10, 2);

	// Финальный корабль-выход. Создаётся последним среди статических объектов!
	ui_factory->create_ship({190, 25}, 25, 2);
}
