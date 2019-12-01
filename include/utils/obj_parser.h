//
// Created by Yakimov on 09.11.2019.
//

#ifndef GLASSYRENDER_OBJ_PARSER_H
#define GLASSYRENDER_OBJ_PARSER_H


#include <vector>
#include "../entities/model_objects/i_object.h"

class obj_parser {
public:
    std::vector<i_object*> parse(std::string file_path);
protected:
    std::string get_path(std::string file_path);
};


#endif //GLASSYRENDER_OBJ_PARSER_H
