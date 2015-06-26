/* 
 * File:   main.cpp
 * Author: patrick
 *
 * Created on June 26, 2015, 6:04 PM
 */


#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <regex>

using namespace std;
void convertToPlist();

/*
 * 
 */
int main(int argc, char** argv) {
    convertToPlist();
    
    ifstream blobPlist;
    blobPlist.open("blobs.plist");
    cout << "opened" << endl;
    string line;
    int dictLevel = 0;
    int lineNumber = 0;
    vector<int> startLines;
    vector<int> endLines;
    vector<int> iOSBuildLines;
    vector<string> iOSBuildStrings;
    bool storeBuildLine = false;
    regex keyRegex ("<key>[A-Z0-9]*</key>");

    while (getline(blobPlist, line)) {
        lineNumber++;
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        if (storeBuildLine) {
            iOSBuildStrings.push_back(line);
            storeBuildLine = false;
        }
        if (line == "</dict>") {
            dictLevel--;
            if (dictLevel == 2) {
                cout << "END at line " << lineNumber << endl;
                endLines.push_back(lineNumber);
            }
        }
        if (line == "<dict>") {
            dictLevel++;
            if (dictLevel == 3) {
                cout << "START at line " << lineNumber << endl;
                startLines.push_back(lineNumber);
            }
        }
        if (regex_match(line, keyRegex) && dictLevel == 1) {
                cout << "KEY at line " << lineNumber << endl;
                iOSBuildLines.push_back(lineNumber);
                
                int buildLength = line.length() - 11;
                
                line = line.substr(5, buildLength);
                
                iOSBuildStrings.push_back(line);
        }

    }
    
    blobPlist.close();
    
    /*Boundaries boundaries [startLines.size()];
    
    for (int i = 0; i < startLines.size(); i++) {
        Boundaries b (startLines[i], endLines[i]);
        boundaries[i] = b;
    }*/
    
    cout << "Done parsing." << endl;
    
    int buildNameAppearances[iOSBuildLines.size()];
    
    for (int i = 0; i < startLines.size(); i++) {
        ifstream in;
        cout << "starting file" << endl;
        const int filesizeInLines = endLines[i] - startLines[i];
        string lines[filesizeInLines];
        in.open("blobs.plist");
        
        //discard lines until reaching the part we want
        for (int j = 0; j < startLines[i]; j++) {
            getline(in, line);
            //cout << "discarded line " << j << endl;
        }
        
        //now get our lines
        for (int j = 0; j < filesizeInLines; j++) {
            getline(in, line);
            lines[j] = line;
            //cout << "got line " << j << endl;
        }
        
        ofstream out;
        
        
        /*for (int j=0; j< iOSBuildStrings.size();j++){
            cout << iOSBuildLines[j] << endl;
        }*/
        
        string filename;
        bool found = false;
        for (int j = 0; !found; j++) {
            //cout << "startline: " << startLines[i] << endl;
            //cout << "buildline: " << iOSBuildLines[j] << endl;
            if (startLines[i] < iOSBuildLines[j]) {
                
                //cout << "FOUND IT";
                
                filename = iOSBuildStrings[j-1];
                
                if (buildNameAppearances[j-1] > 0) {
                    filename += "_";
                    cout << j-1 << endl;
                    cout << "file exists " << buildNameAppearances[j-1] << endl;
                    filename += to_string(buildNameAppearances[j-1]);
                }
                    
                buildNameAppearances[j-1] += 1;
                
                found = true;
                
            }
        }
        
        cout << "FILENAME: " << filename << endl;
        
        out.open(filename += ".shsh");
        
        out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
        out << "<!DOCTYPE plist PUBLIC \"-//Apple Computer//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">" << endl;
        out << "<plist version=\"1.0\">" << endl;
        out << "        <dict>" << endl;
        
        for (int j = 0; j < filesizeInLines; j++){
            out << lines[j] << endl;
        }
        
        out << "</plist>";
        
        in.close();
        
        
    }
    
    return 0;
}

void convertToPlist() {
    system("zcat blobs.shsh > blobs.plist");
    system("perl plutil.pl blobs.plist");
}

