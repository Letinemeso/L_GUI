#include <Actions_Controller.h>

using namespace LGui;


void Actions_Controller::register_action(const std::string& _name, const Action& _action)
{
    L_ASSERT(!m_actions_map.find(_name).is_ok());

    m_actions_map.insert(_name, _action);
}

const Action& Actions_Controller::get_action(const std::string& _name) const
{
    Actions_Map::Const_Iterator action_it = m_actions_map.find(_name);

    L_ASSERT(action_it.is_ok());

    return *action_it;
}
