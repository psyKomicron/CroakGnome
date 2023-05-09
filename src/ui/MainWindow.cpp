#include "MainWindow.hpp"
#include "common/AudioController.hpp"

#include <future>

namespace Croak::UI
{
    MainWindow::MainWindow(BaseObjectType *base, const Glib::RefPtr<Gtk::Builder>& builder) :
        Gtk::ApplicationWindow(base),
        builder{ builder }
    {
        auto&& button = builder->get_widget<Gtk::Button>("icon_button");
        if (!button)
        {
            g_error("'icon_button' not found, cannot connect signal.");
        }
        else
        {
            button->signal_clicked().connect
            (
                sigc::mem_fun(*this, &MainWindow::button_clicked)
            );
        }
    }

    void MainWindow::loadAudioEndpoint()
    {
        try
        {
            auto&& label = builder->get_widget<Gtk::Label>("title_label");
            if (label)
            {
                auto name = controller.getAudioEndpoints();
                Glib::ustring text{ name };
                label->set_text(text);
            }
        }
        catch (const Glib::Error& err)
        {
            g_warning("(Glib::Error) Failed to load audio endpoint: %s", err.what());
        }
        catch (const std::exception& ex)
        {
            g_warning("(std::exception) Failed to load audio endpoint: %s", ex.what());
        }
    }

    void MainWindow::button_clicked()
    {
        g_message("Launching audio endpoint discovery.");
        auto fut = std::async(
            std::launch::async,
            &MainWindow::loadAudioEndpoint,
            this
        );
        g_message("Launched audio endpoint discovery async.");
        //fut.get();
    }
}
