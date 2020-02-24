//
// Created by Yakimov on 09.11.2019.
//

#include <objects/obj_file_handler.h>
#include <boost/algorithm/string.hpp>
#include <fstream>

shared_ptr<polygonal_object> obj_file_handler::load(const std::string &file_path) {
    std::ifstream is(file_path);

    if (!is.is_open()) {
        throw std::invalid_argument(file_path);
    }

    vec3f_arr vertices;
    vec3f_arr n_vertices;
    vec2f_arr t_vertices;
    vector<face> faces;

    char* str = new char[128];
    vector<string> strs(5);
    while (!is.eof()) {

        is.getline(str, 128, '\n');

        boost::split(strs, str, boost::is_any_of(" "));
        const string &header = strs[0];
        if (header == "v") {
            vertices.push_back(parse_v_vertex(strs));
        } else if (header == "vt") {
            t_vertices.push_back(parse_vt_vertex(strs));
        } else if (header == "vn") {
            n_vertices.push_back(parse_vn_vertex(strs));
        } else if (header == "f") {
            parse_face(strs, faces);
        }

        strs.clear();
    }
    delete[] str;

    auto obj = new polygonal_object();
    obj->set_vertices(move(vertices));
    obj->set_t_vertices(move(t_vertices));
    obj->set_n_vertices(move(n_vertices));
    obj->set_faces(move(faces));
    return shared_ptr<polygonal_object>(obj);
}

vec3f obj_file_handler::parse_v_vertex(const vector<string> &strs) {
    return vec3f{stof(strs[1]), stof(strs[2]), stof(strs[3])};
}

vec2f obj_file_handler::parse_vt_vertex(const vector<string> &strs) {
    return vec2f{stof(strs[1]), stof(strs[2])};
}

vec3f obj_file_handler::parse_vn_vertex(const vector<string> &strs) {
    return vec3f{stof(strs[1]), stof(strs[2]), stof(strs[3])};
}

void obj_file_handler::parse_face(const vector<string> &strs, vector<face> &faces) {
    char n = strs.size() - 1;
    switch (n) {
        case 3:
            parse_face_internal(strs, faces);
            break;
        case 4:
            triangulate_polygon(strs, faces);
            break;
        default:
            throw std::invalid_argument("Invalid argument while parsing face");
    }
}

void obj_file_handler::triangulate_polygon(const vector<string> &strs, vector<face> &faces) {
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
    parse_face_internal(f1, faces);
    parse_face_internal(f2, faces);
}

void obj_file_handler::parse_face_internal(const vector<string> &strs, vector<face> &faces) {
    face f{};
    auto it = strs.begin();
    if (*it == "f") {
        it++;
    }
    vector<string> face_splited(3);
    for (int i = 0; it < strs.end(); ++i, ++it) {
        boost::algorithm::split(face_splited, *it, boost::is_any_of("/"));
        f.v[i] = stoi(face_splited[0]);
        f.vt[i] = !face_splited[1].empty() ? stoi(face_splited[1]) : 0;
        f.vn[i] = !face_splited[2].empty() ? stoi(face_splited[2]) : 0;
    }
    faces.push_back(f);
}


