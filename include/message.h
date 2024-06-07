#pragma once

#include <string>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <sstream>

#include "debug.h"
#include "tcp.h"
#include "message.pb.h"

typedef uint8_t byte;

class Message {
private:
    std::vector<byte> buffer;

public:
    /// Constructor
    Message(size_t len);

    // Destructor
    ~Message();

    // Get ID and Sequence as a concatenated string
    std::string getIdSeq(message::ConsensusObj &c);

    // Compare proxy sequence IDs for equality
    bool proxySeqIdEqual(message::ConsensusObj &c1, message::ConsensusObj &c2);

    // Compare proxy sequence IDs for ordering
    bool proxySeqIdLessThan(message::ConsensusObj &c1, message::ConsensusObj &c2);

    // Write data to the buffer
    void buffWrite(const std::vector<byte> &data);

    // Read data from the buffer
    std::vector<byte> buffRead();

    // Write buffer to socket and clear it
    void writeFlush(int sock);

    // Serialize and write Command object to buffer
    void marshalWriteFlush(message::Command &c);

    // Read and unmarshal data into Command object
    void readUnmarshal(message::Command &c);

    // Serialize and write Msg object to buffer
    void marshalWriteFlush(message::Msg &m);

    // Read and unmarshal data into Msg object
    void readUnmarshal(message::Msg &m);
};