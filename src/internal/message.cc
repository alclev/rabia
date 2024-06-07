#include "message.h"
#include "debug.h"
#include "tcp.h"
#include "message.pb.h"

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

// Read data from the buffer
std::vector<byte> Message::buffRead() {
#ifdef DEBUG
    _log("Message::buffRead called");
#endif
    return buffer;
}

// Write buffer to socket and clear it
void Message::writeFlush(int sock) {
#ifdef DEBUG
    _log("Message::writeFlush called");
#endif
    /* write buffer to socket */
    client_tcp::send(sock, buffer);
    buffer.clear();
}

// Serialize and write Command object to buffer
void Message::marshalWriteFlush(message::Command &c) {
#ifdef DEBUG
    _log("Message::marshalWriteFlush called");
#endif
    /* serialize command object using protobuf */
    std::string serialized;
    if(c.SerializeToString(&serialized)) {
        std::vector<byte> data(serialized.begin(), serialized.end());
        buffWrite(data);
    } else {
        _err("Failed to serialize Command object");
    }
}

// Read and unmarshal data into Command object
void Message::readUnmarshal(message::Command &c) {
#ifdef DEBUG
#endif
    /* read data from buffer */
    std::vector<byte> data = buffRead();
    std::string serialized(data.begin(), data.end());
    if(!c.ParseFromString(serialized)) {
        _err("Failed to parse Command object");
    }
}

// Serialize and write Msg object to buffer
void Message::marshalWriteFlush(message::Msg &m) {
#ifdef DEBUG
    _log("Message::marshalWriteFlush called");
#endif
    /* serialize message object using protobuf */
    std::string serialized;
    if(m.SerializeToString(&serialized)) {
        std::vector<byte> data(serialized.begin(), serialized.end());
        buffWrite(data);
    } else {
        _err("Failed to serialize Msg object");
    }
}

// Read and unmarshal data into Msg object (implementation pending)
void Message::readUnmarshal(message::Msg &m) {
#ifdef DEBUG
    _log("Message::readUnmarshal called");
#endif
    /* read data from buffer */
    std::vector<byte> data = buffRead();
    std::string serialized(data.begin(), data.end());
    if(!m.ParseFromString(serialized)) {
        _err("Failed to parse Msg object");
    }
}