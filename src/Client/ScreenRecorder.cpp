#include "ScreenRecorder.h"
#include <stdexcept>
#include <iostream>

ScreenRecorder::ScreenRecorder(SdlWindow& window) :
    window(window),
    outfile("out.mp4"),
    framerate("40"),
    _recording(false) {}

void ScreenRecorder::start() {
	_recording = true;
    std::string ffmpeg_command = getCommand();
    std::string remove_command = std::string("rm -f ") + "\"" + outfile + "\"";

    if (std::system(remove_command.c_str()) != 0) {
        throw std::runtime_error("Error al borrar el archivo antiguo");
    }

    process = ::popen(ffmpeg_command.c_str(), "w");
    if (!process) {
        throw std::runtime_error("ScreenRecorder: couldn't open ffmpeg");
    }
}

std::string ScreenRecorder::getCommand() {
    int wScreen, hScreen;
    window.getWindowSize(&wScreen, &hScreen);

    std::string command = "ffmpeg";
    std::string video_size = " -video_size " + std::to_string(wScreen) + "x" + std::to_string(hScreen);
    std::string framerate_c = " -framerate " + framerate;
    std::string device = " -f x11grab";
    std::string offset = " -i :0.0+0,0";

    return command + video_size + framerate_c + device + offset + " \"" + outfile + "\"";
}

ScreenRecorder::~ScreenRecorder() {
    if (process) {
        close();
        pclose(process);
    }
}

void ScreenRecorder::close() {
	_recording = false;
	char close_signal[] = "q";
	::fwrite(close_signal, 1, 1, process);
}

bool ScreenRecorder::recording() {
	return _recording;
}
