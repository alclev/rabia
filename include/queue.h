#pragma once

#include "message.pb.h"
#include "Message.h"  
#include <vector>

class PQueue {
private:
    std::vector<message::ConsensusObj> queue;

public:
    // Constructor
    PQueue();

    // Destructor
    ~PQueue();

    // Member functions
    void push(message::ConsensusObj &c);
    message::ConsensusObj pop();
    bool less(Message &m, int i, int j);
    void swap(int i, int j);
    size_t len();
};
