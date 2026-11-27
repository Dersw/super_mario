/**
	Игровой цикл - это обощённое представление потока событий, происходящих в игре.

	Игровой цикл:
		1. Установка параметров игры
		2. Получение пользовательского ввода
		3. Обновление внутреннего состояния игры
		4. Обновление изображения на экране
		5. Проверка того, не окончена ли игра

		*** Если игра не окончена, то возвращаемся в пункт № 2.

		6. Завершение
		
	- Какие архитектурные принципы применены при реализации игры?
	
	- На основе какого приципа ООП построен алгоритм игры?
	- Какими элементами языка С++ реализуется этот принцип?
	- Приведите примеры кода, отображающие этот прицип.
*/


//TODO
/**
 * 1) Наследование прыгающего и летающего врага от модели (не Enemy)
 * 2) Марио двигается вместе с двигающейся платформой если на ней
 * 3) Удалить MovingPlatform
 * 4) Поднять двигающиеся платформы 2 уровня на 2-3 единицы
 * 5) Добавить коробку с плащом-воды(coat_of_water), подобрав который он может ходить по воде
 *
*/
#include <cstdio>
#include <thread>

#include "console_ui_factory.hpp"
#include "first_level.hpp"
#include "game.hpp"
#include "game_level.hpp"
#include "game_map.hpp"
#include "keyboard.hpp"
#include "mario.hpp"
#include "os_control_settings.hpp"
#include "ui_factory.hpp"

#ifdef WINDOWS_CONSOLE
	#include "windows_control_settings.hpp"
	#include "windows_keyboard.hpp"
#elif defined(LINUX_CONSOLE)
	#include "linux_control_settings.hpp"
	#include "linux_keyboard.hpp"
	#include "ncurses.h"
#endif

int main() {
	// 1. Установка параметров игры
	using namespace std::chrono_literals;
	
	const int map_height = 30;
	const int map_weight = 200;
	auto frame_delay = std::chrono::milliseconds(0);
	
	drw::OSControlSettings* control_settings = nullptr;
	drw::KeyBoard* keyboard = nullptr;
	#ifdef WINDOWS_CONSOLE
		control_settings = new drw::WindowsControlSettings();
		keyboard = new drw::WindowsKeyBoard();
		frame_delay = std::chrono::milliseconds(10);
	#elif defined(LINUX_CONSOLE)
		control_settings = new drw::LinuxControlSettings(map_height, map_weight);
		keyboard = new drw::LinuxKeyboard();
		frame_delay = std::chrono::milliseconds(50);
	#endif
	
	control_settings->init();
	keyboard->on();
	
	drw::Game game;
	drw::UIFactory* ui_factory = new drw::ConsoleUIFactory(&game);
	drw::GameMap* game_map = ui_factory->get_game_map(map_height, map_weight);
	drw::GameLevel* game_level = new drw::FirstLevel(ui_factory);
	drw::Mario* mario = ui_factory->get_mario();
	
	drw::UserInput user_input;
	bool is_victory = false;
	do {
		// 2. Получение пользовательского ввода	
		user_input = keyboard->get_user_input();
		switch (user_input) {
			case drw::UserInput::MAP_LEFT:
				mario->move_map_left();
				if (!game.check_static_collisions(mario)) {
					game.move_map_left();
				}
				mario->move_map_right();
				break;
			case drw::UserInput::MAP_RIGHT:
				mario->move_map_right();
				if (!game.check_static_collisions(mario)) {
					game.move_map_right();
				}
				mario->move_map_left();
				break;
			case drw::UserInput::MARIO_JUMP:
				mario->jump();
				break;
			case drw::UserInput::EXIT:
				game.finish();
				break;
		}


		
		// 3. Обновление внутреннего состояния игры

		//TODO
		/**
		 * game.check_moving_platform
		 * game.check_coat_of_water
		 */

		game.move_objs_horizontally();
		game.carry_mario();
		game.check_horizontally_static_collisions();
		
		game.move_objs_vertically();
		game.check_mario_collision();
		game.check_vertically_static_collisions();
		ui_factory->remove_inactive_objs();
		
		if (
			game_map->is_below_map(mario->get_top())
			|| !mario->is_active()
		) {
			keyboard->off();
			keyboard->on();
			game_level->restart();
			mario = ui_factory->get_mario();
			std::this_thread::sleep_for(1000ms);
		}
		
		if (game.is_level_end()) {
			if (!game_level->is_final()) {
				game_level = game_level->get_next();
				mario = ui_factory->get_mario();
				std::this_thread::sleep_for(1000ms);
				keyboard->off();
				keyboard->on();
				game.start_level();
			} else {
				is_victory = true;
				game.finish();
			}
		}
		
		game_map->refresh();
		control_settings->set_cursor_start_position();
		game_map->show();
		std::this_thread::sleep_for(frame_delay);
	} while (
		!game.is_finished()
	);
	
#ifdef LINUX_CONSOLE
	endwin();
#endif
	
	if (is_victory) {
		std::printf("\nПоздравляем! Вы прошли игру!\n");
		std::printf("Нажмите Enter, чтобы выйти...");
		std::fflush(stdout);
		std::getchar();
	}
}
