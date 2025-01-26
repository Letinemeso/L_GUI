#include <GUI_Shader_Components/FS__Component__Crop_Rect.h>

using namespace LGui;


void FS__Component__Crop_Rect::init(unsigned int _opengl_program_handle)
{
    Shader_Component::init(_opengl_program_handle);

    m_crop_area_rect_uniform = M_extract_uniform_location(m_crop_area_rect_uniform_name);
}

void FS__Component__Crop_Rect::set_crop_area_rect(const Rectangle& _rectangle) const
{
    glm::mat2x2 matrix = _rectangle.construct_matrix();
    glUniformMatrix2fv(m_crop_area_rect_uniform, 1, false, &matrix[0][0]);
}

void FS__Component__Crop_Rect::reset_crop_area() const
{
    glm::mat2x2 matrix = Rectangle().construct_matrix();

    glUniformMatrix2fv(m_crop_area_rect_uniform, 1, false, &matrix[0][0]);
}





BUILDER_STUB_DEFAULT_CONSTRUCTION_FUNC(FS__Component_Stub__Crop_Rect)

BUILDER_STUB_INITIALIZATION_FUNC(FS__Component_Stub__Crop_Rect)
{
    BUILDER_STUB_PARENT_INITIALIZATION;
    BUILDER_STUB_CAST_PRODUCT;

    product->set_crop_area_rect_uniform_name(crop_area_rect_uniform_name);
}
