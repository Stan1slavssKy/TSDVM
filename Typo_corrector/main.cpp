#include "typo_corrector.hpp"

std::string console_input (int argc, char* argv[])
{
    std::string filename;

    if (argc == 2)
        filename = argv[1];
    else if (argc == 1)
        std::cout << "You didn't enter the file name. Please return program and enter file name." << std::endl;
    else
        std::cout << "Error: to few or too many arguments." << std::endl;

    return filename;
}

int main(int argc, char *argv[])
{
    std::string input_pathname = console_input(argc, argv);

    if (input_pathname.empty())
        return -1;

    input_pathname = "../" + input_pathname;

    s1ky::Typo_corrector corrector;
    corrector.start_correcting(input_pathname);

    return 0;
}
