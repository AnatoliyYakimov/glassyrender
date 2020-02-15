

#ifndef GLASSYRENDER_COMMAND_HANDLER_H
#define GLASSYRENDER_COMMAND_HANDLER_H

#include <ostream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <command.h>

using namespace std;

class command_handler {
private:
    ostream &os;
    istream &is;
public:

    command_handler(ostream &os, istream &is) : os(os), is(is) {}

    void loop() {
        string input;
        vector<string> args;
        const auto predicate = boost::is_any_of(" \t\n");
        const unique_ptr<commands> &cmds = command::registry;
        while (true) {
            is >> input;
            if (input.empty()) {
                break;
            }
            boost::algorithm::split(args, input, predicate);
            const string &signature = *args.begin();
            for (command *cmd : *cmds) {
                if (cmd->is_signature(signature)) {
                    cmd->exec(args, os);
                    break;
                }
            }
        }
    }
};


#endif //GLASSYRENDER_COMMAND_HANDLER_H
