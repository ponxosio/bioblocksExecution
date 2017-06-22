#include "consoleusercommunications.h"

ConsoleUserCommunications::ConsoleUserCommunications()
{

}

ConsoleUserCommunications::~ConsoleUserCommunications()
{

}

void ConsoleUserCommunications::sendUserMessage(const std::string & message) {
    std::cout << message;
}

std::string ConsoleUserCommunications::getUserResponse() {
    std::string strRead;
    std::cin >> strRead;
    return strRead;
}
