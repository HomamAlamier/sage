#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <vector>
#include <fstream>

#define LOG_CHANNELS 100
#define LOG_FORMAT "[%s] (%s) %s@%s : %s\n"
#define LOGGER(CH_NAME, TAG) \
    private: \
    LoggerProxy* _logger = LoggerProxy::makeProxy(#CH_NAME, #TAG);

class Logger
{
public:
    static const char* logFile;
    static const int mainChannel;
    static Logger* system();
    int regChannel(const std::string& name);
    int regChannel(const std::string& name, const std::string& logFile);
    template<typename ...Args>
    void info(int channel, const char* tag, const char* format, Args... args)
    {
        log(channel, "Info", tag, format, args...);
    }
    template<typename ...Args>
    void error(int channel, const char* tag, const char* format, Args... args)
    {
        log(channel, "Error", tag, format, args...);
    }
    template<typename ...Args>
    void warning(int channel, const char* tag, const char* format, Args... args)
    {
        log(channel, "Warning", tag, format, args...);
    }
    template<typename ...Args>
    void critical(int channel, const char* tag, const char* format, Args... args)
    {
        log(channel, "Critical", tag, format, args...);
    }
    template<typename ...Args>
    void debug(int channel, const char* tag, const char* format, Args... args)
    {
#ifndef NDEBUG
        log(channel, "Debug", tag, format, args...);
#endif
    }
private:
    struct LogChannel
    {
        std::string name;
        std::string file;
        void* stream;
    };
    int channelExists(const std::string& s);
    template<typename ...Args>
    void log(int ch, const char* o, const char* t, const char* fmt, Args... args)
    {
        if (ch >= _channels.size() || ch < 0)
            return;
        const LogChannel& c = _channels[ch];
        std::fstream* st = (std::fstream*)c.stream;

        if (!st || st->bad())
            return;

        char textBuffer[4096];
        sprintf(textBuffer, fmt, args...);
        char buffer[sizeof(textBuffer) + 1024];
        int sz = sprintf(buffer, LOG_FORMAT,
                         dateTimeToString().c_str(),
                         o, t, c.name.c_str(), textBuffer);

        st->write(buffer, sz);
        st->flush();
    }
    std::string dateTimeToString();
    std::vector<LogChannel> _channels;
    Logger();
};

class LoggerProxy
{
public:
    static LoggerProxy* makeProxy(int ch, const char* tag);
    static LoggerProxy* makeProxy(const std::string& chname, const char* tag);
    template <typename ...Args>
    void info(const char* format, Args... args)
    {
        Logger::system()->info(_ch, _tag, format, args...);
    }
    template <typename ...Args>
    void error(const char* format, Args... args)
    {
        Logger::system()->error(_ch, _tag, format, args...);
    }
    template <typename ...Args>
    void warning(const char* format, Args... args)
    {
        Logger::system()->warning(_ch, _tag, format, args...);
    }
    template <typename ...Args>
    void critical(const char* format, Args... args)
    {
        Logger::system()->critical(_ch, _tag, format, args...);
    }
    template <typename ...Args>
    void debug(const char* format, Args... args)
    {
        Logger::system()->debug(_ch, _tag, format, args...);
    }
private:
    LoggerProxy(int ch, const char* tag);
    const char* _tag;
    int _ch;
};

#endif // !LOGGER_H
