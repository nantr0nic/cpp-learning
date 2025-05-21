// Messing around and learning how to read binary files

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

int main()
{
    // Open file in binary mode
    std::string inputFile {"testread"};
    std::ifstream ist { inputFile, std::ios::binary };
    if (!ist.is_open())
    {
        throw std::runtime_error("Couldn't open file: " + inputFile);
        return 1;
    }

    // Determine the file size
    ist.seekg(0, std::ios::end);
    std::streamsize fileSize { ist.tellg() };
    ist.seekg(0, std::ios::beg);

    // Allocate a buffer
    std::vector<char> buffer(static_cast<std::size_t>(fileSize));

    // Read the data
    if (ist.read(buffer.data(), fileSize))
    {
        std::cout << "Read " << fileSize << " bytes.\n";
        
    }
    else
    {
        std::cerr << "Failed to read data.\n";
    }

    ist.close();
    return 0;
}