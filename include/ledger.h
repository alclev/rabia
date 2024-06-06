#include "message.pb.h"
#include <mutex>
#include <vector>
#include <cstdint>

struct Tally{
    message::ConsensusObj proposal;
    int count;
};

struct Slot{
    uint32_t term;
    std::mutex lock;
    bool isDone;
    bool hasRecvDec;
    message::ConsensusObj decision;
    // TODO Queue
    uint32_t phase;
    uint32_t round;
    message::ConsensusObj myProposal;
    std::vector<Taly> recvProposals;
    std::vector<std::vector<uint32_t>> myBCMsgs;
    std::vector<std::vector<std::vector<int>>> recvBCMsgs;
    std::vector<std::vector<int>> recvBCMsgsT;
}

class Ledger{
    private:
        std::vector<Slot> slots;
    public:
        void reset();
        void incrPhaseDecRound();
        message::ConsensusObj setMyProposal(message::ConsensusObj &p);
        message::ConsensusObj getMyProposal();
        void putrecvProposals(message::ConsensusObj &p);
        void sortRecvProposals();
        message::ConsensusObj recvProposalsMajV();
        int recvProposalsMajT();
        void setMyBCMsgs(uint32_t phase, uint32_t round, uint32_t x);
        uint32_t getMyBCMsgs(uint32_t phase, uint32_t round);
        void putRecvBCMsgs(uint32_t phase, uint32_t round);
        uint32_t recvBCMsgsMajV(uint32_t phase, uint32_t round);
        int recvBCMsgsMajT(uint32_t phase, uint32_t round);
        int getRecvBCMsgsT(uint32_t phase, uint32_t round);
        bool hasEnoughMsg(uint32_t phase, uint32_t round);
};