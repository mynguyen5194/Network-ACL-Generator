
#include "Alert.hpp"

Alert::Alert() {
    Timestamp = "";
    SignatureID = 0;
    Message = "";
    Protocol = "";
    SourceIP = "";
    SourcePort = 0;
    DestinationIP = "";
    DestinationPort = 0;
    Next = NULL;
}

void Alert::setAlert(string timestamp, int signatureID,
              string message, string protocol, string sourceIP,
                     int sourcePort, string destinationIP, int destinationPort) {
    Timestamp = timestamp;
    SignatureID = signatureID;
    Message = message;
    Protocol = protocol;
    SourceIP = sourceIP;
    SourcePort = sourcePort;
    DestinationIP = destinationIP;
    DestinationPort = destinationPort;
}

void Alert::setNext(Alert * next) {
    Next = next;
}

void Alert::setTimestamp(string timestamp) {
    Timestamp = timestamp;
}
void Alert::setSignatureID(int signatureID) {
    SignatureID = signatureID;
}
void Alert::setMessage(string message) {
    Message = message;
}
void Alert::setProtocol(string protocol) {
    Protocol = protocol;
}
void Alert::setSourceIP(string sourceIP) {
    SourceIP = sourceIP;
}
void Alert::setSourcePort(int sourcePort) {
    SourcePort = sourcePort;
}
void Alert::setDestinationIP(string destinationIP) {
    DestinationIP = destinationIP;
}
void Alert::setDestinationPort(int destinationPort) {
    DestinationPort = destinationPort;
}

string Alert::getTimestamp() {
    return Timestamp;
}
int Alert::getSignatureID() {
    return SignatureID;
}
string Alert::getMessage() {
    return Message;
}
string Alert::getProtocol() {
    return Protocol;
}
string Alert::getSourceIP() {
    return SourceIP;
}
int Alert::getSourcePort() {
    return SourcePort;
}
string Alert::getDestinationIP() {
    return DestinationIP;
}
int Alert::getDestinationPort() {
    return DestinationPort;
}
Alert* Alert::getNext() {
    return Next;
}



