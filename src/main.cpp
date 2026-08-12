#include <blackboard/app.hpp>




// TODO: add logging system (IMGUI)




using bb::App;




int main(int /*unused*/, char** /*unused*/)
{
    App::initialize();

    while (App::is_open())
    {
        App::update();
        App::draw();
    }

    App::deinitialize();


    return 0;
}