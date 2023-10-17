#ifndef SCREEN_H
#define SCREEN_H

#include <Data_Structures/Map.h>

#include <Object_System/Object_2D.h>


namespace LGui
{

    class Screen
    {
    private:
        LDS::Map<std::string, LEti::Object_2D*> m_objects;

    public:
        Screen();
        Screen(Screen&& _other);

        ~Screen();

    private:
        Screen(const Screen& _other) = delete;

    public:


    };

}

#endif // SCREEN_H
