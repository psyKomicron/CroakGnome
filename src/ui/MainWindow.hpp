#ifndef __MAINWINDOW_HPP
#define __MAINWINDOW_HPP

#include <gtkmm.h>
#include <string>

namespace Croak::UI
{
    class MainWindow : public Gtk::ApplicationWindow
    {
    public:
        MainWindow(BaseObjectType* base, const Glib::RefPtr<Gtk::Builder>& builder);

    private:
        std::wstring_view name{};
        Glib::RefPtr<Gtk::Builder> builder{ nullptr };
    };
}

#endif