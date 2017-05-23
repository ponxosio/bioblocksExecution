#ifndef PROTOCOLRUNNINGSIMULATOR_H
#define PROTOCOLRUNNINGSIMULATOR_H

#include <algorithm>
#include <cstdarg>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include <bioblocksTranslation/logicblocksmanager.h>

#include <protocolGraph/ProtocolGraph.h>
#include <protocolGraph/execution_interface/protocolsimulationinterface.h>
#include <protocolGraph/operables/mathematics/VariableEntry.h>
#include <protocolGraph/operations/controlnode.h>

#include <utils/memento.h>
#include <utils/machineflowstringadapter.h>

class ProtocolRunningSimulator : public ProtocolSimulatorInterface
{
public:
    ProtocolRunningSimulator(std::shared_ptr<ProtocolGraph> protocol,
                             std::shared_ptr<LogicBlocksManager> logicBlocks);

    virtual ~ProtocolRunningSimulator();

    virtual void simulateProtocol(std::shared_ptr<ActuatorsSimulationInterface> executor,int nargs, ...) throw (std::runtime_error);

protected:
    class IfState;

    std::shared_ptr<MachineFlowStringAdapter> machineFlows;
    std::shared_ptr<LogicBlocksManager> logicBlocks;    

    std::unordered_set<int> whilesExecuted;
    std::unordered_map<int, int> ifBranchesExecuted;

    std::unordered_map<int, IfState> ifInitStateMap;
    std::unordered_map<int, IfState> ifMaxDurationStateMap;

    void resetTemporalValues();

    void simulateIf(int nodeId, std::vector<int> & nodes2process);
    void startNewIfSimulation(int nodeId);
    void finishIfSimulation(int nodeId);
    void updateIfDuration(int nodeId);

    void simulateWhile(int nodeId, std::vector<int> & nodes2process);
    void startNewWhileSimulation(int nodeId);
    void finishWhileSimulation(int nodeId);

    void setToActualTime(std::shared_ptr<VariableEntry> varEntry);
    void setToActualTime(const std::vector<std::shared_ptr<VariableEntry>> & varEntry);

    void blockVariables(const std::vector<std::shared_ptr<VariableEntry>> & varEntry);
    void unBlockVariables(const std::vector<std::shared_ptr<VariableEntry>> & varEntry);

    bool hasBeenWritten(const std::vector<std::shared_ptr<VariableEntry>> & varEntry);
    void clearHasBeenWritten(const std::vector<std::shared_ptr<VariableEntry>> & varEntry);
};

class ProtocolRunningSimulator::IfState {
public:
    IfState(){}
    ~IfState(){}

    double time;
    std::shared_ptr<Memento<VariableTable>> varTableState;
    std::shared_ptr<Memento<MachineFlowStringAdapter>> machineFlowState;
};

#endif // PROTOCOLRUNNINGSIMULATOR_H
