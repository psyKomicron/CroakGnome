#include "AudioController.hpp"

#include <glibmm.h>
#include <fmt/core.h>

namespace Croak::Audio::PipeWire
{
}

namespace Croak::Audio
{
    AudioController::~AudioController()
    {
        // if (threadRunning)
        // {
        //     g_debug("Waiting for PipeWire thread.");
        //     pwThread.join();
        // }
    }


    void AudioController::registryEventGlobal(void* data, uint32_t id, uint32_t permissions, const char*  type, uint32_t version, const struct spa_dict* props)
    {
        g_debug("Object id: %u | type: %s/%d", id, type, version);
    }

    std::string AudioController::getAudioEndpoints()
    {
        threadRunning = true;
        pwThread = std::thread(&AudioController::getPWAudioObjects, this);
        
        return std::string();
    }


    void AudioController::getPWAudioObjects()
    {
        g_debug("Using PipeWire version %s -- headers %s", pw_get_library_version(), pw_get_headers_version());
        // g_debug("Connecting to deamon.");

        int argc = 0;
        pw_init(&argc, nullptr);

        pw_main_loop* loop = pw_main_loop_new(nullptr);
        // g_debug(">> pw_main_loop_new OK");
        
        pw_context* context = pw_context_new(pw_main_loop_get_loop(loop), nullptr, 0);
        // g_debug(">> pw_context_new OK");

        pw_core* core = pw_context_connect(context, nullptr, 0);
        // g_debug(">> pw_context_connect OK");

        pw_registry *registry = pw_core_get_registry(core, PW_VERSION_REGISTRY, 0);
        // g_debug(">> pw_core_get_registry OK");

        spa_hook registryListener{};
        spa_zero(registryListener);

        static struct pw_registry_events registryEvents = 
        {
            PW_VERSION_REGISTRY_EVENTS
        };
        registryEvents.global = &AudioController::registryEventGlobal;

        pw_registry_add_listener(registry, &registryListener, &registryEvents, nullptr);
        // g_debug(">> pw_registry_add_listener OK");

        pw_main_loop_run(loop);

        pw_proxy_destroy((pw_proxy*)registry);
        // g_debug(">> pw_proxy_destroy OK");

        pw_core_disconnect(core);
        // g_debug(">> pw_core_disconnect OK");
        
        pw_context_destroy(context);
        // g_debug(">> pw_context_destroy OK");
        
        pw_main_loop_destroy(loop);
        // g_debug(">> pw_main_loop_destroy OK");

        g_message("Finished audio pass.");
    }
}