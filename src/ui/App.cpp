#include "App.hpp"
#include <glibmm.h>
#include <stdexcept>
#include <iostream>

namespace Croak::UI
{
    App::App() :
        Gtk::Application("org.gtkmm.croak.application", Gio::Application::Flags::HANDLES_OPEN)
    {}

    Glib::RefPtr<App> App::create()
    {
        g_message("App created.");

        return Glib::make_refptr_for_instance(new App());
    }

    void App::on_activate()
    {
        g_message("App activated.");

        try
        {
            auto&& provider = Gtk::CssProvider::create();
            provider->load_from_resource("/croak/ui/style.css");
            //provider->add_provider_for_display()

            // Create main window.
            auto&& refBuilder = Gtk::Builder::create_from_resource("/croak/ui/mainwindow2.glade");
            auto&& window = Gtk::Builder::get_widget_derived<MainWindow>(refBuilder, "app_window");
            if (!window)
            {
                throw std::runtime_error("No \"app_window\" object in window.ui");
            }

            // Add the main window to the window list.
            add_window(*window);

            window->signal_hide().connect(
                sigc::bind(sigc::mem_fun(*this, &App::on_hide_window), window)
            );

            window->present();
        }
        catch (const Glib::Error& ex) 
        {
            g_error("ExampleApplication::on_activate(): %s", ex.what());
            //std::cerr << "ExampleApplication::on_activate(): " << ex.what() << std::endl;
        }
        catch (const std::exception& ex) 
        {
            g_error("ExampleApplication::on_activate(): %s", ex.what());
            //std::cerr << "ExampleApplication::on_activate(): " << ex.what() << std::endl;
        }
    }

    void App::on_open(const Gio::Application::type_vec_files &files, const Glib::ustring &hint)
    {
    }
    
    void App::on_hide_window(Gtk::Window *window)
    {
        delete window;
    }
}