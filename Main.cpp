#include <iostream>
#include <string>
#include <Windows.h> // Include the Windows header for ChangeDisplaySettings

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <executable_name>" << std::endl;
        return 1;
    }

    // Get the name of the executable to run
    std::string executableName = argv[1];

    DEVMODE devmode;
    devmode.dmPelsWidth = 640;
    devmode.dmPelsHeight = 480;
    devmode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
    devmode.dmSize = sizeof(DEVMODE);

    long result = ChangeDisplaySettings(&devmode, 0);

    if (result == DISP_CHANGE_SUCCESSFUL) {
        std::cout << "Display settings changed successfully." << std::endl;
    } else if (result == DISP_CHANGE_RESTART) {
        std::cout << "You need to restart your computer to apply the changes." << std::endl;
        return 1;
    } else {
        std::cerr << "Failed to change display settings." << std::endl;
        return 1;
    }

    std::string command = executableName + " " + executableName; // Pass the executable name as an argument
    int exitCode = system(command.c_str());

    // Reset display settings to the original state
    ChangeDisplaySettings(NULL, 0);

    return exitCode;
}
