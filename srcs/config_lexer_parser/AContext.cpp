#include "AContext.hpp"

bool AContext::keywordExistsInContext(const std::string *context, const std::string &keyword)
{
	for (int i = 0 ; not context[i].empty() ; i++)
	{
		if (context[i] == keyword)
			return true;
	}
	return false;
}
