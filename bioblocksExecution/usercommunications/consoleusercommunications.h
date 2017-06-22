#ifndef CONSOLEUSERCOMMUNICATIONS_H
#define CONSOLEUSERCOMMUNICATIONS_H

#include <iostream>

#include "bioblocksExecution/usercommunications/usercommunicationinterface.h"

#include "bioblocksExecution/bioblocksexecution_global.h"

class CONSOLEUSERCOMMUNICATIONS_EXPORT ConsoleUserCommunications : public UserCommunicationInterface
{
public:
    ConsoleUserCommunications();
    virtual ~ConsoleUserCommunications();

    virtual void sendUserMessage(const std::string & message);
    virtual std::string getUserResponse();
};

#endif // CONSOLEUSERCOMMUNICATIONS_H
