
#include <iostream>
#include <fstream>
#include <map>
#include "Alert.hpp"

using namespace std;

const string LOCAL_IP = "192.168.4.1";

bool generateACLRule(Alert alert) {
    string rule = "sudo iptables -A ";
    
    if (alert.getSourceIP() == LOCAL_IP || alert.getDestinationIP() == LOCAL_IP) {
        rule += "INPUT ";
    } else {
        rule += "FORWARD ";
    }
    
    rule += "-p " + alert.getProtocol() + " ";
    
    if (alert.getSourcePort() != 0) {
        rule += "--sport " + to_string(alert.getSourcePort()) + " ";
    }
    if (alert.getDestinationPort() != 0) {
        rule += "--dport " + to_string(alert.getDestinationPort()) + " ";
    }
    
    rule += "-s " + alert.getSourceIP() + " -d " + alert.getDestinationIP() + " -j REJECT";
    
    cout << rule << endl;
    
    int res = system(rule.c_str());
    
    if (res != 0) {
        cerr << "Error: fail applying iptables rule\n";
        return false;
    }
    
    return true;
}

bool alertExisted(map<string, Alert> alertMap, string key) {
    size_t pos = key.find("-");
    string part1 = key.substr(0, pos);
    string part2 = key.substr(pos+1, key.length());
    string swappedKey = part2 + "-" + part1;
    
    for (auto it = alertMap.begin(); it != alertMap.end(); ++it) {
        if (key == it->first || swappedKey == it->first) {
            return true;
        }
    }
    
    return false;
}

bool parseAlertFile(map<string, Alert> & alertMap, string filePath) {
    ifstream file;
    string line, delimiter = ",", key;
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
        
        key = sourceIP + "-" + destinationIP;
        
        // Insert new alert if the 2 IP addresses are not in the alertMap
        if (alertExisted(alertMap, key) == false) {
            alertMap.insert(pair<string, Alert> (key, alertInfo));
            generateACLRule(alertInfo);
        }
    }
    return true;
}


int main(int argc, const char * argv[]) {
    map<string, Alert> alertMap;
    
    parseAlertFile(alertMap, "/var/log/snort/alert.csv");
    
    return 0;
}
