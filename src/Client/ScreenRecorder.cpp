#include "ScreenRecorder.h"
#include <stdexcept>
#include <iostream>

ScreenRecorder::ScreenRecorder(int wScreen, int hScreen) :
    wScreen(std::to_string(wScreen)),
    hScreen(std::to_string(hScreen)),
    outfile("out.mp4"),
    framerate("25") {}

void ScreenRecorder::start() {
    std::string ffmpeg_command = getCommand();
    std::string remove_command = std::string("rm -f ") + "\"" + outfile + "\"";

    if (std::system(remove_command.c_str()) != 0) {
        throw std::runtime_error("ScreenRecorder: couldn't delete old outfile.");
    }

    process = ::popen(ffmpeg_command.c_str(), "w");
    if (!process) {
        throw std::runtime_error("ScreenRecorder: couldn't open ffmpeg");
    }
}

std::string ScreenRecorder::getCommand() {
    std::string command = "ffmpeg -loglevel quiet";
    std::string video_size = " -video_size " + wScreen + "x" + hScreen;
    std::string framerate_c = " -framerate " + framerate;
    std::string device = " -f x11grab";
    std::string offset = " -i :0.0+0,0";

    return command + video_size + framerate_c + device + offset + " \"" + outfile + "\"";
}

ScreenRecorder::~ScreenRecorder() {
    if (process) {
        char close_signal[] = "q";
        ::fwrite(close_signal, 1, 1, process);
        pclose(process);
    }
}