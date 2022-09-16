#ifndef TOOLS_HPP
# define TOOLS_HPP

# include <sstream>

namespace ft {

template <typename T1, typename T2>
inline T1 lexical_cast(const T2 &to_cast)
{
	std::ostringstream oss;
	oss << to_cast;
	return oss.str();
}

}; // NAMESPACE FT

#endif
