#include "options.h"

#include "utils.h"

std::ostream& operator<< (std::ostream& out, const Options& options) {
    return out
        << as_integer(options.text_color) << " "
        << as_integer(options.x_color) << " "
        << as_integer(options.o_color) << " ";
}

std::istream& operator>> (std::istream& in, Options& options) {
    unsigned color;

    in >> color;
    options.text_color = static_cast<Color>(color);
    in >> color;
    options.x_color = static_cast<Color>(color);
    in >> color;
    options.o_color = static_cast<Color>(color);

    return in;
}
