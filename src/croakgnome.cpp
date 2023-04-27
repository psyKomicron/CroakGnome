#include <stdio.h>
#include <gtkmm.h>
#include <glibmm.h>

//#include "ui/MainWindow.hpp"
#include "ui/App.hpp"

#define PROJECT_NAME "CroakGnome"

int main(int argc, char **argv) 
{
    g_message("Croak GTK - Simple audio mixer application made with Gtkmm4.");

    auto&& app = Croak::UI::App::create();
    return app->run(argc, argv);
}
