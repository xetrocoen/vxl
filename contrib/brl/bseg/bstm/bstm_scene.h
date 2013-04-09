#ifndef bstm_scene_h_
#define bstm_scene_h_
//:
// \file
// \brief  bstm scene models a very generic (dynamic) scene, only specifies dimensions
// \author Ali Osman Ulusoy
// \date   07 Aug 2012
//
#include <bstm/basic/bstm_block_id.h>
#include <bstm/bstm_block_metadata.h>
#include <vpgl/vpgl_lvcs.h>
#include <vgl/vgl_point_3d.h>
#include <vgl/vgl_box_3d.h>
#include <vgl/vgl_box_2d.h>
#include <vcl_iosfwd.h>
#include <vul/vul_file.h>

//smart pointer stuff
#include <vbl/vbl_ref_count.h>
#include <vbl/vbl_smart_ptr.h>

//vpgl camera
#include <vpgl/vpgl_generic_camera.h>
#include <vpgl/vpgl_perspective_camera.h>

//: block info that can be easily made into a buffer and sent to gpu
struct bstm_scene_info
{
  //world information
  float    scene_origin[4];          // scene origin (4d point)
  int      scene_dims[4];            // number of blocks in each dimension
  float    block_len;                // size of each block (can only be 1 number now that we've established blocks are cubes)
  float    time_block_len;           // dimension of the time axis
  float    epsilon;                  // block_len/100.0 (placed here to avoid using a register)

  // tree meta information
  int      root_level;               // root_level of trees
  int      num_buffer;               // number of buffers (both data and tree)
  int      tree_buffer_length;       // length of tree buffer (number of cells/trees)
  int      data_buffer_length;       // length of data buffer (number of cells)


};

class bstm_scene_info_wrapper : public vbl_ref_count
{
  public:
  bstm_scene_info * info;
};

//: bstm_scene_scene: simple scene model that maintains (in world coordinates)
//      - scene origin
//      - number of blocks in each dimension
//      - size of each block in each dimension
//      - lvcs information
//      - xml path on disk and data path (directory) on disk
class bstm_scene : public vbl_ref_count
{
  public:
    //: empty scene, needs to be initialized manually
    bstm_scene() {}

    bstm_scene(vcl_string data_path, vgl_point_3d<double> const& origin, int version = 2);

    //: initializes scene from xmlFile
    bstm_scene(vcl_string filename);

    //: destructor
    ~bstm_scene() { }

    //: save scene xml file
    void save_scene();

    //: return a vector of block ids in visibility order
    vcl_vector<bstm_block_id> get_vis_blocks(vpgl_generic_camera<double>* cam);
    vcl_vector<bstm_block_id> get_vis_blocks(vpgl_perspective_camera<double>* cam);
    vcl_vector<bstm_block_id> get_vis_blocks(vpgl_camera_double_sptr & cam) {
      if ( cam->type_name() == "vpgl_generic_camera" )
        return this->get_vis_blocks( (vpgl_generic_camera<double>*) cam.ptr() );
      else if ( cam->type_name() == "vpgl_perspective_camera" )
        return this->get_vis_blocks( (vpgl_perspective_camera<double>*) cam.ptr() );
      else
        vcl_cout<<"bstm_scene::get_vis_blocks doesn't support camera type "<<cam->type_name()<<vcl_endl;
      //else return empty
      vcl_vector<bstm_block_id> empty;
      return empty;
    }
    //: visibility order from point, blocks must intersect with cam box
    vcl_vector<bstm_block_id>
    get_vis_order_from_pt(vgl_point_3d<double> const& pt,
                          vgl_box_2d<double> camBox = vgl_box_2d<double>());

    //: return a heap pointer to a scene info
    bstm_scene_info* get_blk_metadata(bstm_block_id id);
    bool block_exists(bstm_block_id id) const { return blocks_.find(id) != blocks_.end(); }
    bool block_on_disk(bstm_block_id id) const { return vul_file::exists( data_path_ + id.to_string() + ".bin"); }
    bool data_on_disk(bstm_block_id id, vcl_string data_type) {
      return vul_file::exists(data_path_ + data_type + "_" + id.to_string() + ".bin");
    }

    //: a list of block metadata...
    vcl_map<bstm_block_id, bstm_block_metadata>& blocks() { return blocks_; }
    unsigned num_blocks() const { return (unsigned) blocks_.size(); }

    //: mutable reference
    bstm_block_metadata& get_block_metadata(bstm_block_id id) { return blocks_[id]; }
    //: const so return a copy
    bstm_block_metadata get_block_metadata_const(bstm_block_id id) const;


    vcl_vector<bstm_block_id> get_block_ids() const;

    //: gets a tight bounding box for the scene
    vgl_box_3d<double>      bounding_box() const;
    //: gets a tight bounding box for the scene
    vgl_box_3d<int>         bounding_box_blk_ids() const;

    // returns the dimesnsion of the scene grid where each grid element is a block
    vgl_vector_3d<unsigned int>   scene_dimensions() const;

    //: If a block contains a 3-d point, set the block id, else return false. The local coordinates of the point are also returned
    bool contains(vgl_point_3d<double> const& p, bstm_block_id& bid, vgl_point_3d<double>& local_coords, double const t, double& local_time) const;

    //: returns bstm_block_id that contains specified time. The local coordinates of t is also returned
    bool contains_t(double const t, bstm_block_id& bid, double& local_time) const;

    //: gets a tight bounding box for the scene
    void      bounding_box_t(double& min_t, double& max_t) const;

    //: gets a tight bounding box of the block ids
    unsigned      blocks_ids_bounding_box_t() const;

    //: scene dimensions accessors
    vgl_point_3d<double>    local_origin()const { return local_origin_; }
    vgl_point_3d<double>    rpc_origin()  const { return rpc_origin_; }
    vpgl_lvcs               lvcs()        const { return lvcs_; }

    //: scene path accessors
    vcl_string              xml_path()    const { return xml_path_; }
    vcl_string              data_path()   const { return data_path_; }

    //: appearance model accessor
    vcl_vector<vcl_string> appearances()  const { return appearances_; }
    bool has_data_type(vcl_string data_type);

    //: scene version number
    int version() { return version_; }
    void set_version(int v) { version_ = v; }

    //: scene mutators
    void set_local_origin(vgl_point_3d<double> org) { local_origin_ = org; }
    void set_rpc_origin(vgl_point_3d<double> rpc)   { rpc_origin_ = rpc; }
    void set_lvcs(vpgl_lvcs lvcs)                   { lvcs_ = lvcs; }
    void set_blocks(vcl_map<bstm_block_id, bstm_block_metadata> blocks) { blocks_ = blocks; }
    void add_block_metadata(bstm_block_metadata data);
    void set_appearances(vcl_vector<vcl_string> const& appearances){ this->appearances_ = appearances; }

    //: scene path mutators
    void set_xml_path(vcl_string path)              { xml_path_ = path; }
    void set_data_path(vcl_string path)             { data_path_ = path+"/"; }

  private:

    //: world scene information
    vpgl_lvcs               lvcs_;
    vgl_point_3d<double>    local_origin_;
    vgl_point_3d<double>    rpc_origin_;

    //: location on disk of xml file and data/block files
    vcl_string data_path_, xml_path_;

    //: list of block meta data available to this scene
    vcl_map<bstm_block_id, bstm_block_metadata> blocks_;

    //: list of appearance models/observation models used by this scene
    vcl_vector<vcl_string> appearances_;
    int version_;
};


//: utility class for sorting id's by their distance
class bstm_dist_id_pair
{
  public:
  bstm_dist_id_pair(double dist, bstm_block_id id) : dist_(dist), id_(id) {}
    double dist_;
    bstm_block_id id_;

    inline bool operator < (bstm_dist_id_pair const& v) const {
      return dist_ < v.dist_;
    }
};


//Smart_Pointer typedef for bstm_scene
typedef vbl_smart_ptr<bstm_scene> bstm_scene_sptr;
typedef vbl_smart_ptr<bstm_scene_info_wrapper> bstm_scene_info_wrapper_sptr;
//: scene output stream operator
vcl_ostream& operator<<(vcl_ostream &s, bstm_scene& scene);

//: scene xml write function
void x_write(vcl_ostream &os, bstm_scene& scene, vcl_string name);


//--- IO read/write for sptrs--------------------------------------------------
//: Binary write bstm_scene scene to stream
void vsl_b_write(vsl_b_ostream& os, bstm_scene const& scene);
void vsl_b_write(vsl_b_ostream& os, const bstm_scene* &p);
void vsl_b_write(vsl_b_ostream& os, bstm_scene_sptr& sptr);
void vsl_b_write(vsl_b_ostream& os, bstm_scene_sptr const& sptr);

//: Binary load bstm_scene scene from stream.
void vsl_b_read(vsl_b_istream& is, bstm_scene &scene);
void vsl_b_read(vsl_b_istream& is, bstm_scene* p);
void vsl_b_read(vsl_b_istream& is, bstm_scene_sptr& sptr);
void vsl_b_read(vsl_b_istream& is, bstm_scene_sptr const& sptr);

//: Binary write bstm_scene scene to stream
void vsl_b_write(vsl_b_ostream& os, bstm_scene_info_wrapper const& scene);
void vsl_b_write(vsl_b_ostream& os, const bstm_scene_info_wrapper* &p);
void vsl_b_write(vsl_b_ostream& os, bstm_scene_info_wrapper_sptr& sptr);
void vsl_b_write(vsl_b_ostream& os, bstm_scene_info_wrapper_sptr const& sptr);

//: Binary load bstm_scene scene from stream.
void vsl_b_read(vsl_b_istream& is, bstm_scene_info_wrapper &scene);
void vsl_b_read(vsl_b_istream& is, bstm_scene_info_wrapper* p);
void vsl_b_read(vsl_b_istream& is, bstm_scene_info_wrapper_sptr& sptr);
void vsl_b_read(vsl_b_istream& is, bstm_scene_info_wrapper_sptr const& sptr);


#endif // bstm_scene_h_