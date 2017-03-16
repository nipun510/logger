#ifndef _logger_
#define _logger_

#include <fstream>
#include <cassert>
#include <sstream>

class logger;

template<T>
class singleton : private boost::noncopyable
{

public:
	static T & instance()
	{
		boost::call_once(&createInstance, s_once);
		return *s_instance;
	}

protected:
	singleton() {}
	static void createInstance() { s_instance.reset(new T());}
	
private:
	static boost::once_flag s_once;
	static boost::scoped_ptr<T> s_instance;
}

struct log_entry
{
	std::string file;
	int line;
	std::string component;
	boost::posix_time::ptime ts;
	log_entry(){}
	log_entry(const std::string &f, 
			int l,
			const std::string &c,
			boost::posix_time::ptime t,
			const std::string &m):
	file(f), line(l), component(c), ts(t), message(m){}

};



class logger
{
public:
	typedef enum {
    	VERBOSE = 0,
    	DEBUG = 1,
    	INFO,
    	WARNING,
    	ERROR,
    	CRITICAL
    	} logger_level_t;
		
	logger();
	virutal ~logger();
	
	static void set_level(log_level_t level){ instance().m_log_level = level;}
	static void set_file_name(const std::string &name){ instance()._set_file_name(name);}

}
