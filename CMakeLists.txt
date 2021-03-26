cmake_minimum_required(VERSION 3.5)

project(ECS_Game LANGUAGES C)

set(CMAKE_C_FLAGS "-Wall -Wextra -g")

add_subdirectory(List)
add_subdirectory(Vector2D)
file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR})

set(LIBS
	SDL2
	SDL2_image
	m
	list
	vector2f
	)

set(HDR
	Entitys/entity.h

	Systems/collision_system.h
	Systems/ai_system.h
	Systems/drawing_system.h
	Systems/moving_system.h
	Systems/event_system.h
	Systems/transform_system.h

	Components/position_component.h
	Components/texture_component.h
	Components/physics_component.h
	Components/transform_component.h
	Components/component.h
	)

set (SRC
	Systems/ai_system.c
	Systems/collision_system.c
	Systems/drawing_system.c
	Systems/moving_system.c
	Systems/event_system.c
	Systems/transform_system.c
	main.c
	)
add_executable(${PROJECT_NAME} main.c ${HDR} ${SRC})
target_link_libraries(${PROJECT_NAME} ${LIBS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
