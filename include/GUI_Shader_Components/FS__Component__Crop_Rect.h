#pragma once

#include <mat2x2.hpp>

#include <Window/Window_Controller.h>
#include <Shader/Shader_Components/Shader_Component.h>


namespace LGui
{

    class FS__Component__Crop_Rect : public LR::Shader_Component
    {
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
        std::string m_crop_area_rect_uniform_name = "fs_crop_area_rect";

        int m_crop_area_rect_uniform = -1;

    public:
        void init(unsigned int _opengl_program_handle) override;

    public:
        void set_crop_area_rect(const Rectangle& _rectangle) const;
        void reset_crop_area() const;

    };

}
