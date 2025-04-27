#include "main.h"
#include "model.h"
#include "view.h"
#include "control.h"


int main(int argc, char* argv[])
{
	SDL_Window* main_window;
	init(main_window);

	Model model1("models/sun.obj", glm::vec3(1.0f, 1.0f, 0.0f), 1.0f);
	//model1.matrix = glm::scale(model1.matrix, { 100,100,100 });

	// Example: Use default ambient value (0.1f) for the test cube
	Model model2("models/earth.obj", {0.5f, 0.5f, 0.5f}, 0.f);
	Model model3("models/mercury.obj", {0.5f, 0.5f, 0.5f}, 0.f);
	Model model4("models/mars.obj", {0.5f, 0.5f, 0.5f}, 0.f);
	//model2.matrix = glm::scale(model2.matrix, { 40,80,40 });

	Camera camera;
	Control control(camera);

	View view1(model1, camera);
	View view2(model2, camera);
	View view3(model3, camera);
	View view4(model4, camera);

	std::vector<View*> views;
	views.push_back(&view1);
	views.push_back(&view2);
	views.push_back(&view3);
	views.push_back(&view4);

	for (size_t i = 1; i < views.size(); ++i)
	{
		views[i]->addPointLight(glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f), 100);
	}
	for (auto& view : views)
	{
		//view->addDirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.8f, 0.8f, 0.8f), 0.8f);
		//view->addPointLight(glm::vec3(0, 0, 0), glm::vec3(1.0f, 0.0f, 0.0f), 1.0f);
		//view->addSpotLight(glm::vec3(20, 10, 10), glm::vec3(0, 0, -1), glm::vec3(1.0f), 100.0f);
	}

	const double dt = 10;
	double accumulatedTime = 0.0;
	double lastTime = SDL_GetTicks();
	double currentTime;

	float radius = 40.0f; // Orbit radius
	while (true)
	{
		currentTime = SDL_GetTicks();
		accumulatedTime += currentTime - lastTime;
		lastTime = currentTime;

		control.handleInput();

		while (accumulatedTime > dt)
		{
			accumulatedTime -= dt;
		}
		//	model2.matrix = glm::rotate(model2.matrix, 0.01f, glm::vec3(0, 1, 0));
		float angle = (float)currentTime * 0.0005f; // Adjust speed factor as needed
		glm::vec3 orbitPos = glm::vec3(radius * cos(angle), 0.0f, radius * sin(angle));

		// Set model2's matrix to orbit the origin (0,0,0)
		model2.matrix = glm::translate(glm::mat4(1.0f), orbitPos);
		model3.matrix = glm::translate(glm::mat4(1.0f), orbitPos);
		model4.matrix = glm::translate(glm::mat4(1.0f), orbitPos);
		// Apply scaling (from original commented line) after translation
		//model2.matrix = glm::scale(model2.matrix, glm::vec3(40.0f, 80.0f, 40.0f));

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
