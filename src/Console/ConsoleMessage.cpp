#include "ConsoleMessage.h"
#include <iostream>

void ConsoleMessage::printMessage(char *level, char *message, Color color, ConsoleLevel lvl) {
    if (ConsoleLogging.passesConsoleLevel(lvl)) return;
    std::cout << "\033[" << color << "m" << level << "\033[" << RESET << "m" << message << std::endl;
}


void ConsoleMessage::INFO(const std::string &message) {
    ConsoleMessage::printMessage((char *) "[\tINFO\t]\t", (char *) message.c_str(), GREEN, ConsoleLevel::INFO);
}

void ConsoleMessage::WARN(const std::string &message) {
    ConsoleMessage::printMessage((char *) "[\tWARNING\t]\t", (char *) message.c_str(), YELLOW, ConsoleLevel::WARN);
}

void ConsoleMessage::ERROR(const std::string &message) {
    ConsoleMessage::printMessage((char *) "[\tERROR\t]\t", (char *) message.c_str(), RED, ConsoleLevel::ERROR);
}

void ConsoleMessage::TRACE(const std::string &message) {
    ConsoleMessage::printMessage((char *) "[\tTRACE\t]\t", (char *) message.c_str(), BLUE, ConsoleLevel::TRACE);
}

void ConsoleMessage::DEBUG(const std::string &message) {
    ConsoleMessage::printMessage((char *) "[\tDEBUG\t]\t", (char *) message.c_str(), MAGENTA, ConsoleLevel::DEBUG);
}

void ConsoleMessage::FATAL(const std::string &message) {
    ConsoleMessage::printMessage((char *) "[\tFATAL\t]\t", (char *) message.c_str(), RED, ConsoleLevel::FATAL);
}