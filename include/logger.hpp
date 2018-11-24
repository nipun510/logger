# ifndef LOGGER_HPP
# define LOGGER_HPP


#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <thread>
#include <mutex>

#define INFO(X) info(x)
#define WARN(X) warn(x)
#define ERRROR(X) error(x)


namespace logger
{
	namespace color
	{
		const std::string white("\e[37m");
		const std::string yellow("\e[33m");
		const std::string red("\e[31m");
		const std::string nocolor("\e[0m");
	}

	struct stream
	{
		std::ostream & os;
		bool color;
		stream(std::ostream &os, bool c):os(os), color(c){}
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
		
	public:
		static logger * get_instance()
		{
			if(logger_instance == nullptr)
			{
				std::mutex logger_mutex;
				std::lock_guard<std::mutex> logger_lock(logger_mutex);
				if(logger_instance == nullptr)
				{
					logger_instance = new logger();
				}
			}
			return logger_instance;
		}

		void add_stream(std::ostream &os, bool color)
		{
			streams.emplace_back(stream{os, color});
		}

		template<typename T>
		void stringify(std::stringstream &ss, T t)
		{
			ss << t;
		}

		void stringify(std::stringstream &ss, const level & l)
		{
			ss << l.prefix;
		}

		template<typename T, typename ...Args>
		void stringify(std::stringstream & ss, const T & t, const Args& ...  args)
		{
			stringify(t);
			stringify(ss, args...);
		}

		template<typename... Args>
		std::string stringify(const Args & ... args)
		{
			std::stringstream ss;
			stringify(ss, args...);
			return ss.str();
		}

		
		template<typename... Args>
		void print(const level & l, const Args& ...  args)
		{
		
			std::for_each(streams.begin(), streams.end(), [this, &l, &args...](stream s){
				if(s.color) s.os << l.color;
				s.os << stringify(l);
				s.os << stringify(args...);
			});
		}

		template<typename ...Args>
		void println(const Args& ...  args)
		{
			std::lock_guard<std::mutex> stream_lock(stream_mutex);
			print(args...);
			std::for_each(streams.begin(), streams.end(), [this](stream s){
				s.os << std::endl;
				if(s.color) s.os << color::nocolor;
			});
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

		bool contains_stream() const
		{
			return not streams.empty();
		}

	private:

		logger(){}
		static logger * logger_instance;
		std::vector<stream> streams;

		std::mutex stream_mutex;
		
	};
	logger * logger::logger_instance = nullptr;
}


template<typename... Args>
void info(const Args &... args)
{
	if(not logger::logger::get_instance()->contains_stream()) 
		logger::logger::get_instance()->add_stream(std::cout, true);
	logger::logger::get_instance()->info(args...);

}

template<typename... Args>
void warn(const Args &... args)
{
	if(not logger::logger::get_instance()->contains_stream()) 
		logger::logger::get_instance()->add_stream(std::cout, true);
	logger::logger::get_instance()->warn(args...);

}

template<typename... Args>
void error(const Args &... args)
{
	if(not logger::logger::get_instance()->contains_stream()) 
		logger::logger::get_instance()->add_stream(std::cout, true);
	logger::logger::get_instance()->error(args...);

}
# endif
