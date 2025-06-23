#include <Collisions/GUI_Collision_Resolution.h>

#include <Modules/Physics_Module__Point.h>

#include <Modules/Physics_Module__GUI.h>

using namespace LGui;


bool GUI_Collision_Resolution::resolve(const LPhys::Intersection_Data& _id, float _dt)
{
    L_ASSERT(LV::cast_variable<Physics_Module__GUI>(_id.first));
    L_ASSERT(LV::cast_variable<LPhys::Physics_Module__Point>(_id.second));

    Physics_Module__GUI* gui_physics_module = (Physics_Module__GUI*)_id.first;
//    LPhys::Physics_Module__Point* physics_module_point = (LPhys::Physics_Module__Point*)_id.second;

    gui_physics_module->notify_on_hovered(_id.point);

    return true;
}
