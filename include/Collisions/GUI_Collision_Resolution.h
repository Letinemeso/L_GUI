#pragma once

#include <Collision_Resolution/Collision_Resolution_Interface.h>
#include <Modules/Physics_Module__Point.h>

#include <Collisions/Physics_Module__GUI.h>


namespace LGui
{

    class GUI_Collision_Resolution : public LPhys::Collision_Resolution_Interface
    {
    public:
        void resolve(const LPhys::Intersection_Data& _id, float _dt) override;

    };

}
