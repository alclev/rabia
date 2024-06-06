#include "ledger.h"

Ledger::Ledger(){
#ifdef DEBUG
    _log("Ledger constructor called");
#endif
    
}

Ledger::~Ledger(){
#ifdef DEBUG
    _log("Ledger destructor called");
#endif
}

void Ledger::reset(){
#ifdef DEBUG
    _log("Ledger::reset called");
#endif
}

void Ledger::incrPhaseDecRound(){
#ifdef DEBUG
    _log("Ledger::incrPhaseDecRound called");
#endif
}

message::ConsensusObj Ledger::setMyProposal(message::ConsensusObj &p){
#ifdef DEBUG
    _log("Ledger::setMyProposal called");
#endif
}

message::ConsensusObj Ledger::getMyProposal(){
#ifdef DEBUG
    _log("Ledger::getMyProposal called");
#endif
}

void Ledger::putrecvProposals(message::ConsensusObj &p){
#ifdef DEBUG
    _log("Ledger::putrecvProposals called");
#endif
}

void Ledger::sortRecvProposals(){
#ifdef DEBUG
    _log("Ledger::sortRecvProposals called");
#endif
}

message::ConsensusObj Ledger::recvProposalsMajV(){
#ifdef DEBUG
    _log("Ledger::recvProposalsMajV called");
#endif
}

int Ledger::recvProposalsMajT(){
#ifdef DEBUG
    _log("Ledger::recvProposalsMajT called");
#endif
}

void Ledger::setMyBCMsgs(uint32_t phase, uint32_t round, uint32_t x){
#ifdef DEBUG
    _log("Ledger::setMyBCMsgs called");
#endif
}

uint32_t Ledger::getMyBCMsgs(uint32_t phase, uint32_t round){
#ifdef DEBUG
    _log("Ledger::getMyBCMsgs called");
#endif
}

void Ledger::putRecvBCMsgs(uint32_t phase, uint32_t round){
#ifdef DEBUG
    _log("Ledger::putRecvBCMsgs called");
#endif
}

uint32_t Ledger::recvBCMsgsMajV(uint32_t phase, uint32_t round){
#ifdef DEBUG
    _log("Ledger::recvBCMsgsMajV called");
#endif
}

int Ledger::recvBCMsgsMajT(uint32_t phase, uint32_t round){
#ifdef DEBUG
    _log("Ledger::recvBCMsgsMajT called");
#endif
}

int Ledger::getRecvBCMsgsT(uint32_t phase, uint32_t round){
#ifdef DEBUG
    _log("Ledger::getRecvBCMsgsT called");
#endif
}

bool Ledger::hasEnoughMsg(uint32_t phase, uint32_t round){
#ifdef DEBUG
    _log("Ledger::hasEnoughMsg called");
#endif
}

