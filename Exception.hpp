#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <string>
#include <exception>
#define BAD_REQUEST_RESPONSE "Bad Request"
#define PERMISSION_DENIED "Permission Denied"
#define NOT_FOUND "Not Found"
#define BAD_COMMENT "Illigal Comment"

class Exception :public std::exception
{
    public:
        virtual std::string what() = 0;
};


class SignUpException : public Exception {
    public:
    std::string what(){
        return BAD_REQUEST_RESPONSE;
    }
};


class LoginException : public Exception {
    public:
    std::string what() {
        return BAD_REQUEST_RESPONSE;
    }
};


class LogoutException : public Exception {
    public:
    std::string what() {
        return PERMISSION_DENIED;
    } 
};


class importProductException : public Exception {
    public:
    std::string what() {
        return PERMISSION_DENIED;
    }
};


class NotFoundException : public Exception {
    public:
    std::string what() {
        return NOT_FOUND;
    }
};


class illigalAccessException : public Exception {
    public:
    std::string what() {
        return PERMISSION_DENIED;
    }
};

class BadRequestException : public Exception {
    public:
    std::string what() {
        return BAD_REQUEST_RESPONSE;
    }
};

class BadCommentException : public Exception {
    public:
    std::string what() {
        return BAD_COMMENT;
    }
};

#endif