#include "Message.h"

// Constructor
Message::Message(size_t len) {
#ifdef DEBUG
    _log("Message constructor called");
#endif
    buffer.resize(len);
}

// Destructor
Message::~Message() {
#ifdef DEBUG
    _log("Message destructor called");
#endif
    buffer.clear();
}

// Get ID and Sequence as a concatenated string
std::string Message::getIdSeq(message::ConsensusObj &c) {
#ifdef DEBUG
    _log("Message::getIdSeq called");
#endif
    std::stringstream ss;
    ss << c.proid() << "-" << c.proseq();
    return ss.str();
}

// Compare proxy sequence IDs for equality
bool Message::proxySeqIdEqual(message::ConsensusObj &c1, message::ConsensusObj &c2) {
#ifdef DEBUG
    _log("Message::proxySeqIdEqual called");
#endif
    return c1.proid() == c2.proid() && c1.proseq() == c2.proseq();
}

// Compare proxy sequence IDs for ordering
bool Message::proxySeqIdLessThan(message::ConsensusObj &c1, message::ConsensusObj &c2) {
#ifdef DEBUG
    _log("Message::proxySeqIdLessThan called");
#endif
    return c1.proid() < c2.proid() || (c1.proid() == c2.proid() && c1.proseq() < c2.proseq());
}

// Write data to the buffer
void Message::buffWrite(const std::vector<byte> &data) {
#ifdef DEBUG
    _log("Message::buffWrite called");
#endif
    buffer.insert(buffer.end(), data.begin(), data.end());
}

// Read data from the buffer (implementation pending)
void Message::buffRead() {
#ifdef DEBUG
    _log("Message::buffRead called");
#endif
    // TODO: Implement buffer reading logic
}

// Flush the buffer (implementation pending)
void Message::writeFlush() {
#ifdef DEBUG
    _log("Message::writeFlush called");
#endif
    // TODO: Implement write flush logic
}

// Marshal write flush for Command (implementation pending)
void Message::marshalWriteFlush(message::Command &c) {
#ifdef DEBUG
    _log("Message::marshalWriteFlush called");
#endif
    // TODO: Implement marshal write flush for Command
}

// Read and unmarshal data into Command (implementation pending)
void Message::readUnmarshal(message::Command &c) {
#ifdef DEBUG
    _log("Message::readUnmarshal called");
#endif
    // TODO: Implement read unmarshal for Command
}

// Marshal write flush for Msg (implementation pending)
void Message::marshalWriteFlush(message::Msg &m) {
#ifdef DEBUG
    _log("Message::marshalWriteFlush called");
#endif
    // TODO: Implement marshal write flush for Msg
}

// Read and unmarshal data into Msg (implementation pending)
void Message::readUnmarshal(message::Msg &m) {
#ifdef DEBUG
    _log("Message::readUnmarshal called");
#endif
    // TODO: Implement read unmarshal for Msg
}