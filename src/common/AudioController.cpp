#include "AudioController.hpp"

#include <glibmm.h>
#include <fmt/core.h>
#include <mutex>

namespace Croak::Audio::PipeWire
{
}

namespace Croak::Audio
{
    AudioController::~AudioController()
    {
        stop();
    }

    std::string AudioController::getAudioEndpoints()
    {
        return std::string();
    }

    void AudioController::start()
    {
        pwThread = std::thread(&AudioController::getPWAudioObjects, this);
    }
    
    void Croak::Audio::AudioController::stop()
    {
        if (pwLoop)
        {
            pw_main_loop_quit(pwLoop);

            if (pwRegistry)
            {
                pw_proxy_destroy((pw_proxy*)pwRegistry);
            }

            if (pwCore)
            {
                pw_core_disconnect(pwCore);
            }

            if (pwContext)
            {
                pw_context_destroy(pwContext);        
            }

            pw_main_loop_destroy(pwLoop);

            joinedLoop = false;
        }
        else
        {
            g_warning("(AudioController::quitLoop) PipeWire loop is null, impossible to free PipeWire objects if they are not allocated.");
        }
    }


    void AudioController::registryEventGlobal(void* data, uint32_t id, uint32_t permissions, const char*  type, uint32_t version, const struct spa_dict* props)
    {
        if (data)
        {
            auto controller = static_cast<AudioController*>(data);
            std::unique_lock lock{ controller->pwObjectsLock };
            controller->pwObjects.push_back(fmt::format("Object id: %u | type: %s/%d", id, type, version));
        }
    }

    void AudioController::getPWAudioObjects()
    {
        g_debug("Using PipeWire version %s -- headers %s", pw_get_library_version(), pw_get_headers_version());

        int argc = 0;
        pw_init(&argc, nullptr);

        pwLoop = pw_main_loop_new(nullptr);
        pwContext = pw_context_new(pw_main_loop_get_loop(pwLoop), nullptr, 0);
        pwCore = pw_context_connect(pwContext, nullptr, 0);
        pwRegistry = pw_core_get_registry(pwCore, PW_VERSION_REGISTRY, 0);

        static struct pw_registry_events registryEvents = 
        {
            PW_VERSION_REGISTRY_EVENTS
        };
        spa_hook registryListener{};
        spa_zero(registryListener);
        registryEvents.global = &AudioController::registryEventGlobal;

        pw_registry_add_listener(pwRegistry, &registryListener, &registryEvents, static_cast<void*>(this));

        joinedLoop = true;
        pw_main_loop_run(pwLoop);
        
        g_message("Finished audio pass.");
    }
}