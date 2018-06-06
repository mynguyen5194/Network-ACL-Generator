
#include <iostream>
#include <fstream>
//#include <libip>
#include "Alert.hpp"
#include "HashTable.hpp"

using namespace std;

bool parseAlertFile(HashTable<Alert> * alertHashTable, string filePath) {
    ifstream file;
    string line, delimiter = ",";
    string timestamp = "", message = "",
        protocol = "", sourceIP = "", destinationIP = "";
    int signatureID = 0, sourcePort = 0, destinationPort = 0;
    size_t pos = 0;
    Alert alertInfo;
    
    file.open(filePath);
    if (!file) {
        cerr << "Error opening file alert.csv\n";
        return false;
    }
    
    while (getline(file, line)) {
        pos = line.find(delimiter);
        timestamp = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        
        pos = line.find(delimiter);
        signatureID = atoi(line.substr(0, pos).c_str());
        line.erase(0, pos + delimiter.length());
        
        pos = line.find(delimiter);
        message = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        
        pos = line.find(delimiter);
        protocol = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        
        pos = line.find(delimiter);
        sourceIP = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        
        pos = line.find(delimiter);
        sourcePort = atoi(line.substr(0, pos).c_str());
        line.erase(0, pos + delimiter.length());
        
        pos = line.find(delimiter);
        destinationIP = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        
        pos = line.find(delimiter);
        destinationPort = atoi(line.substr(0, pos).c_str());
        line.erase(0, pos + delimiter.length());
        
        alertInfo.setAlert(timestamp, signatureID, message,
            protocol, sourceIP, sourcePort, destinationIP, destinationPort);
        
        alertInfo.printAlert();
        
        alertHashTable->insert(alertInfo);
        
        
    }
    return true;
}

int main(int argc, const char * argv[]) {
    HashTable<Alert> * alertHashTable = new HashTable<Alert>(500);
    
    parseAlertFile(alertHashTable, "/Users/MyNguyen/Desktop/152C/Project/Network\ ACL\ Generator/Network\ ACL\ Generator/alertTest.csv");
    
    return 0;
}
