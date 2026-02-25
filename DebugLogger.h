#pragma once
#include <fstream>
#include <string>
#include <ctime>
#include <shlobj.h>
#include <comdef.h>

class DebugLogger {
public:
    static void log(const std::string& msg) {
        std::ofstream log(getDownloadsPath(), std::ios::app);
        time_t now = time(0);
        log << now << ": " << msg << std::endl;
    }
    
private:
    static std::string getDownloadsPath() {
        PWSTR path = nullptr;
        SHGetKnownFolderPath(FOLDERID_Downloads, 0, nullptr, &path);
        
        std::string downloadsPath = _bstr_t(path);
        downloadsPath += "\\nekosynth_debug.txt";
        
        CoTaskMemFree(path);
        return downloadsPath;
    }
};

#ifdef DEBUG_MODE
    #define DEBUG_LOG(x) DebugLogger::log(x)
#else
    #define DEBUG_LOG(x)
#endif