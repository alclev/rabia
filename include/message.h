#pragma once

#include "message.pb.h"
#include <string>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <sstream>

typedef uint8_t byte;

class Message {
private:
    std::vector<byte> buffer;

public:
    // Constructor
    Message(size_t len);

    // Destructor
    ~Message();

    // Member functions
    std::string getIdSeq(message::ConsensusObj &c);
    bool proxySeqIdEqual(message::ConsensusObj &c1, message::ConsensusObj &c2);
    bool proxySeqIdLessThan(message::ConsensusObj &c1, message::ConsensusObj &c2);

    void buffWrite(const std::vector<byte> &data);
    void buffRead();

    void writeFlush();
    void marshalWriteFlush(message::Command &c);
    void readUnmarshal(message::Command &c);
    void marshalWriteFlush(message::Msg &m);
    void readUnmarshal(message::Msg &m);
};