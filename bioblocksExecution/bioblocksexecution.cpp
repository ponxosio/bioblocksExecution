#include "bioblocksexecution.h"

BioblocksExecution::BioblocksExecution(
        std::shared_ptr<PluginAbstractFactory> pluginFactory,
        std::shared_ptr<UserCommunicationInterface> userComm)
{
    this->pluginFactory = pluginFactory;
    this->userComm = userComm;
}

BioblocksExecution::~BioblocksExecution() {

}

void BioblocksExecution::executeNewProtocol(
        const std::string & protocolJSONFile,
        const std::string & machineJSONFile,
        units::Time timeSlice)
{
    BioBlocksTranslator translator(timeSlice, protocolJSONFile);

    std::shared_ptr<LogicBlocksManager> logicBlocks = std::make_shared<LogicBlocksManager>();
    std::shared_ptr<ProtocolGraph> protocol = translator.translateFile(logicBlocks);

    BlocklyFluidicMachineTranslator machineLoader(machineJSONFile, pluginFactory);
    BlocklyFluidicMachineTranslator::ModelMappingTuple modelTuple = machineLoader.translateFile();

    std::shared_ptr<ModelInterface> model = std::get<0>(modelTuple);
    std::shared_ptr<MappingInterface> mapping = std::get<1>(modelTuple);

    std::shared_ptr<BioBlocksRunningSimulator> simulator = std::make_shared<BioBlocksRunningSimulator>(protocol, logicBlocks);

    std::string erroMsg;
    if (mapping->findRelation(simulator, erroMsg)) {

        std::shared_ptr<GeneralModelExecutor> actuatorsExecutor = std::make_shared<GeneralModelExecutor>(model, mapping, userComm);

        int mainLoopId = logicBlocks->getMainLoopId();
        BioBlocksProtocolExecutor protocolExecutor(protocol, mainLoopId, actuatorsExecutor->getTimer());

        protocolExecutor.executeProtocol(actuatorsExecutor, 0);
    } else {
        userComm->sendUserMessage(erroMsg);
    }
}
