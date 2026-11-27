target_sources(${PROJECT_NAME}
	PRIVATE
		coat_of_water.cpp
		coat_of_water_box.cpp
		full_box.cpp
		enemy.cpp
		floating_ship.cpp
		flyable_enemy.cpp
		jumpable_enemy.cpp
		mario.cpp
		money.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
