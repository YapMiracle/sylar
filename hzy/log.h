#ifndef __YAP_LOG_H
#define __YAP_LOG_H

#include <iostream>
#include <stdint.h>
#include <memory>
#include <list>
#include <vector>
#include <strstream>
#include <fstream>

namespace YAP {
//日志事件
class LogEvent {
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent();
    const char* getFile() const { return m_file;}
    int32_t getLine() const { return m_line; }
    uint32_t getElapse() const {return m_elapse;}
    uint32_t getThreadId() const { return m_threadId;}
    uint32_t getFiberId() const { return m_fiberId;}
    uint64_t getTime() const { return m_time;}
    const std::string& getContent() const { return m_content;}
private:
    const char *m_file = nullptr; //文件名
    int32_t m_line = 0;           //行号
    uint32_t m_elapse = 0;        //程序启动开始到现在的毫秒数
    uint32_t m_threadId = 0;      //线程id
    uint32_t m_fiberId = 0;       //协程id
    uint64_t m_time = 0;          //事件戳
    std::string m_content;
};

//日志级别
class LogLevel {
public:
    enum Level
    {
        UNKNOW = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };
    static const char* ToString(LogLevel::Level level);
};

// 日志格式器
class LogFormatter {
public:
    LogFormatter(const std::string& pattern);
    typedef std::shared_ptr<LogFormatter> ptr;
    std::string format(std::ostream os, LogLevel::Level level, LogEvent::ptr event);
    void init();
public:
    class FormatItem{
    public:
        typedef std::shared_ptr<FormatItem> ptr;
        virtual ~FormatItem(){}
        virtual std::string format(std::ostream os, LogLevel::Level level,LogEvent::ptr event)=0;
    };
private:
    std::string m_pattern;
    std::vector<LogFormatter::ptr> m_items;
};

//日志输出地
class LogAppender {
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender() {}
    virtual void log(LogLevel::Level level, LogEvent::ptr event) = 0;
    void setFormatter(const LogFormatter::ptr formatter) { m_formatter = formatter;}
    LogFormatter::ptr getFormatter() const { return m_formatter; }
private:
    LogLevel::Level m_level;
    LogFormatter::ptr m_formatter;
};

//日志器
class Logger {
public:
    typedef std::shared_ptr<Logger> ptr;
    Logger(const std::string &name = "root");
    void log(LogLevel::Level level, LogEvent::ptr evnet);

    void debug(LogLevel::Level level,LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    LogLevel::Level getLevel() const {return m_level;}
    void setLevel(LogLevel::Level _level) {m_level = _level;}
private:
    std::string m_name;                     // name
    LogLevel::Level m_level;                // level
    std::list<LogAppender::ptr> m_appenders;// appenders collections
};

class FileLogAppender: public LogAppender{
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const std::string& name);
    void log(LogLevel::Level level, LogEvent::ptr event) override;
    bool reopen();
private:
    std::string m_filename;
    std::ofstream m_filestream;
};

class StdoutLogAppender: public LogAppender{
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    void log(LogLevel::Level level, LogEvent::ptr event) override;
};
} // namesapce YAP

#endif
