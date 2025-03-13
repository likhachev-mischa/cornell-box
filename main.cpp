#include "main.h"
#include "model.h"
#include "view.h"
#include "control.h"


int main(int argc, char* argv[]) {
    SDL_Window* main_window;
    init(main_window);

    Model model("cornell_room.obj",glm::vec3(1.0f,0.0f,0.0f));
    Camera camera;
    View view(model,camera);
    Control control(view);


    const double dt = 10;
    double accumulatedTime = 0.0;
    double lastTime = SDL_GetTicks();
    double currentTime;

    while (true) {

        currentTime = SDL_GetTicks();
        accumulatedTime += currentTime - lastTime;
        lastTime = currentTime;

        //we will later handle input
        control.handleInput();

        while (accumulatedTime > dt) {
            //timeStepModel(model, dt); // move the model dt time forward
            accumulatedTime -= dt;
        }

        //rendering, will later be a function call to the view part
        view.render(main_window);
    }

    tearDown(main_window);

    return 0;
}