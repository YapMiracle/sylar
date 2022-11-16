#ifndef __SYLAR_LOG_H
#define __SYLAR_LOG_H

#include <iostream>
#include <stdint.h>
#include <memory>

namespace sylar
{
    //日志事件
    class LogEvent
    {
    public:
        typedef std::shared_ptr<LogEvent> ptr;
        LogEvent();

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
    class LogLevel
    {
    public:
        enum Level
        {
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROE = 4,
            FATAL = 5
        };
    };

    // 日志格式器
    class LogFormatter
    {
    public:
        typedef std::shared_ptr<LogFormatter> ptr;
        std::string format(LogEvent::ptr event);

    private:
    };

    //日志输出地
    class LogAppender
    {
    public:
        typedef std::shared_ptr<LogAppender> ptr;
        virtual ~LogAppender() {}
        void log(LogLevel::Level level, LogEvent::ptr evnet)
        {
        }

    private:
    };

    //日志器
    class Logger
    {
    public:
        typedef std::shared_ptr<Logger> ptr;
        Logger(const std::string &name = "root");
        void log(LogLevel::Level level, LogEvent::ptr evnet);

    private:
    };
}

#endif
