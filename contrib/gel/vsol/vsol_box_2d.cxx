#include <vsol/vsol_box_2d.h>

vsol_box_2d::vsol_box_2d()
{
  // cout << "making a boxology object" << endl;
}

vsol_box_2d::vsol_box_2d(vsol_box_2d const &b){
  _box = b._box;
}
vsol_box_2d::~vsol_box_2d()
{
  // cout << "deleting a boxology object" << endl;
  
}




double vsol_box_2d::get_min_x()
{
  return (_box.get_min())[0]; 
}

double vsol_box_2d::get_max_x()
{
  return (_box.get_max())[0]; 
}

double vsol_box_2d::get_min_y()
{
  return (_box.get_min())[1]; 
}

double vsol_box_2d::get_max_y()
{
  return (_box.get_max())[1]; 
}



void vsol_box_2d::set_min_x(const double& v)
{
  (_box.get_min())[0]=v;
}

void vsol_box_2d::set_max_x(const double& v)
{
  (_box.get_max())[0]=v;
}

void vsol_box_2d::set_min_y(const double& v)
{
  (_box.get_min())[1]=v;
}

void vsol_box_2d::set_max_y(const double& v)
{
  (_box.get_max())[1]=v;
}

