//
//  Alert.cpp
//  Generate ACLs From Snort Alert
//
//  Created by My Nguyen on 6/4/18.
//  Copyright © 2018 My Nguyen. All rights reserved.
//

#include "Alert.hpp"

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
