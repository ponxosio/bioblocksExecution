#ifndef BIOBLOCKSEXECUTION_H
#define BIOBLOCKSEXECUTION_H

#include <memory>
#include <string>

#include <commonmodel/plugininterface/pluginabstractfactory.h>

#include <bioblocksTranslation/bioblockstranslator.h>
#include <bioblocksTranslation/logicblocksmanager.h>

#include <blocklyFluidicMachineTranslator/blocklyfluidicmachinetranslator.h>

#include <utils/timestampsimulator.h>

#include "bioblocksExecution/bioblocksSimulation/bioblocksrunningsimulator.h"

#include "bioblocksExecution/protocolexecution/bioblocksprotocolexecutor.h"
#include "bioblocksExecution/protocolexecution/generalmodelexecutor.h"
#include "bioblocksExecution/protocolexecution/generalmodeltimesimulatedexecution.h"

#include "bioblocksExecution/usercommunications/usercommunicationinterface.h"

#include "bioblocksexecution_global.h"

class BIOBLOCKSEXECUTIONSHARED_EXPORT BioblocksExecution
{
public:
    BioblocksExecution(std::shared_ptr<PluginAbstractFactory> pluginFactory,
                       std::shared_ptr<UserCommunicationInterface> userComm);
    virtual ~BioblocksExecution();

    void executeNewProtocol(const std::string & protocolJSONFile, const std::string & machineJSONFile, units::Time timeSlice);

    void executeNewProtocolSimulateTime(const std::string & protocolJSONFile,
                                        const std::string & machineJSONFile,
                                        units::Time timeSlice,
                                        std::shared_ptr<TimeStampSimulator> timestampManager);

    void stopExecution();

protected:
    volatile bool running;
    std::shared_ptr<PluginAbstractFactory> pluginFactory;
    std::shared_ptr<UserCommunicationInterface> userComm;
    std::shared_ptr<ModelInterface> model;
    std::shared_ptr<GeneralModelExecutor> actuatorsExecutor;
};

#endif // BIOBLOCKSEXECUTION_H
