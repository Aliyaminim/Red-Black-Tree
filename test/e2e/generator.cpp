#include <iostream>
#include <fstream>

int main() {
    
    std::ofstream outputFile; // Create an output file stream
    outputFile.open("tes1t.in");
    
    if (outputFile.is_open()) { // Check if the file was opened successfully
        
        for (int i = 0; i < 100; ++i) {
            int y = (rand() % 100) + 1;
            outputFile << y << " ";
        }
        
        outputFile.close(); // Close the file stream
        std::cout << "Numbers written to the file successfully.\n";
        
    } else {
        std::cerr << "Unable to open the file.\n";
    }

    std::ofstream outputFile1; // Create an output file stream
    outputFile1.open("test.in");
    
    if (outputFile1.is_open()) { // Check if the file was opened successfully
        
        for (int i = 0; i < 100; ++i) {
            int y = (rand() % 100) + 1;
            outputFile1 << y << " ";
        }
        
        outputFile1.close(); // Close the file stream
        std::cout << "Numbers written to the file successfully.\n";
        
    } else {
        std::cerr << "Unable to open the file.\n";
    }
    
    return 0;
}