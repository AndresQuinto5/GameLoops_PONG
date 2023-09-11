#ifndef PONG_OPENGL_CONSOLEMESSAGE_H
#define PONG_OPENGL_CONSOLEMESSAGE_H

#include <string>

enum Color {
    BLACK = 30,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    RESET = 0
};
enum ConsoleLevel {
    ALL,
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
    OFF
};

static struct ConsoleLoggingStruct {

    ConsoleLevel currentConsoleLevel = ALL;
    void setLoggingLevel(ConsoleLevel newLevel) {
        currentConsoleLevel = newLevel;
    }

    ConsoleLevel getConsoleLevel() const {
        return currentConsoleLevel;
    }

    bool passesConsoleLevel(ConsoleLevel level) const {
        return level < currentConsoleLevel;
    }
} ConsoleLogging;
class ConsoleMessage {
public:

    static void TRACE(const std::string &message);
    static void DEBUG(const std::string &message);
    static void INFO(const std::string &message);
    static void WARN(const std::string &message);
    static void ERROR(const std::string &message);
    static void FATAL(const std::string &message);

private:
    static void printMessage(char *level, char *message, Color color, ConsoleLevel lvl);

};


#endif //PONG_OPENGL_CONSOLEMESSAGE_H
