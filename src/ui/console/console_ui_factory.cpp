#include "console_ui_factory.hpp"

using drw::ConsoleUIFactory;

ConsoleUIFactory::ConsoleUIFactory(Game* game) : UIFactory(game) {}

void ConsoleUIFactory::remove_inactive_objs() {
	// Убитых врагов, собранные монеты и плащ воды пора убрать с карты.
	remove_inactive(enemies);
	remove_inactive(flyable_enemies);
	remove_inactive(jumpable_enemies);
	remove_inactive(moneys);
	remove_inactive(coat_of_waters);
}

template<class T>
void ConsoleUIFactory::remove_inactive(std::vector<T*>& objs) {
	for (auto it = objs.begin(); it != objs.end(); ) {
		T* obj = *it;
		if (obj->is_active()) {
			++it;
		} else {
			game->remove_collisionable(obj);
			game->remove_movable(obj);
			game->remove_map_movable(obj);
			game_map->remove_obj(obj);
			delete obj;
			it = objs.erase(it);
		}
	}
}

void ConsoleUIFactory::clear_data() {
	game->remove_objs();
	game_map->remove_objs();
	delete mario;
	mario = nullptr;
	boxes.clear();
	coat_of_waters.clear();
	coat_of_water_boxes.clear();
	full_boxes.clear();
	floating_ships.clear();
	ships.clear();
	enemies.clear();
	flyable_enemies.clear();
	jumpable_enemies.clear();
	moneys.clear();
}

void ConsoleUIFactory::create_box(
	const Coord& top_left, const int width, const int height
) {
	ConsoleBox* box = new ConsoleBox(top_left, width, height);
	boxes.push_back(box);
	game->add_map_movable(box);
	game->add_static_obj(box);
	game_map->add_obj(box);
}

void ConsoleUIFactory::create_coat_of_water(
	const Coord& top_left, const int width, const int height
) {
	ConsoleCoatOfWater* coat = new ConsoleCoatOfWater(top_left, width, height);
	coat_of_waters.push_back(coat);
	game->add_map_movable(coat);
	game->add_movable(coat);
	game->add_collisionable(coat);
	game_map->add_obj(coat);
}

void ConsoleUIFactory::create_coat_of_water_box(
	const Coord& top_left, const int width, const int height
) {
	ConsoleCoatOfWaterBox* coat_box = new ConsoleCoatOfWaterBox(top_left, width, height, this);
	coat_of_water_boxes.push_back(coat_box);
	game->add_collisionable(coat_box);
	game->add_map_movable(coat_box);
	game->add_static_obj(coat_box);
	game_map->add_obj(coat_box);
}

void ConsoleUIFactory::create_enemy(
	const Coord& top_left, const int width, const int height
) {
	ConsoleEnemy* enemy = new ConsoleEnemy(top_left, width, height);
	enemies.push_back(enemy);
	game->add_map_movable(enemy);
	game->add_movable(enemy);
	game->add_collisionable(enemy);
	game_map->add_obj(enemy);
}

void ConsoleUIFactory::create_flyable_enemy(
	const Coord& top_left, const int width, const int height
) {
	ConsoleFlyableEnemy* enemy = new ConsoleFlyableEnemy(top_left, width, height);
	flyable_enemies.push_back(enemy);
	game->add_map_movable(enemy);
	game->add_movable(enemy);
	game->add_collisionable(enemy);
	game_map->add_obj(enemy);
}

void ConsoleUIFactory::create_floating_ship(
	const Coord& top_left, const int width, const int height
) {
	ConsoleFloatingShip* ship = new ConsoleFloatingShip(top_left, width, height);
	floating_ships.push_back(ship);
	game->add_map_movable(ship);
	game->add_movable(ship);
	game->add_static_obj(ship);
	game_map->add_obj(ship);
}

void ConsoleUIFactory::create_full_box(
	const Coord& top_left, const int width, const int height
) {
	ConsoleFullBox* full_box = new ConsoleFullBox(top_left, width, height, this);
	full_boxes.push_back(full_box);
	game->add_collisionable(full_box);
	game->add_map_movable(full_box);
	game->add_static_obj(full_box);
	game_map->add_obj(full_box);
}

void ConsoleUIFactory::create_jumpable_enemy(
	const Coord& top_left, const int width, const int height
) {
	ConsoleJumpableEnemy* enemy = new ConsoleJumpableEnemy(top_left, width, height);
	jumpable_enemies.push_back(enemy);
	game->add_map_movable(enemy);
	game->add_movable(enemy);
	game->add_collisionable(enemy);
	game_map->add_obj(enemy);
}

void ConsoleUIFactory::create_mario(
	const Coord& top_left, const int width, const int height
) {
	game->remove_collisionable(mario);
	game->remove_movable(mario);
	game->remove_mario();
	game_map->remove_obj(mario);
	delete mario;
	mario = nullptr;
	
	mario = new ConsoleMario(top_left, width, height);
	game->add_collisionable(mario);
	game->add_movable(mario);
	game->add_mario(mario);
	game_map->add_obj(mario);
}

void ConsoleUIFactory::create_money(
	const Coord& top_left, const int width, const int height
) {
	ConsoleMoney* money = new ConsoleMoney(top_left, width, height);
	moneys.push_back(money);
	game->add_map_movable(money);
	game->add_movable(money);
	game->add_collisionable(money);
	game_map->add_obj(money);
}

void ConsoleUIFactory::create_ship(
	const Coord& top_left, const int width, const int height
) {
	ConsoleShip* ship = new ConsoleShip(top_left, width, height);
	ships.push_back(ship);
	game->add_map_movable(ship);
	game->add_static_obj(ship);
	game_map->add_obj(ship);
}

drw::GameMap* ConsoleUIFactory::get_game_map(const int height, const int width) {
	if (game_map == nullptr) {
		game_map = new ConsoleGameMap(height, width);
		game->set_game_map(game_map);
	}
	return game_map;
}

drw::Mario* ConsoleUIFactory::get_mario() {
	return mario;
}
