#pragma once

#include <Collision_Resolution/Collision_Resolution.h>


namespace LGui
{

    class GUI_Collision_Resolution : public LPhys::Collision_Resolution
    {
    public:
        bool resolve(const LPhys::Intersection_Data& _id, float _dt) override;

    };

}
