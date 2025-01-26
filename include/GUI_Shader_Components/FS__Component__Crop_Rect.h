#pragma once

#include <mat2x2.hpp>

#include <Window/Window_Controller.h>
#include <Shader/Shader_Components/Shader_Component.h>


namespace LGui
{

    class FS__Component__Crop_Rect : public LR::Shader_Component
    {
    public:
        INIT_VARIABLE(LGui::FS__Component__Crop_Rect, LR::Shader_Component)

    public:
        struct Rectangle
        {
            float left = 0.0f;
            float right = LR::Window_Controller::get_window_data().width;
            float bottom = 0.0f;
            float top = LR::Window_Controller::get_window_data().height;

            inline glm::mat2x2 construct_matrix() const { return { left, right, bottom, top }; }
        };

    private:
        std::string m_crop_area_rect_uniform_name;

        int m_crop_area_rect_uniform = -1;

    public:
        inline void set_crop_area_rect_uniform_name(const std::string& _value) { m_crop_area_rect_uniform_name = _value; }

    public:
        void init(unsigned int _opengl_program_handle) override;

    public:
        void set_crop_area_rect(const Rectangle& _rectangle) const;
        void reset_crop_area() const;

    };


    class FS__Component_Stub__Crop_Rect : public LR::Shader_Component_Stub
    {
    public:
        INIT_VARIABLE(LGui::FS__Component_Stub__Crop_Rect, LR::Shader_Component_Stub)

        INIT_FIELDS
        ADD_FIELD(std::string, crop_area_rect_uniform_name)
        FIELDS_END

    public:
        std::string crop_area_rect_uniform_name;

    public:
        INIT_BUILDER_STUB(FS__Component__Crop_Rect)

    };

}
