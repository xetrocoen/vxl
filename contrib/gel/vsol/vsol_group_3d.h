#ifndef VSOL_GROUP_3D_H
#define VSOL_GROUP_3D_H
//*****************************************************************************
//
// .NAME vsol_group_3d - Group of Spatial object in a 3D space
// .LIBRARY vsol
// .INCLUDE vsol/vsol_group_3d.h
// .FILE    vsol/vsol_group_3d.cxx
//
// .SECTION Author
// Fran�ois BERTEL
//
// .SECTION Modifications
// 2000/06/17 Peter Vanroose  Implemented all operator==()s and type info
// 2000/05/03 Fran�ois BERTEL Creation
//*****************************************************************************

class vsol_group_3d;

//*****************************************************************************
// External declarations for values
//*****************************************************************************
#include <vsol/vsol_group_3d_ref.h>
#include <vsol/vsol_spatial_object_3d.h>
#include <vcl_list.h>

class vsol_group_3d
  :public vsol_spatial_object_3d
{
  //***************************************************************************
  // Initialization
  //***************************************************************************
public:
  //---------------------------------------------------------------------------
  //: Default Constructor: group with no child
  //---------------------------------------------------------------------------
  explicit vsol_group_3d(void);

  //---------------------------------------------------------------------------
  //: Copy constructor.
  //: The objects of the group are not duplicated
  //---------------------------------------------------------------------------
  vsol_group_3d(const vsol_group_3d &other);
  
  //---------------------------------------------------------------------------
  //: Destructor
  //: The objects of the group are not deleted
  //---------------------------------------------------------------------------
  virtual ~vsol_group_3d();

  //---------------------------------------------------------------------------
  //: Clone `this': creation of a new object and initialization
  //: See Prototype pattern
  //---------------------------------------------------------------------------
  virtual vsol_spatial_object_3d_ref clone(void) const;

  //***************************************************************************
  // Access
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Return the object `i'
  //: REQUIRE: i>=0 and i<size()
  //---------------------------------------------------------------------------
  virtual vsol_spatial_object_3d_ref object(const int i) const;

  //***************************************************************************
  // Status report
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Return the real type of a group. It is a SPATIALGROUP
  //---------------------------------------------------------------------------
  enum vsol_spatial_object_3d_type spatial_type(void) const;

  //---------------------------------------------------------------------------
  //: Compute the bounding box of `this'
  //: REQUIRE: size()>0
  //---------------------------------------------------------------------------
  virtual void compute_bounding_box(void);

  //---------------------------------------------------------------------------
  //: Return the number of direct children of the group
  //---------------------------------------------------------------------------
  virtual int size(void) const;

  //---------------------------------------------------------------------------
  //: Return the number of objects of the group
  //---------------------------------------------------------------------------
  virtual int deep_size(void) const;

  //---------------------------------------------------------------------------
  //: Is `new_object' a child (direct or not) of `this' ?
  //---------------------------------------------------------------------------
  virtual bool is_child(const vsol_spatial_object_3d_ref &new_object) const;

  //***************************************************************************
  // Element change
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Add an object `new_object'to `this'
  //---------------------------------------------------------------------------
  virtual void add_object(const vsol_spatial_object_3d_ref &new_object);

  //***************************************************************************
  // Removal
  //***************************************************************************
  
  //---------------------------------------------------------------------------
  //: Remove object `i' of `this' (not delete it)
  //: REQUIRE: i>=0 and i<size()
  //---------------------------------------------------------------------------
  virtual void remove_object(const int i);

  //---------------------------------------------------------------------------
  //: The same behavior than dynamic_cast<>. Needed because VXL is not
  //: compiled with -frtti :-(
  //---------------------------------------------------------------------------
  virtual const vsol_group_3d *cast_to_group(void) const;

  //***************************************************************************
  // Implementation
  //***************************************************************************
private:
  //---------------------------------------------------------------------------
  // Description: Set of objects that `this' contains
  //---------------------------------------------------------------------------
  vcl_list<vsol_spatial_object_3d_ref> *storage_;
};

#endif // #ifndef VSOL_GROUP_3D_H
