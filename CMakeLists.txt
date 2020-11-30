cmake_minimum_required(VERSION 3.5)

project(ECS_Game LANGUAGES C)

set(LIBS
	SDL2
	SDL2_image
	m
	/home/ilyas/pureC/libs/build-libs-Desktop-Debug/liblist.so
	)
set(HDR
	#List/list.h
	/home/ilyas/pureC/libs/libs/list/list.h
	Vector2D/vector2d.h
	Entitys/game_object.h
	Entitys/player_entity.h
	Systems/collision_system.h
	Systems/ai_system.h
	Systems/drawing_system.h
	Systems/moving_system.h
	Systems/event_system.h
	Components/position_component.h
	Components/texture_component.h
	)

set (SRC
	#List/list.c
	Vector2D/vector2d.c
	Systems/ai_system.c
	Systems/collision_system.c
	Systems/drawing_system.c
	Systems/moving_system.c
	Systems/event_system.c
	main.c
	)
add_executable(${PROJECT_NAME} main.c ${HDR} ${SRC})
target_link_libraries(${PROJECT_NAME} ${LIBS})


target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
