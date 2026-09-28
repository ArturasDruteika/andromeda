#pragma once


#include "pch.hpp"


namespace andromeda::rendering
{
    /// @brief Tracks frame timing and frames per second.
    ///
    /// Computes the elapsed time between frames as well as instantaneous and
    /// smoothed FPS values.
    class FpsCounter
    {
    public:
        /// @brief Constructs an FPS counter.
        FpsCounter();

        /// @brief Destroys the FPS counter.
        ~FpsCounter();

        FpsCounter(const FpsCounter& other) = delete;
        FpsCounter& operator=(const FpsCounter& other) = delete;
        FpsCounter(FpsCounter&& other) noexcept = delete;
        FpsCounter& operator=(FpsCounter&& other) noexcept = delete;

        /// @brief Updates the frame timing information.
        ///
        /// Call this once for every rendered frame.
        void frame_tick();

        /// @brief Retrieves the instantaneous frames per second.
        ///
        /// @return Instantaneous FPS.
        float get_instant_fps() const;

        /// @brief Retrieves the smoothed frames per second.
        ///
        /// @return Smoothed FPS.
        float get_smoothed_fps() const;

        /// @brief Retrieves the elapsed time since the previous frame.
        ///
        /// @return Frame delta time in seconds.
        float get_delta_seconds() const;

    private:
        /// @brief Time point of the previous frame.
        std::chrono::steady_clock::time_point m_last_time;

        /// @brief Elapsed time between the current and previous frame.
        float m_delta_seconds;

        /// @brief Instantaneous frames per second.
        float m_instant_fps;

        /// @brief Smoothed frames per second.
        float m_smoothed_fps;

        /// @brief Indicates whether the next frame is the first recorded frame.
        bool m_first_frame;
    };
}
