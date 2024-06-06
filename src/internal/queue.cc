#include "queue.h"

// Constructor
PQueue::PQueue() {
#ifdef DEBUG
    _log("PQueue constructor called");
#endif
    queue.clear();
}

// Destructor
PQueue::~PQueue() {
#ifdef DEBUG
    _log("PQueue destructor called");
#endif
    queue.clear();
}

// Push a ConsensusObj onto the queue
void PQueue::push(message::ConsensusObj &c) {
#ifdef DEBUG
    _log("PQueue::push called");
#endif
    queue.push_back(c);
}

// Pop a ConsensusObj from the queue
message::ConsensusObj PQueue::pop() {
#ifdef DEBUG
    _log("PQueue::pop called");
#endif
    message::ConsensusObj c = queue.front();
    queue.erase(queue.begin());
    return c;
}

// Compare two ConsensusObj objects in the queue using the proxySeqIdLessThan method from Message
bool PQueue::less(Message &m, int i, int j) {
#ifdef DEBUG
    _log("PQueue::less called");
#endif
    return m.proxySeqIdLessThan(queue[i], queue[j]);
}

// Swap two ConsensusObj objects in the queue
void PQueue::swap(int i, int j) {
#ifdef DEBUG
    _log("PQueue::swap called");
#endif
    message::ConsensusObj temp = queue[i];
    queue[i] = queue[j];
    queue[j] = temp;
}

// Return the length of the queue
size_t PQueue::len() {
#ifdef DEBUG
    _log("PQueue::len called");
#endif
    return queue.size();
}