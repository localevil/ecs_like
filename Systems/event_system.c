#include <SDL2/SDL.h>

int8_t event_system(uint32_t *current_time) {
	static SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return 1;
		}
	}
	*current_time = SDL_GetTicks();
	return 0;
}
