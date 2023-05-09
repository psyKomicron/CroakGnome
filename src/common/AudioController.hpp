#ifndef __AUDIOCONTROLLER_HPP
#define __AUDIOCONTROLLER_HPP

#include <string>
#include <thread>
#include <pipewire/pipewire.h>

namespace Croak::Audio
{
    class AudioController
    {
    public:
        ~AudioController();

        std::string getAudioEndpoints();
        
        static void registryEventGlobal(void* data, uint32_t id, uint32_t permissions, const char*  type, uint32_t version, const struct spa_dict* props);

    private:
        std::thread pwThread{};
        bool threadRunning = false;

        void getPWAudioObjects();
    };
}

#endif