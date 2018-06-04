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
    Alert();
    
    void setAlert(string timestamp, int signatureID,
                  string message, string protocol, string sourceIP,
                  int sourcePort, string destinationIP, int destinationPort);
    void setNext(Alert * next);
    void setTimestamp(string timestamp);
    void setSignatureID(int signatureID);
    void setMessage(string message);
    void setProtocol(string protocol);
    void setSourceIP(string sourceIP);
    void setSourcePort(int sourcePort);
    void setDestinationIP(string destinationIP);
    void setDestinationPort(int destinationPort);
    
    string getTimestamp();
    int getSignatureID();
    string getMessage();
    string getProtocol();
    string getSourceIP();
    int getSourcePort();
    string getDestinationIP();
    int getDestinationPort();
    Alert * getNext();
    
};

#endif /* Alert_hpp */
