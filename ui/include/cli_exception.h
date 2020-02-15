

#ifndef GLASSYRENDER_CLI_EXCEPTION_H
#define GLASSYRENDER_CLI_EXCEPTION_H

#include <exception>
#include <vector>
#include <string>

using namespace std;


class cli_exception : private exception {
public:
    enum error_code {
        EXIT,
        INVALID_ARGS,
        INVALID_COMMAND,
        OTHER
    };

    const error_code code;

    explicit cli_exception(error_code code) : code(code) {}

    string get_message() {
        string description;
        switch (code) {
            case EXIT:
                description = "User decided to exit";
                break;
            case INVALID_ARGS:
                description = "Invalid arguments for command";
                break;
            case INVALID_COMMAND:
                description = "Invalid command";
                break;
            case OTHER:
                description = what();
        }
        return description;
    }
};

#endif //GLASSYRENDER_CLI_EXCEPTION_H
