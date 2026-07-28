#pragma once


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/scene/i_scene_update_hooks.hpp"
#include "pch.hpp"


namespace andromeda::space
{
    class SPACE_API UpdateHooks
        : public virtual ISceneUpdateHooks
    {
    public:
        UpdateHooks();
        ~UpdateHooks() override;

        ISceneUpdateHooks::Handle add(ISceneUpdateHooks::Callback callback) override;
        void remove(ISceneUpdateHooks::Handle handle) override;
        void clear() override;
        void run(float delta_time) override;

    private:
        struct Entry
        {
            std::uint64_t id = 0;
            ISceneUpdateHooks::Callback fn;
        };

    private:
        std::uint64_t m_next_id;
        std::vector<Entry> m_entries;
    };
}