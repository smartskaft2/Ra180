#pragma once

#include <string>
#include <sstream>

namespace Ra180 {

	template<typename T>
	std::string toString(const T& obj)
	{
		std::stringstream ss;
		ss << obj;
		return ss.str();
	}

	template<> inline
	std::string toString<const char*>(const char * const & obj)
	{
		return { obj };
	}

	template<> inline
	std::string toString<std::string>(const std::string& obj)
	{
		return obj;
	}
	 
	template<> inline
	std::string toString<bool>(const bool& obj)
	{
		return { obj ? "true" : "false" };
	}

} // namespace Ra180 