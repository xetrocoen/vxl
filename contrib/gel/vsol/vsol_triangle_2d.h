#ifndef VSOL_TRIANGLE_2D_H
#define VSOL_TRIANGLE_2D_H
//*****************************************************************************
//
// .NAME vsol_triangle_2d - Triangle of a 2D space.
// .LIBRARY vsol
// .INCLUDE vsol/vsol_triangle_2d.h
// .FILE    vsol/vsol_triangle_2d.cxx
//
// .SECTION Author
// Fran�ois BERTEL
//
// .SECTION Modifications
// 2000/06/17 Peter Vanroose  Implemented all operator==()s and type info
// 2000/05/02 Fran�ois BERTEL Creation
//*****************************************************************************

class vsol_triangle_2d;

//*****************************************************************************
// External declarations for values
//*****************************************************************************
#include <vsol/vsol_triangle_2d_ref.h>
#include <vsol/vsol_polygon_2d.h>

class vsol_triangle_2d
  :public vsol_polygon_2d
{
  //***************************************************************************
  // Initialization
  //***************************************************************************
public:
  //---------------------------------------------------------------------------
  //: Constructor from its 3 vertices
  //---------------------------------------------------------------------------
  explicit vsol_triangle_2d(const vsol_point_2d_ref &new_p0,
                            const vsol_point_2d_ref &new_p1,
                            const vsol_point_2d_ref &new_p2);

  //---------------------------------------------------------------------------
  //: Copy constructor
  //---------------------------------------------------------------------------
  vsol_triangle_2d(const vsol_triangle_2d &other);

  //---------------------------------------------------------------------------
  //: Destructor
  //---------------------------------------------------------------------------
  virtual ~vsol_triangle_2d();

  //---------------------------------------------------------------------------
  //: Clone `this': creation of a new object and initialization
  //: See Prototype pattern
  //---------------------------------------------------------------------------
  virtual vsol_spatial_object_2d_ref clone(void) const;

  //***************************************************************************
  // Access
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Return the first vertex
  //---------------------------------------------------------------------------
  virtual vsol_point_2d_ref p0(void) const;

  //---------------------------------------------------------------------------
  //: Return the second vertex
  //---------------------------------------------------------------------------
  virtual vsol_point_2d_ref p1(void) const;
  
  //---------------------------------------------------------------------------
  //: Return the last vertex
  //---------------------------------------------------------------------------
  virtual vsol_point_2d_ref p2(void) const;

  //***************************************************************************
  // Comparison
  //***************************************************************************
  
  //---------------------------------------------------------------------------
  //: Has `this' the same points than `other' in the same order ?
  //---------------------------------------------------------------------------
  virtual bool operator==(const vsol_triangle_2d &other) const;
  virtual bool operator==(const vsol_polygon_2d &other) const; // virtual of vsol_polygon_2d
  virtual bool operator==(const vsol_spatial_object_2d& obj) const; // virtual of vsol_spatial_object_2d

  //***************************************************************************
  // Status report
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Return the area of `this'
  //---------------------------------------------------------------------------
  virtual double area(void) const;

  //***************************************************************************
  // Element change
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Set the first vertex
  //---------------------------------------------------------------------------
  virtual void set_p0(const vsol_point_2d_ref &new_p0);

  //---------------------------------------------------------------------------
  //: Set the second vertex
  //---------------------------------------------------------------------------
  virtual void set_p1(const vsol_point_2d_ref &new_p1);
  
  //---------------------------------------------------------------------------
  //: Set the last vertex
  //---------------------------------------------------------------------------
  virtual void set_p2(const vsol_point_2d_ref &new_p2);
};

#endif // #ifndef VSOL_TRIANGLE_2D_H
