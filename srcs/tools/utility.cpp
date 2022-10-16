#include "utility.hpp"

namespace ft {

    // renvoie index de la première occurence de to_find dans tab à partir de l'index index
    int	search_vector_char(std::vector<char> tab, const char *to_find, size_t index) {
        std::vector<char>::iterator it = std::search(tab.begin() + index, tab.end(), to_find, to_find + std::strlen(to_find));
        if (it == tab.end())
            return (-1);
        return (it - tab.begin());
    }
}