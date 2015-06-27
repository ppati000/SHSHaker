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
    string line;
    int dictLevel = 0, lineNumber = 0;
    vector<int> startLines, endLines, iOSBuildLines;
    vector<string> iOSBuildStrings;
    regex keyRegex ("<key>[A-Z0-9]*</key>");

    while (getline(blobPlist, line)) {
        
        lineNumber++;
        
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        if (line == "</dict>") {
            dictLevel--;
            if (dictLevel == 2) {
                cout << "END at line " << lineNumber << endl;
                endLines.push_back(lineNumber);
            }
        }
        else if (line == "<dict>") {
            dictLevel++;
            if (dictLevel == 3) {
                cout << "START at line " << lineNumber << endl;
                startLines.push_back(lineNumber);
            }
        }
        else if (regex_match(line, keyRegex) && dictLevel == 1) {
                cout << "Build key at line " << lineNumber << endl;
                iOSBuildLines.push_back(lineNumber);
                
                /* check how long the build number is. <key></key> are 11 chars.
                 * so we need to subtract 11 to get the build number's length */
                int buildLength = line.length() - 11;
                //extract the build number
                line = line.substr(5, buildLength);
                
                iOSBuildStrings.push_back(line);
        }

    }
    
    blobPlist.close();
    
    cout << "Done parsing." << endl;
    cout << "startLines.size(): " << startLines.size() << endl;
    cout << "endLines.size(): " << endLines.size() << endl;
    cout << "iOSBuildLines.size(): " << iOSBuildLines.size() << endl;
    cout << "iOSBuildStrings.size(): " << iOSBuildStrings.size() << endl;
    
    vector<int> buildNameAppearances(iOSBuildLines.size());
    for (int i = 0; i < startLines.size(); i++) {
        
        cerr << "I IS " << i << endl;
        
        int currentStartLine = startLines.at(i);
        
        ifstream in;
        cout << "starting file" << endl;
        const int filesizeInLines = endLines.at(i) - currentStartLine;
        vector<string> lines (filesizeInLines);
        in.open("blobs.plist");
        
        //discard lines until reaching the part we want
        for (int j = 0; j < currentStartLine; j++) {
            getline(in, line);
            //cout << "discarded line " << j << endl;
        }
        
        //now get our lines
        for (int j = 0; j < filesizeInLines; j++) {
            getline(in, line);
            lines.push_back(line);
        }
        
        ofstream out;
        string filename;
        bool found = false;
        for (int j = 0; !found; j++) {
            //cout << "startline: " << startLines[i] << endl;
            //cout << "buildline: " << iOSBuildLines[j] << endl;
            if (/*j == iOSBuildLines.size() || */currentStartLine < iOSBuildLines.at(j)) {
                
                filename = iOSBuildStrings.at(j-1);
                
                if (buildNameAppearances.at(j-1) > 0) {
                    filename += "_";
                    cout << "file exists " << buildNameAppearances.at(j-1) << endl;
                    cout << "build number index: " << j-1 << endl;
                    cout << "build number: " << iOSBuildStrings.at(j-1) << endl;
                    filename += to_string(buildNameAppearances.at(j-1));
                }
                    
                buildNameAppearances.at(j-1) += 1;
                
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
            out << lines.at(j) << endl;
        }
        
        out << "</plist>";
        
        in.close();
        out.close();
        
    }
    
    return 0;
}

void convertToPlist() {
    system("zcat blobs.shsh > blobs.plist");
    system("perl plutil.pl blobs.plist");
}

