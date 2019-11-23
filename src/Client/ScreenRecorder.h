#ifndef SCREEN_RECORDER_H
#define SCREEN_RECORDER_H

#include <cstdio>
#include <string>
#include "SdlWindow.h"

class ScreenRecorder {
private:
    SdlWindow& window;
    std::string outfile;
    std::string framerate;

    bool _recording;

    FILE* process = nullptr;

public:
    ScreenRecorder(SdlWindow& window);
    void start();
    bool recording();
    void close();
    ~ScreenRecorder();

private:
    std::string getCommand();
};

#endif // SCREEN_RECORDER_H
