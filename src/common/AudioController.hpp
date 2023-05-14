#ifndef __AUDIOCONTROLLER_HPP
#define __AUDIOCONTROLLER_HPP

#include <string>
#include <thread>
#include <vector>
#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wpedantic"
#include <pipewire/pipewire.h>
#pragma GCC diagnostic pop

namespace Croak::Audio
{
    class AudioController
    {
    public:
        ~AudioController();

        inline bool running() { return joinedLoop; };
        inline std::vector<std::string> pipeWireObjects() { return pwObjects; }

        std::string getAudioEndpoints();
        void start();
        void stop();

    private:
        static AudioController* instance;
        std::thread pwThread{};
        bool joinedLoop = false;
        std::mutex pwObjectsLock{};
        std::vector<std::string> pwObjects{};
        // PipeWire API attributes.
        pw_main_loop* pwLoop = nullptr;
        pw_context* pwContex = nullptr;
        pw_core* pwCore = nullptr;
        pw_registry *pwRegistry = nullptr;
        pw_context* pwContext = nullptr;

        static void registryEventGlobal(void* data, uint32_t id, uint32_t permissions, const char*  type, uint32_t version, const struct spa_dict* props);
        void getPWAudioObjects();
    };
}

#endif