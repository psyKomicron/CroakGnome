#ifndef __AUDIOCONTROLLER_HPP
#define __AUDIOCONTROLLER_HPP

#include <string>

namespace Croak::Audio
{
    class AudioController
    {
    public:
        std::wstring getAudioEndpoints();
    };
}

#endif