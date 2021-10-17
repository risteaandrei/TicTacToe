#include "options.h"

#include "utils.h"

std::ostream& operator<< (std::ostream& out, const Options& options) {
    return out
        << as_integer(options.difficulty) << " "
        << as_integer(options.text_color) << " "
        << as_integer(options.x_color) << " "
        << as_integer(options.o_color) << " ";
}

std::istream& operator>> (std::istream& in, Options& options) {
    unsigned u;

    in >> u;
    options.difficulty = static_cast<Difficulty>(u);

    in >> u;
    options.text_color = static_cast<Color>(u);
    in >> u;
    options.x_color = static_cast<Color>(u);
    in >> u;
    options.o_color = static_cast<Color>(u);

    return in;
}
