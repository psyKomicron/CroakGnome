#include "MainWindow.hpp"
#include "common/AudioController.hpp"
#include <exception>

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
            button->signal_clicked().connect(
                sigc::mem_fun(*this, &MainWindow::button_clicked)
            );
        }
    }

    void MainWindow::loadAudioEndpoint()
    {
        g_debug("This is a call to g_debug");

        try
        {
            throw std::exception();

            Croak::Audio::AudioController controller{};
            auto name = controller.getAudioEndpoints();

            auto&& button = builder->get_widget<Gtk::Button>("icon_button1");
            if (!button)
            {
                throw std::runtime_error("Button is nullptr.");
            }

            if (button->get_icon_name() == "audio-volume-low")
            {
                button->set_icon_name("audio-volume-high");
            }
            else
            {
                button->set_icon_name("audio-volume-low");
            }
        }
        catch (const std::exception& ex)
        {
            g_error("(std::exception) Failed to load audio endpoint: %s\n", ex.what());
        }
        // catch (const Glib::Error& err)
        // {
        //     g_error("(Glib::Error) Failed to load audio endpoint: %s", err.what());
        // }
        // catch (const std::exception& ex)
        // {
        //     g_error("(std::exception) Failed to load audio endpoint: %s\n", ex.what());
        // }
    }

    void MainWindow::button_clicked()
    {
        g_message("Button clicked.");
        
        loadAudioEndpoint();
    }
}
