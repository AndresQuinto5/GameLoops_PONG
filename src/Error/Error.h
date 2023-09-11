
#ifndef PONGPROJECT_ERROR_H
#define PONGPROJECT_ERROR_H
#include <string>
namespace Game {

    enum ERROR_TYPE {
        INFO,
        FATAL,
        PANIC
    };


    struct StandardError {
        std::string message;
        ERROR_TYPE errorType;
        std::string caller;
        bool exists;

        StandardError() : errorType(INFO), exists(false) {
        }
    };

    class ErrorSupport {
    public:
        ErrorSupport(StandardError *error, std::string caller);

        std::string name;

        bool errorIsSet();

        void setErrorManager(StandardError* newError);
        void setNewError(std::string error, ERROR_TYPE type);

    protected:
        StandardError *masterError;

    };

    struct AllowError {
        StandardError *error;
        explicit AllowError(StandardError *error) : error(error) {}
    };

    char *getError(ERROR_TYPE type);

} // Game

#endif //PONGPROJECT_ERROR_H
