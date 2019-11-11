#ifndef SCREEN_RECORDER_H
#define SCREEN_RECORDER_H

#include <cstdio>
#include <string>

class ScreenRecorder {
private:
    std::string wScreen;
    std::string hScreen;
    std::string outfile;
    std::string framerate;

    FILE* process = nullptr;

public:
    ScreenRecorder(int wScreen, int hScreen);
    void start();
    ~ScreenRecorder();

private:
    std::string getCommand();
};

#endif // SCREEN_RECORDER_H
