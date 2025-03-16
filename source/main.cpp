#include "main.h"
#include "model.h"
#include "view.h"
#include "control.h"


int main(int argc, char* argv[]) {
	SDL_Window* main_window;
	init(main_window);

	Model model1("models/cornell_box.obj","materials/cornell_box.mtl");
	model1.matrix = glm::scale(model1.matrix, { 100,100,100 });
	Model model2("models/test_cube.obj","materials/example.mtl");
	model2.matrix = glm::scale(model2.matrix, { 40,80,40 });

	Camera camera;
	Control control(camera);

	View view1(model1, camera);
	View view2(model2, camera);
	std::vector<View*> views;
	views.push_back(&view1);
	views.push_back(&view2);

	for (auto& view : views)
	{
		view->addDirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.8f, 0.8f, 0.8f), 0.8f);
		view->addPointLight(glm::vec3(0, 0, 0), glm::vec3(1.0f, 0.5f, 0.5f), 100.0f);
		view->addSpotLight(glm::vec3(20, 10, 10), glm::vec3(0, 0, -1), glm::vec3(1.0f), 100.0f);
	}

	const double dt = 10;
	double accumulatedTime = 0.0;
	double lastTime = SDL_GetTicks();
	double currentTime;

	while (true) {
		currentTime = SDL_GetTicks();
		accumulatedTime += currentTime - lastTime;
		lastTime = currentTime;

		control.handleInput();

		while (accumulatedTime > dt) {
			accumulatedTime -= dt;
		}
		model2.matrix = glm::rotate(model2.matrix, 0.01f, glm::vec3(0, 1, 0));

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (auto& view : views)
		{
			view->render();
		}
		glFlush();
		SDL_GL_SwapWindow(main_window);
	}

	tearDown(main_window);

	return 0;
}