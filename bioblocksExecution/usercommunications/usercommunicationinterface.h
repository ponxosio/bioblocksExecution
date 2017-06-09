#ifndef USERCOMMUNICATIONINTERFACE_H
#define USERCOMMUNICATIONINTERFACE_H

#include <string>

class UserCommunicationInterface
{
public:
    virtual ~UserCommunicationInterface(){}

    virtual void sendUserMessage(const std::string & message) = 0;
    virtual std::string getUserResponse() = 0;
};

#endif // USERCOMMUNICATIONINTERFACE_H
