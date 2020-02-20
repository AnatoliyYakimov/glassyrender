//
// Created by Yakimov on 09.11.2019.
//

#ifndef GLASSYRENDER_OBJ_FILE_HANDLER_H
#define GLASSYRENDER_OBJ_FILE_HANDLER_H


#include <vector>
#include <vec.h>
#include <memory>

using std::shared_ptr;
using std::vector;
using std::string;

class obj_file_handler {
private:
    typedef shared_ptr<vec3f_arr> vec3_arrf;
    typedef shared_ptr<vector<vec2f>> vec2_arrf;
    typedef shared_ptr<vector<vec3i>> vec_arri;


    void parse_face(const vector<string> &strs);

    void parse_v_vertex(const vector<string> &strs);

    void parse_vt_vertex(const vector<string> &strs);

    void parse_vn_vertex(const vector<string> &strs);

    void parse_mtl_library(const vector<string> &strs);

    void parse_face_internal(const vector<string> &vector);

    void triangulate_polygon(const vector<string> &vector);

public:
    vec3_arrf vertices;
    vec3_arrf n_vertices;
    vec2_arrf t_vertices;
    vec_arri faces;

    obj_file_handler() :
            vertices(new vec3f_arr()),
            n_vertices(new vec3f_arr()),
            t_vertices(new vector<vec2f>()),
            faces(new vector<vec3i>()) {
    }

    void load(const string &file_path);

};


#endif //GLASSYRENDER_OBJ_FILE_HANDLER_H
