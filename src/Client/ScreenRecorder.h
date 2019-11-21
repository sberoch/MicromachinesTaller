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

    bool _recording;

    FILE* process = nullptr;

public:
    ScreenRecorder(int wScreen, int hScreen);
    void start();
    bool recording();
    void close();
    ~ScreenRecorder();

private:
    std::string getCommand();
};

#endif // SCREEN_RECORDER_H
