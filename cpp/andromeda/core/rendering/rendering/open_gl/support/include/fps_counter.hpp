#ifndef RENDERING__OPENGL__SUPPORT__FPS_COUNTER__HPP
#define RENDERING__OPENGL__SUPPORT__FPS_COUNTER__HPP


#include "pch.hpp"


namespace andromeda::rendering
{
    class FpsCounter
    {
    public:
        FpsCounter();
        ~FpsCounter();

        FpsCounter(const FpsCounter& other) = delete;
        FpsCounter& operator=(const FpsCounter& other) = delete;
        FpsCounter(FpsCounter&& other) noexcept = delete;
        FpsCounter& operator=(FpsCounter&& other) noexcept = delete;

        // Call once per frame
        void frame_tick();

        float get_instant_fps() const;
        float get_smoothed_fps() const;

        // Delta time in seconds
        float get_delta_seconds() const;

    private:
        std::chrono::steady_clock::time_point m_last_time;
        float m_delta_seconds;
        float m_instant_fps;
        float m_smoothed_fps;
        bool m_first_frame;
    };
}

#endif // RENDERING__OPENGL__SUPPORT__FPS_COUNTER__HPP