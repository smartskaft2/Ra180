#pragma once

#include <string>
#include <sstream>
#include <chrono>

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

	template<> inline
	std::string toString<std::chrono::milliseconds>(const std::chrono::milliseconds& obj)
	{
		std::stringstream ss;
		if (obj.count() % 1000 == 0)
		{
			ss << static_cast<int>(obj.count() / 1000) << "s";
		}
		else
		{
			ss << obj.count() << "ms";
		}
		return ss.str();
	}

} // namespace Ra180 