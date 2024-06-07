#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace constants {
    constexpr int width = 800; ///< Width of the display window.
    constexpr int height = 600; ///< Height of the display window.
    const std::string windowName = "Display"; ///< Name of the display window.
    extern const char *all_class_names[];
}

#endif // CONSTANTS_H