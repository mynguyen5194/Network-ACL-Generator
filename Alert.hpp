#ifndef Alert_hpp
#define Alert_hpp

#include <iostream>

using namespace std;

class Alert {
private:
    string Timestamp;
    int SignatureID;
    string Message;
    string Protocol;
    string SourceIP;
    int SourcePort;
    string DestinationIP;
    int DestinationPort;
    Alert * Next;
    
public:
    Alert() {
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
    
    void setAlert(string timestamp, int signatureID,
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
    void setNext(Alert * next) { Next = next; }

    string getTimestamp() { return Timestamp; }
    int getSignatureID() { return SignatureID; }
    string getMessage() { return Message; }
    string getProtocol() { return Protocol; }
    string getSourceIP() { return SourceIP; }
    int getSourcePort() { return SourcePort; }
    string getDestinationIP() { return DestinationIP; }
    int getDestinationPort() { return DestinationPort; }
    Alert * getNext() { return Next; }
    
    void printAlert() {
        cout << Timestamp << " " << SignatureID << " " << Message << " " <<
        Protocol << " " << SourceIP << " " << SourcePort << " " <<
        DestinationIP << " " << DestinationPort << endl;
    }
};

#endif /* Alert_hpp */
