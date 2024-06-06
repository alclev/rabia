#include "Message.h"

// Constructor
Message::Message(size_t len) {
    buffer.resize(len);
}

// Destructor
Message::~Message() {
    buffer.clear();
}

// Get ID and Sequence as a concatenated string
std::string Message::getIdSeq(message::ConsensusObj &c) {
    std::stringstream ss;
    ss << c.proid() << "-" << c.proseq();
    return ss.str();
}

// Compare proxy sequence IDs for equality
bool Message::proxySeqIdEqual(message::ConsensusObj &c1, message::ConsensusObj &c2) {
    return c1.proid() == c2.proid() && c1.proseq() == c2.proseq();
}

// Compare proxy sequence IDs for ordering
bool Message::proxySeqIdLessThan(message::ConsensusObj &c1, message::ConsensusObj &c2) {
    return c1.proid() < c2.proid() || (c1.proid() == c2.proid() && c1.proseq() < c2.proseq());
}

// Write data to the buffer
void Message::buffWrite(const std::vector<byte> &data) {
    buffer.insert(buffer.end(), data.begin(), data.end());
}

// Read data from the buffer (implementation pending)
void Message::buffRead() {
    // TODO: Implement buffer reading logic
}

// Flush the buffer (implementation pending)
void Message::writeFlush() {
    // TODO: Implement write flush logic
}

// Marshal write flush for Command (implementation pending)
void Message::marshalWriteFlush(message::Command &c) {
    // TODO: Implement marshal write flush for Command
}

// Read and unmarshal data into Command (implementation pending)
void Message::readUnmarshal(message::Command &c) {
    // TODO: Implement read unmarshal for Command
}

// Marshal write flush for Msg (implementation pending)
void Message::marshalWriteFlush(message::Msg &m) {
    // TODO: Implement marshal write flush for Msg
}

// Read and unmarshal data into Msg (implementation pending)
void Message::readUnmarshal(message::Msg &m) {
    // TODO: Implement read unmarshal for Msg
}