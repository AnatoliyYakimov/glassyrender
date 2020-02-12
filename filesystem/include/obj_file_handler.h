//
// Created by Yakimov on 09.11.2019.
//

#ifndef GLASSYRENDER_OBJ_FILE_HANDLER_H
#define GLASSYRENDER_OBJ_FILE_HANDLER_H


#include <vector>
#include "../../include/entities/model_objects/i_object.h"
#include "../../include/entities/model_objects/polygonal_object.h"

using namespace std;
class obj_file_handler {
private:
    vector<vec3f>* vertices =  new vector<vec3f>();
    vector<vec2f>* t_vertices =  new vector<vec2f>();
    vector<vec3f>* n_vertices =  new vector<vec3f>();
    vector<face>* faces =  new vector<face>();

    void parse_face(const vector<string> &strs);

    void parse_v_vertex(const vector<string> &strs);

    void parse_vt_vertex(const vector<string> &strs);

    void parse_vn_vertex(const vector<string> &strs);

    void parse_mtl_library(const vector<string> &strs);

    void parse_face_internal(const vector<string> &vector);

    void triangulate_polygon(const vector<string> &vector);

public:

    obj_file_handler() = default;

    ~obj_file_handler() {
        delete vertices;
        delete n_vertices;
        delete t_vertices;
        delete faces;
    }

    vector<i_object*>* load(const string &file_path);

};


#endif //GLASSYRENDER_OBJ_FILE_HANDLER_H
