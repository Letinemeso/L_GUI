#include <Data_Extraction_Module.h>

using namespace LGui;


Data_Extraction_Module::Data_Extraction_Module()
{

}

Data_Extraction_Module::~Data_Extraction_Module()
{

}





LV::Variable_Base* Data_Extraction_Module_Stub::M_construct_product() const
{
    return new Data_Extraction_Module;
}

void Data_Extraction_Module_Stub::M_init_constructed_product(LV::Variable_Base* _product) const
{
    LV::Builder_Stub::M_init_constructed_product(_product);
}
