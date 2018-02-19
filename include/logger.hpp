# ifndef LOGGER_HPP
#  define LOGGER_HPP


#include <iostream>
#include <vector>
#include <sstream>

namespace logger
{
	namespace color
	{
		const std::string white("\e[37m");
		const std::string yellow("\e[33m");
		const std::string red("\e[31m");
		const std::string nocolor("\e[0m");
	}

	struct Stream
	{
		std::ostream & os;
		bool color;
		Stream(std::ostream &os, bool c):os(os), color(c){}
	};

	struct level
	{
		std::string prefix;
		std::string color;
		level(const std::string &p, const std::string &c): prefix(p), color(c){}
	};
	namespace log_level
	{
	    const level info("[INFO]", color::white);
		const level warn("[WARN]", color::yellow);
		const level error("[ERROR]", color::red);
	}
	class logger
	{
		std::vector<Stream> streams;
	public:
		void addstream(std::ostream &os, bool color)
		{
			streams.emplace_back(Stream{os, color});
		}

		template<typename T>
		void makeString(std::stringstream &ss, T t)
		{
			ss << t;
		}

		void makestring(std::stringstream &ss, const level & l)
		{
			ss << l.prefix;
		}

		template<typename T, typename ...Args>
		void makeString(std::stringstream & ss, const T & t, const Args& ...  args)
		{
			makeString(t);
			makeString(ss, args...);
		}

		template<typename... Args>
		std::string makeString(const Args & ... args)
		{
			std::stringstream ss;
			makeString(ss, args...);
			return ss.str();
		}



		template<typename... Args>
		void print(const level & l, const Args& ...  args)
		{
			for(auto & stream : streams)
			{
				if(stream.color)
				{
					stream.os << l.color;
				}
				stream.os << l.prefix;
				stream.os << makeString(args...);
				
			}
		}

		template<typename ...Args>
		void println(const Args& ...  args)
		{
			
			print(args...);
			for(auto & stream: streams)
			{
				stream.os << std::endl;
				if(stream.color)
				{
					stream.os << color::nocolor;
				}
				
			}

		}

		template<typename... Args>
		void log(const Args &... args)
		{
			println(log_level::info, args...);
		}

		template<typename... Args>
		void log(const level & l, const Args &... args)
		{
			println(l, args...);
		}

		template<typename... Args>
		void  info(const Args &... args)
		{
			log(args...);
		}

		template<typename... Args>
		void warn(const Args &... args)
		{
			log(log_level::warn, args...);
		}

		template<typename... Args>
		void error(const Args &... args)
		{
			log(log_level::error, args...);
		}
	};
}


# endif