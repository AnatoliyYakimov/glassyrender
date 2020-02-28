//
// Created by Yakimov on 09.11.2019.
//

#ifndef GLASSYRENDER_OBJ_FILE_HANDLER_H
#define GLASSYRENDER_OBJ_FILE_HANDLER_H


#include <vector>
#include <math/vec.h>
#include <memory>
#include <objects/polygonal_object.h>

using std::shared_ptr;
using std::vector;
using std::string;

class obj_file_handler {
private:

    static vec3f parse_v_vertex(const vector<string> &strs);

    static vec2f parse_vt_vertex(const vector<string> &strs);

    static vec3f parse_vn_vertex(const vector<string> &strs);

    static void parse_face(const vector<string> &strs, vector<face> &faces);

    static void parse_face_internal(const vector<string> &strs, vector<face> &faces);

    static void triangulate_polygon(const vector<string> &strs, vector<face> &faces);

public:

    static shared_ptr<polygonal_object> load(const string &file_path);

};


#endif //GLASSYRENDER_OBJ_FILE_HANDLER_H
