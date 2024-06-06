#include "queue.h"

// Constructor
PQueue::PQueue() {
    queue.clear();
}

// Destructor
PQueue::~PQueue() {
    queue.clear();
}

// Push a ConsensusObj onto the queue
void PQueue::push(message::ConsensusObj &c) {
    queue.push_back(c);
}

// Pop a ConsensusObj from the queue
message::ConsensusObj PQueue::pop() {
    message::ConsensusObj c = queue.front();
    queue.erase(queue.begin());
    return c;
}

// Compare two ConsensusObj objects in the queue using the proxySeqIdLessThan method from Message
bool PQueue::less(Message &m, int i, int j) {
    return m.proxySeqIdLessThan(queue[i], queue[j]);
}

// Swap two ConsensusObj objects in the queue
void PQueue::swap(int i, int j) {
    message::ConsensusObj temp = queue[i];
    queue[i] = queue[j];
    queue[j] = temp;
}

// Return the length of the queue
size_t PQueue::len() {
    return queue.size();
}