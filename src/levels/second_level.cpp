#include "second_level.hpp"

#include "third_level.hpp"

using drw::SecondLevel;

SecondLevel::SecondLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

drw::GameLevel* SecondLevel::get_next() {
	if (!next) {
		clear_data();
		next = new ThirdLevel(ui_factory);
	}
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void SecondLevel::init_data() {
	ui_factory->create_mario({24, 10}, 3, 3);
	
	// Стартовый корабль.
	ui_factory->create_ship({20, 25}, 40, 2);
	
	// Ящики с монетами.
	ui_factory->create_box({30, 15}, 10, 3);
	ui_factory->create_full_box({42, 15}, 5, 3);
	
	// На стартовом корабле: один враг прыгает на месте, другой бегает.
	ui_factory->create_jumpable_enemy({28, 22}, 3, 2);
	ui_factory->create_enemy({50, 22}, 3, 2);
	
	// Летающий враг над морем.
	ui_factory->create_flyable_enemy({46, 12}, 3, 2);
	
	// Широкий корабль со вторым ярусом (как в первом уровне).
	ui_factory->create_ship({60, 20}, 40, 7);
	ui_factory->create_box({62, 10}, 10, 3);
	ui_factory->create_full_box({74, 10}, 5, 3);
	ui_factory->create_box({82, 10}, 8, 3);
	ui_factory->create_coat_of_water_box({91, 13}, 5, 3);
	
	// Движущаяся платформа через пропасть: служит безопасной ступенькой.
	ui_factory->create_floating_ship({105, 19}, 10, 2);
	
	// Средний широкий корабль.
	ui_factory->create_ship({120, 25}, 40, 2);
	ui_factory->create_full_box({128, 17}, 5, 3);
	ui_factory->create_jumpable_enemy({134, 22}, 3, 2);
	ui_factory->create_enemy({152, 22}, 3, 2);
	
	// Летающие враги над средним кораблём.
	ui_factory->create_flyable_enemy({128, 12}, 3, 2);
	ui_factory->create_flyable_enemy({150, 10}, 3, 2);
	
	// Вторая движущаяся платформа.
	ui_factory->create_floating_ship({165, 19}, 10, 2);
	
	// Финальный широкий корабль-выход. Создаётся последним среди статических объектов!
	ui_factory->create_ship({180, 25}, 40, 2);
	ui_factory->create_enemy({186, 22}, 3, 2);
}
