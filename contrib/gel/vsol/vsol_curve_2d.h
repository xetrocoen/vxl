#ifndef VSOL_CURVE_2D_H
#define VSOL_CURVE_2D_H
//*****************************************************************************
//
// .NAME vsol_curve_2d - Abstract curve in a 2D space
// .LIBRARY vsol
// .INCLUDE vsol/vsol_curve_2d.h
// .FILE    vsol/vsol_curve_2d.cxx
//
// .SECTION Author
// Fran�ois BERTEL
//
// .SECTION Modifications
// 2000/06/17 Peter Vanroose  Implemented all operator==()s and type info
// 2000/04/27 Fran�ois BERTEL Creation
//*****************************************************************************

class vsol_curve_2d;

//*****************************************************************************
// External declarations for values
//*****************************************************************************
#include <vsol/vsol_curve_2d_ref.h>
#include <vsol/vsol_spatial_object_2d.h>

#include <vsol/vsol_point_2d_ref.h>

class vsol_curve_2d
  :public vsol_spatial_object_2d
{
public:
  enum vsol_curve_2d_type
  { CURVE_NO_TYPE=0,
    LINE,
    CONIC,
    NUM_CURVE_TYPES
  };

  //***************************************************************************
  // Initialization
  //***************************************************************************
public:
  //---------------------------------------------------------------------------
  //: Destructor
  //---------------------------------------------------------------------------
  virtual ~vsol_curve_2d();

  //---------------------------------------------------------------------------
  //: return the spatial type
  //---------------------------------------------------------------------------
  vsol_spatial_object_2d_type spatial_type(void) const { return vsol_spatial_object_2d::CURVE; }

  //---------------------------------------------------------------------------
  //: return the curve type
  //---------------------------------------------------------------------------
  virtual vsol_curve_2d_type curve_type(void) const { return vsol_curve_2d::CURVE_NO_TYPE; }

  //***************************************************************************
  // Access
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Return the first point of `this'
  //---------------------------------------------------------------------------
  virtual vsol_point_2d_ref p0(void) const=0;

  //---------------------------------------------------------------------------
  //: Return the last point of `this'
  //---------------------------------------------------------------------------
  virtual vsol_point_2d_ref p1(void) const=0;
  
  //***************************************************************************
  // Status report
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Return the length of `this'
  //---------------------------------------------------------------------------
  virtual double length(void) const=0;

  //***************************************************************************
  // Status setting
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Set the first point of the curve
  //---------------------------------------------------------------------------
  virtual void set_p0(const vsol_point_2d_ref &new_p0)=0;

  //---------------------------------------------------------------------------
  //: Set the last point of the curve
  //---------------------------------------------------------------------------
  virtual void set_p1(const vsol_point_2d_ref &new_p1)=0;
};

#endif // #ifndef VSOL_CURVE_2D_H
