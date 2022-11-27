#include "log.h"

namespace YAP{

Logger::Logger(const std::string &name)
    :m_name(name){
    
}
void Logger::addAppender(LogAppender::ptr appender){
    m_appenders.push_back(appender);
}
void Logger::delAppender(LogAppender::ptr appender){
    for(auto it=m_appenders.begin();
        it!=m_appenders.end(); it++){
        if(*it==appender){
            m_appenders.erase(it);
            break;
        }
    }
}

void Logger::log(LogLevel::Level level, LogEvent::ptr event){
    if(level < m_level){
        return ;
    }
    for(auto& i: m_appenders){
        i->log(level, event);
    }
}
void Logger::debug(LogEvent::ptr event){
    debug(LogLevel::DEBUG);
}
void Logger::info(LogEvent::ptr event){
    debug(LogLevel::INFO);
}
void Logger::warn(LogEvent::ptr event){
    debug(LogLevel::WARN);
}
void Logger::error(LogEvent::ptr event){
    debug(LogLevel::ERROR);
}
void Logger::fatal(LogEvent::ptr event){
    debug(LogLevel::FATAL);
}
}
