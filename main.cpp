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
#include <sstream>

using namespace std;
string convertToPlist();

/*
 * 
 */
int main(int argc, char** argv) {
    
    string plistFilename = convertToPlist();
    
    ifstream blobPlist;
    blobPlist.open(plistFilename);
    string line;
    int dictLevel = 0, lineNumber = 0;
    vector<int> startLines, endLines, iOSBuildLines;
    vector<string> iOSBuildStrings;
    regex keyRegex ("<key>[A-Z0-9]*</key>");
    
    cout << "Parsing " << plistFilename  << endl;

    while (getline(blobPlist, line)) {
        
        lineNumber++;
        
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        if (line == "</dict>") {
            dictLevel--;
            if (dictLevel == 2) {
                //cout << "END at line " << lineNumber << endl;
                endLines.push_back(lineNumber);
            }
        }
        else if (line == "<dict>") {
            dictLevel++;
            if (dictLevel == 3) {
                //cout << "START at line " << lineNumber << endl;
                startLines.push_back(lineNumber);
            }
        }
        else if (regex_match(line, keyRegex) && dictLevel == 1) {
                //cout << "Build key at line " << lineNumber << endl;
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
    cout << "DEBUG INFORMATION:" << endl;
    cout << "startLines.size(): " << startLines.size() << endl;
    cout << "endLines.size(): " << endLines.size() << endl;
    cout << "iOSBuildLines.size(): " << iOSBuildLines.size() << endl;
    cout << "iOSBuildStrings.size(): " << iOSBuildStrings.size() << endl;
    
    vector<int> buildNameAppearances;
    
    for (int i = 0; i < iOSBuildStrings.size(); i++) {
        buildNameAppearances.push_back(0);
    }
    
    for (int i = 0; i < startLines.size(); i++) {
        
        cout << "Starting file " << i << endl;
        
        int currentStartLine = startLines.at(i);
        
        ifstream in;
        const int filesizeInLines = endLines.at(i) - currentStartLine;
        vector<string> lines;
        in.open(plistFilename);
        
        //discard lines until reaching the part we want
        for (int j = 0; j < currentStartLine; j++) {
            getline(in, line);
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
            if ( ( j == iOSBuildLines.size() ) || ( currentStartLine < iOSBuildLines.at(j)) ) { 
                
                filename = iOSBuildStrings.at(j-1);
                
                if (buildNameAppearances.at(j-1) > 0) {
                    filename += "_";
                    cout << "file exists " << buildNameAppearances.at(j-1) << endl;
                    cout << "build number: " << iOSBuildStrings.at(j-1) << endl;
                    stringstream ss;
                    ss << buildNameAppearances.at(j - 1);
                    string str = ss.str();
                    filename += str;
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
        
        for (int j = 0; j < lines.size(); j++){
            out << lines.at(j) << endl;
        }
        
        out << "</plist>";
        
        in.close();
        out.close();
        
    }
    
    return 0;
}

string convertToPlist() {
    
    string plistFilename;
    
#if defined(__CYGWIN__) || defined(_WIN32)
    cout << "Executing ./7za.exe e blobs.shsh -y" << endl;
    int zcat = system("7za.exe e blobs.shsh -y");
    plistFilename = "blobs";
#else
    cout << "Executing zcat blobs.shsh > blobs.plist" << endl;
    int zcat = system("zcat blobs.shsh > blobs.plist");
    plistFilename = "blobs.plist";
#endif
    
    if ( zcat != 0 ) {
        cerr << "Error while running zcat (code " << zcat << ")" << endl
                << "Please make sure to place your SHSH file from TinyUmbrella " 
                << "in the same directory as the executable and rename it to "
                << "blobs.shsh :) Or ask for help on twitter.com/ppati000" 
                << endl;
        exit (EXIT_FAILURE);
        
    }
    
    cout << "Executing perl plutil.pl blobs.plist > zcat.log" << endl;
    
#if defined(__linux__)
    int perl = system((string("perl plutil.pl ") + plistFilename
                + string(" > plutil.log")).c_str());
#elif __APPLE__
    int perl = system("plutil -convert xml1 blobs.plist");
#elif defined(__CYGWIN__) || defined(_WIN32)
    cout << "Executed 7za, no need for plutil." << endl;
    int perl = 0;
#else
    #error "Could not detect OS X or Linux. Other systems are not supported."
#endif

    if ( perl != 0) {
        cerr << "Error while running zcat (code " << perl << ")" << endl <<
                "Please make sure perl is installed on your computer." << 
                "To do this on Ubuntu, run: sudo apt-get install -y perl" << 
                endl << "Or ask for help on twitter.com/ppati000";
        exit (EXIT_FAILURE);
    }
    
    cout << "Done executing commands." << endl;
    
    return plistFilename;
}

