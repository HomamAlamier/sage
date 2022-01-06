#include <logger.h>
#include <loggerproxy.h>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>




const int Logger::mainChannel = 0;
const char* Logger::logFile = "log.txt";

Logger::Logger()
    : _channels()
{
    regChannel("Main");
}

Logger* Logger::system()
{
    static Logger* instance = new Logger();
    return instance;
}

int Logger::channelExists(const std::string &s)
{
    for(size_t i = 0; i < _channels.size(); ++i)
    {
        if (_channels[i].name == s)
        {
            return i;
        }
    }
    return -1;
}

int Logger::regChannel(const std::string &name)
{
    return regChannel(name, logFile);
}

int Logger::regChannel(const std::string &name, const std::string& logFile)
{
    int i = channelExists(name);
    if (i != -1)
        return i;
    LogChannel c;
    c.name = "Main";
    c.file = logFile;
    c.stream = new std::fstream(logFile, std::ios::out);
    _channels.push_back(c);
    return _channels.size();
}

std::string Logger::dateTimeToString()
{
    time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
    return ss.str();
}


LoggerProxy::LoggerProxy(int ch, const char* tag)
    : _ch(ch)
    , _tag(tag)
{}

LoggerProxy* LoggerProxy::makeProxy(int ch, const char* tag)
{
    return new LoggerProxy(ch, tag);
}

LoggerProxy* LoggerProxy::makeProxy(const std::string& chname, const char* tag)
{
    return new LoggerProxy(Logger::system()->regChannel(chname), tag);
}

