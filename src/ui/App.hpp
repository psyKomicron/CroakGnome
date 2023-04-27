#ifndef __APP_HPP
#define __APP_HPP

#include <gtkmm.h>
#include "MainWindow.hpp"

namespace Croak::UI
{
    class App: public Gtk::Application
    {
    public:
        static Glib::RefPtr<App> create();

    protected:
        App();

        void on_activate() override;
        void on_open(const Gio::Application::type_vec_files& files, const Glib::ustring& hint) override;

    private:
        MainWindow* mainWindow = nullptr;

        void on_hide_window(Gtk::Window* window);
    };
}

#endif