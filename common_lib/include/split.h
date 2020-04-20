
#ifndef GLASSYRENDER_SPLIT_H
#define GLASSYRENDER_SPLIT_H

using std::string;
using std::iterator;

template<typename iter_t>
void split(const string &str, iter_t it, char delim) {
    size_t last = 0;
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == delim) {
            *(it++) = str.substr(last, i - last);
            last = i + 1;
        }
    }
}
#endif //GLASSYRENDER_SPLIT_H
