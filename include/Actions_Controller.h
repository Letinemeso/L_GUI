#pragma once

#include <vec3.hpp>

#include <Object.h>

#include <Stuff/Function_Wrapper.h>
#include <Data_Structures/Map.h>


namespace LGui
{

    using Action = LST::Function<void(const glm::vec3&, LEti::Object*)>;


    class Actions_Controller
    {
    private:
        using Actions_Map = LDS::Map<std::string, Action>;

    private:
        Actions_Map m_actions_map;

    public:
        void register_action(const std::string& _name, const Action& _action);

    public:
        const Action& get_action(const std::string& _name) const;

    };

}
