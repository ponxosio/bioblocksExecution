#include "bioblocksexecution.h"

BioblocksExecution::BioblocksExecution(
        std::shared_ptr<PluginAbstractFactory> pluginFactory,
        std::shared_ptr<UserCommunicationInterface> userComm)
{
    this->pluginFactory = pluginFactory;
    this->userComm = userComm;
    this->running = false;
    this->model = NULL;
    this->actuatorsExecutor = NULL;
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

    model = std::get<0>(modelTuple);
    std::shared_ptr<MappingInterface> mapping = std::get<1>(modelTuple);

    std::shared_ptr<BioBlocksRunningSimulator> simulator = std::make_shared<BioBlocksRunningSimulator>(protocol, logicBlocks);

    userComm->sendUserMessage("starting mapping...");

    std::string erroMsg;
    if (mapping->findRelation(simulator, erroMsg)) {
        userComm->sendUserMessage("mapping done!");

        std::unordered_map<int, std::string> aliasMap = Utils::reverseMap<std::string,int>(machineLoader.getVariableIdMap());
        actuatorsExecutor = std::make_shared<GeneralModelExecutor>(model, mapping, userComm, aliasMap);

        int mainLoopId = logicBlocks->getMainLoopId();
        BioBlocksProtocolExecutor protocolExecutor(protocol, mainLoopId, actuatorsExecutor->getTimer());

        running = true;
        protocolExecutor.executeProtocol(actuatorsExecutor, 0);
        running = false;
    } else {
        userComm->sendUserMessage(erroMsg);
    }
}

void BioblocksExecution::executeNewProtocolSimulateTime(
        const std::string & protocolJSONFile,
        const std::string & machineJSONFile,
        units::Time timeSlice,
        std::shared_ptr<TimeStampSimulator> timestampManager)
{
    BioBlocksTranslator translator(timeSlice, protocolJSONFile);

    std::shared_ptr<LogicBlocksManager> logicBlocks = std::make_shared<LogicBlocksManager>();
    std::shared_ptr<ProtocolGraph> protocol = translator.translateFile(logicBlocks);

    BlocklyFluidicMachineTranslator machineLoader(machineJSONFile, pluginFactory);
    BlocklyFluidicMachineTranslator::ModelMappingTuple modelTuple = machineLoader.translateFile();

    model = std::get<0>(modelTuple);
    std::shared_ptr<MappingInterface> mapping = std::get<1>(modelTuple);

    std::shared_ptr<BioBlocksRunningSimulator> simulator = std::make_shared<BioBlocksRunningSimulator>(protocol, logicBlocks);

    userComm->sendUserMessage("starting mapping...");

    std::string erroMsg;
    if (mapping->findRelation(simulator, erroMsg)) {
        userComm->sendUserMessage("mapping done!");

        std::unordered_map<int, std::string> aliasMap = Utils::reverseMap<std::string,int>(machineLoader.getVariableIdMap());
        actuatorsExecutor = std::make_shared<GeneralModelTimeSimulatedExecution>(model, mapping, userComm, aliasMap, timestampManager);

        int mainLoopId = logicBlocks->getMainLoopId();
        BioBlocksProtocolExecutor protocolExecutor(protocol, mainLoopId, actuatorsExecutor->getTimer());

        running = true;
        protocolExecutor.executeProtocol(actuatorsExecutor, 0);
        running = false;
    } else {
        userComm->sendUserMessage(erroMsg);
    }
}

void BioblocksExecution::stopExecution() {
    if (running) {
        actuatorsExecutor->finishExecution();
        model->stopAllOperations();
    }
}
