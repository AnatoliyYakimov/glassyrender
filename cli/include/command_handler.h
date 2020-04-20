

#ifndef GLASSYRENDER_COMMAND_HANDLER_H
#define GLASSYRENDER_COMMAND_HANDLER_H

#include <ostream>
#include <iostream>
#include <command.h>
#include <split.h>

using std::istream;
using std::ostream;
using std::string;
using std::unique_ptr;

class command_handler {
private:
    ostream &os;
    istream &is;
public:

    command_handler(ostream &os, istream &is) : os(os), is(is) {}

    void loop() {
        char input[512];
        vector<string> args;
        const unique_ptr<commands> &cmds = command::registry;
        while (true) {
            os << "\n$:> ";
            os.flush();
            is.getline(input, 512, '\n');
            split(input, args.begin(), ' ');
            const string &signature = *args.begin();
            for (command *cmd : *cmds) {
                if (cmd->is_signature(signature)) {
                    try {
                        cmd->exec(args, os);
                    } catch (std::exception &e) {
                        string msg = e.what();
                        os << "Exception: \"" << msg << "\"";
                    }
                    os.flush();
                    break;
                }
            }
        }
    }
};


#endif //GLASSYRENDER_COMMAND_HANDLER_H
