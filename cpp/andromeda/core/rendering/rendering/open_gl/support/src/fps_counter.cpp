#include "../include/fps_counter.hpp"


namespace andromeda::rendering
{
    FpsCounter::FpsCounter()
        : m_last_time{ std::chrono::steady_clock::now() }
        , m_delta_seconds{ 0.0f }
        , m_instant_fps{ 0.0f }
        , m_smoothed_fps{ 0.0f }
        , m_first_frame{ true }
    {
    }

    FpsCounter::~FpsCounter() = default;

    void FpsCounter::frame_tick()
    {
        const std::chrono::steady_clock::time_point now =
            std::chrono::steady_clock::now();

        m_delta_seconds =
            std::chrono::duration<float>(now - m_last_time).count();

        m_last_time = now;

        if (m_delta_seconds > 0.0f)
        {
            m_instant_fps = 1.0f / m_delta_seconds;
        }
        else
        {
            m_instant_fps = 0.0f;
        }

        // Smooth with exponential moving average.
        constexpr float alpha = 0.1f;

        if (m_first_frame)
        {
            m_smoothed_fps = m_instant_fps;
            m_first_frame = false;
        }
        else
        {
            m_smoothed_fps =
                alpha * m_instant_fps +
                (1.0f - alpha) * m_smoothed_fps;
        }
    }

    float FpsCounter::get_instant_fps() const
    {
        return m_instant_fps;
    }

    float FpsCounter::get_smoothed_fps() const
    {
        return m_smoothed_fps;
    }

    float FpsCounter::get_delta_seconds() const
    {
        return m_delta_seconds;
    }
}