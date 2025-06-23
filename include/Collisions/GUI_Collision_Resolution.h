#pragma once

#include <Collision_Resolution/Collision_Resolution_Interface.h>


namespace LGui
{

    class GUI_Collision_Resolution : public LPhys::Collision_Resolution_Interface
    {
    public:
        bool resolve(const LPhys::Intersection_Data& _id, float _dt) override;

    };

}
