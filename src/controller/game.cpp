#include "game.hpp"

#include <algorithm>

using drw::Game;

Game::Game() {}

void Game::add_collisionable(Collisionable* obj) {
	collisionable_objs.push_back(obj);
}

void Game::add_map_movable(MapMovable* obj) {
	map_movable_objs.push_back(obj);
}

void Game::add_mario(Mario* obj) {
	mario = obj;
}

void Game::add_movable(Movable* obj) {
	movable_objs.push_back(obj);
}

void Game::add_static_obj(Rect* obj) {
	static_objs.push_back(obj);
}

void Game::check_coat_of_water() noexcept {
	if (mario == nullptr || game_map == nullptr || !mario->has_coat_of_water()) {
		return;
	}
	Rect mario_rect = mario->get_rect();
	Rect water(
		{static_cast<float>(mario_rect.get_left()), static_cast<float>(game_map->get_water_level())},
		mario_rect.get_width(),
		GameMap::WATER_HEIGHT
	);
	if (mario->has_collision(&water)) {
		if (mario->get_vspeed() > 0) {
			mario->process_vertical_static_collision(&water);
		} else if (mario->get_vspeed() == 0) {
			mario->move_vertical_offset(
				static_cast<float>(water.get_top() - mario_rect.get_bottom())
			);
		}
	}
}

void Game::check_horizontally_static_collisions() noexcept {
	for (Collisionable* obj: collisionable_objs) {
		for (Rect* static_obj: static_objs) {
			if (obj->has_collision(static_obj)) {
				obj->process_horizontal_static_collision(static_obj);
				break;
			}
		}
	}
}

void Game::check_mario_collision() {
	for (int i = 0; i < collisionable_objs.size(); i++) {
		Collisionable* obj = collisionable_objs[i];
		if (obj->has_collision(mario)) {
			obj->process_mario_collision(mario);
			if (!mario->is_active()) {
				break;
			} else if (!obj->is_active()) {
				// Убитый враг или собранная монета должны исчезнуть из мира:
				// убираем их из модельных контейнеров (вид чистит фабрика).
				if (Movable* movable = dynamic_cast<Movable*>(obj)) {
					remove_movable(movable);
					if (MapMovable* map_movable = dynamic_cast<MapMovable*>(obj)) {
						remove_map_movable(map_movable);
					}
				}
				collisionable_objs[i] = collisionable_objs.back();
				collisionable_objs.pop_back();
				i--;
			}
		}
	}
}

void Game::check_moving_platform() noexcept {
	if (mario == nullptr || mario->get_vspeed() < 0) {
		return;
	}
	Rect mario_rect = mario->get_rect();
	for (Rect* static_obj: static_objs) {
		Movable* platform = dynamic_cast<Movable*>(static_obj);
		if (platform == nullptr) {
			continue;
		}
		if (
			mario_rect.get_bottom() == static_obj->get_top() &&
			mario_rect.get_right() > static_obj->get_left() &&
			mario_rect.get_left() < static_obj->get_right()
		) {
			mario->move_horizontal_offset(platform->get_hspeed());
			break;
		}
	}
}

bool Game::check_static_collisions(Collisionable* obj) const noexcept {
	for (Rect* static_obj: static_objs) {
		if (obj->has_collision(static_obj)) {
			return true;
		}
	}
	return false;
}

void Game::check_vertically_static_collisions() noexcept {
	if (mario->has_collision(static_objs[static_objs.size() - 1])) {
		is_level_end_ = true;
	}
	
	for (Collisionable* obj: collisionable_objs) {
		for (Rect* static_obj: static_objs) {
			if (obj->has_collision(static_obj)) {
				obj->process_vertical_static_collision(static_obj);
				break;
			}
		}
	}
}

void Game::finish() noexcept {
	is_finished_ = true;
}

bool Game::is_finished() const noexcept {
	return is_finished_;
}

bool Game::is_level_end() const noexcept {
	return is_level_end_;
}

void Game::move_map_left() noexcept {
	for (MapMovable* obj: map_movable_objs) {
		obj->move_map_left();
	}
}

void Game::move_map_right() noexcept {
	for (MapMovable* obj: map_movable_objs) {
		obj->move_map_right();
	}
}

void Game::move_objs_horizontally() noexcept {
	for (Movable* obj: movable_objs) {
		obj->move_horizontally();
	}
}

void Game::move_objs_vertically() noexcept {
	for (Movable* obj: movable_objs) {
		obj->move_vertically();
	}
}

void Game::remove_collisionable(Collisionable* obj) {
	remove_obj(collisionable_objs, obj);
}

void Game::remove_map_movable(MapMovable* obj) {
	remove_obj(map_movable_objs, obj);
}

void Game::remove_mario() noexcept {
	mario = nullptr;
}

void Game::remove_movable(Movable* obj) {
	remove_obj(movable_objs, obj);
}

void Game::remove_objs() {
	collisionable_objs.clear();
	map_movable_objs.clear();
	movable_objs.clear();
	static_objs.clear();
	remove_mario();
}

void Game::remove_static_obj(Rect* obj) {
	remove_obj(static_objs, obj);
}

void Game::set_game_map(GameMap* map) noexcept {
	game_map = map;
}

void Game::start_level() noexcept {
	is_level_end_ = false;
}

// ----------------------------------------------------------------------------
// 									PRIVATE
// ----------------------------------------------------------------------------
template<class T>
void Game::remove_obj(std::vector<T*>& container, T* obj) {
	container.erase(
		std::remove(
			container.begin(), container.end(), obj
		), 
		container.end()
	);
}
