#include "Control.h"

Control::Control(Model& model, View& view) : model(model), view(view)
{
	key_state = SDL_GetKeyboardState(nullptr);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Control::handleInput()
{
	SDL_Event Event;
	while (SDL_PollEvent(&Event))
	{
		if (Event.type == SDL_MOUSEMOTION)
		{
			view.camera.pitch -= Event.motion.yrel * 0.1f;
			view.camera.yaw -= Event.motion.xrel * 0.01f;
		}
	}

	if (key_state[SDL_SCANCODE_R]) { model.background_color = std::vector<double>{1, 0, 0, 1}; }
	if (key_state[SDL_SCANCODE_G]) { model.background_color = std::vector<double>{0, 1, 0, 1}; }
	if (key_state[SDL_SCANCODE_B]) { model.background_color = std::vector<double>{0, 0, 1, 1}; }

	if (key_state[SDL_SCANCODE_W]) { view.camera.position += view.camera.direction; }
	if (key_state[SDL_SCANCODE_A]) { view.camera.position -= view.camera.right; }
	if (key_state[SDL_SCANCODE_S]) { view.camera.position -= view.camera.direction; }
	if (key_state[SDL_SCANCODE_D]) { view.camera.position += view.camera.right; }
}
