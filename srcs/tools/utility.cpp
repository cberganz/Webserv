#include "utility.hpp"

namespace ft {

    int	search_vector_char(std::vector<char> tab, const char *to_find, size_t index) {
        std::vector<char>::iterator it = std::search(tab.begin() + index, tab.end(), to_find, to_find + std::strlen(to_find));
        if (it == tab.end())
            return (-1);
        return (it - tab.begin());
    }
}