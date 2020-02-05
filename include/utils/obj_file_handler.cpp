//
// Created by Yakimov on 09.11.2019.
//

#include "obj_file_handler.h"
#include <filesystem>
#include <boost/algorithm/string.hpp>

vector<i_object *> *obj_file_handler::load(const std::string &file_path) {
    //TODO генерировать исключения при некорректном файле
    std::filesystem::path p(file_path);
    std::ifstream is(p);
    vector<i_object*> objects;

    while (!is.eof()) {
        char* str = new char[128];
        is.getline(str, 128, '\n');
        vector<string> strs;
        boost::split(strs, str, boost::is_any_of(" "));
        const string &header = strs[0];
        if (header == "v") {
            parse_v_vertex(strs);
        } else if (header == "vt") {
            parse_vt_vertex(strs);
        } else if (header == "vn") {
            parse_vn_vertex(strs);
        } else if (header == "f") {
            parse_face(strs);
        } else if ("mtllib") {
            parse_mtl_library(strs);
        }
        delete[] str;
    }
    //objects.push_back(new polygonal_object(vertices, t_vertices, faces));
    return nullptr;
}

void obj_file_handler::parse_v_vertex(const vector<string> &strs) {
    vec3f vertex = vec3f{stof(strs[1]), stof(strs[2]), stof(strs[3])};
    vertices->push_back(vertex);
}

void obj_file_handler::parse_vt_vertex(const vector<string> &strs) {
    vec2f vertex_t = vec2f{stof(strs[1]), stof(strs[2])};
    t_vertices->push_back(vertex_t);
}

void obj_file_handler::parse_vn_vertex(const vector<string> &strs) {
    vec3f vertex_n = vec3f{stof(strs[1]), stof(strs[2]), stof(strs[3])};
    n_vertices->push_back(vertex_n);
}

void obj_file_handler::parse_face(const vector<string> &strs) {
    char n = strs.size() - 1;
    switch (n) {
        case 3:
            parse_face_internal(strs);
            break;
        case 4:
            triangulate_polygon(strs);
            break;
    }
}

void obj_file_handler::triangulate_polygon(const vector<string> &strs) {
    vector<string> f1;
    vector<string> f2;
    for (int i = 1; i < 5; ++i) {
        if (i != 4) {
            f1.push_back(strs[i]);
        }
        if (i != 2) {
            f2.push_back(strs[i]);
        }
    }
    parse_face_internal(f1);
    parse_face_internal(f2);
}

void obj_file_handler::parse_face_internal(const vector<string> &strs) {
    face f{};
    auto it = strs.begin();
    if (*it == "f") {
        it++;
    }
    for (int i = 0; it < strs.end(); ++i, ++it) {
        vector<string> face_splited;
        boost::algorithm::split(face_splited, *it, boost::is_any_of("/"));
        f.v[i] = stoi(face_splited[0]);
        f.vt[i] = !face_splited[1].empty() ? stoi(face_splited[1]) : -1;
        f.vn[i] = !face_splited[2].empty() ? stoi(face_splited[2]) : -1;
    }
    faces->push_back(f);
}

void obj_file_handler::parse_mtl_library(const vector<string> &strs) {
    //TODO Not yet implemented
}


