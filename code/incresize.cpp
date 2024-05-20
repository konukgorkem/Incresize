#include <iostream>
#include <fstream>
#include <sstream> // Include the <sstream> header for istringstream
#include <string>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <windows.h> // Include the <Windows.h> header for GetCurrentDirectory
#elif __linux__
#include <unistd.h> // Include the <unistd.h> header for getcwd
#endif

using namespace std;

// Function to generate and write random binary data directly to file
void write_random_binary_data_to_file(long long size, const string& filename) {
    ofstream file(filename.c_str(), ios::out | ios::binary);
    if (!file) {
        cerr << "Error creating file." << endl;
        exit(1);
    }

    // Randomly generate 0s and 1s
    for (long long i = 0; i < size; ++i) {
        char bit = rand() % 2 + '0'; // Random bit (either '0' or '1')
        file.write(&bit, sizeof(char));
        if (!file) {
            cerr << "Error writing to file." << endl;
            exit(1);
        }
    }

    file.close();
}

// Function to write user-provided text directly to file
void write_text_to_file(const string& text, long long size, const string& filename) {
    ofstream file(filename.c_str());
    if (!file) {
        cerr << "Error creating file." << endl;
        exit(1);
    }

    long long totalBytesWritten = 0;
    while (totalBytesWritten < size) {
        long long bytesToWrite = min(size - totalBytesWritten, static_cast<long long>(text.size()));
        file.write(text.c_str(), bytesToWrite);
        if (!file) {
            cerr << "Error writing to file." << endl;
            exit(1);
        }
        totalBytesWritten += bytesToWrite;
    }

    file.close();
}

int main() {
    srand(time(nullptr)); // Seed for random number generation

    string input;
    long long fileSize; // Using long long for larger file sizes
    int modeChoice;
    int sizeMode;
    string exeFileName;
    string combinedFileName;

    //ASCII ART
    cout << " _                     ____  _         " << endl;
    cout << "(_)_ __   ___ _ __ ___/ ___|(_)_______ " << endl;
    cout << "| | '_ \\ / __| '__/ _ \\___ \\| |_  / _ \\" << endl;
    cout << "| | | | | (__| | |  __/___) | |/ /  __/" << endl;
    cout << "|_|_| |_|\\___|_|  \\___|____/|_/___\\___|" <<endl;
    cout << "      .exe size increaser tool"<<endl;
    cout << "---------------------------------------"<<endl<<endl;


    //END OF ASCII ART    

    cout << "1. Lorem ipsum mode" << endl;
    cout << "2. Binary mode" << endl;
    cout << "3. Custom mode" << endl<<endl;

    // Loop until the user enters a valid choice
    while (true) {
        cout << "Please enter your mode: ";
        cin >> modeChoice;

        // Validate mode choice
        if (modeChoice == 1 || modeChoice == 2 || modeChoice == 3) {
            break; // Exit the loop if the choice is valid
        } else {
            cout << "Invalid choice. Please enter either 1, 2, or 3." << endl;
        }
    }

    cout << endl<<"1. Byte mode" << endl;
    cout << "2. Megabyte mode" << endl;
    cout << "3. Gigabyte mode" << endl;

    // Loop until the user enters a valid choice for size mode
    while (true) {
        cout << endl<<"Please select size mode: ";
        cin >> sizeMode;

        // Validate size mode choice
        if (sizeMode == 1 || sizeMode == 2 || sizeMode == 3) {
            break; // Exit the loop if the choice is valid
        } else {
            cout << "Invalid choice. Please enter either 1, 2, or 3." << endl;
        }
    }

    if (sizeMode == 1) {
        cout <<endl<< "Enter the size of the file in bytes: ";
    } else if (sizeMode == 2) {
        cout <<endl<< "Enter the size of the file in megabytes: ";
    } else {
        cout <<endl<< "Enter the size of the file in gigabytes: ";
    }
    cin.ignore(); // Ignore newline character from previous input
    getline(cin, input);

    // Check if the input is an integer
    for (size_t i = 0; i < input.length(); ++i) {
        if (!isdigit(input[i])) {
            cout << "Please enter an integer." << endl;
            return 1;
        }
    }

    // Convert input to integer
    istringstream iss(input); // Create istringstream object
    iss >> fileSize; // Use the istringstream object
    // Convert megabytes/gigabytes to bytes
    if (sizeMode == 2) {
        fileSize *= 1024 * 1024; // 1 MB = 1024 * 1024 bytes
    } else if (sizeMode == 3) {
        fileSize *= 1024LL * 1024LL * 1024LL; // 1 GB = 1024 * 1024 * 1024 bytes
    }

    if (modeChoice == 1) {
        // Write lorem ipsum text directly to file
        write_text_to_file("Lorem ipsum dolor sit amet, consectetur adipiscing elit.", fileSize, "dummy.txt");
    } else if (modeChoice == 2) {
        // Write random binary data directly to file
        write_random_binary_data_to_file(fileSize, "dummy.txt");
    } else {
        // Ask user for the text to be written
        cout << "Enter the text to be written to the file: ";
        string customText;
        getline(cin, customText);
        write_text_to_file(customText, fileSize, "dummy.txt");
    }

#ifdef _WIN32
    // Display the location of the generated text file on Windows
    char cwd[MAX_PATH];
    if (GetCurrentDirectoryA(MAX_PATH, cwd) != 0) {
        cout << "Text file created at: " << cwd << "\\dummy.txt" << endl;
    } else {
        cerr << "Error getting current directory." << endl;
        return 1;
    }
#elif __linux__
    // Display the location of the generated text file on Linux
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        cout << "Text file created at: " << cwd << "/dummy.txt" << endl;
    } else {
        cerr << "Error getting current directory." << endl;
        return 1;
    }
#endif

    cout << "Enter the name of the executable file: ";
    cin >> exeFileName;
    cout << "Enter the name for the combined executable file: ";
    cin >> combinedFileName;

    // Now append the text file to an executable
    // Open the executable file
    ifstream exeFile(exeFileName.c_str(), ios::binary);
    if (!exeFile) {
        cerr << "Error: Unable to open executable file.\n";
        return 1;
    }

    // Open the text file to append
    ifstream textFile("dummy.txt", ios::binary);
    if (!textFile) {
        cerr << "Error: Unable to open text file.\n";
        return 1;
    }

    // Open a new file for writing, which will contain both executable and text file
    ofstream combinedFile(combinedFileName.c_str(), ios::binary);
    if (!combinedFile) {
        cerr << "Error: Unable to create combined file.\n";
        return 1;
    }

    // Read and write the content of the executable file to the combined file
    combinedFile << exeFile.rdbuf();

    // Read and write the content of the text file to the combined file
    combinedFile << textFile.rdbuf();

    // Close the files
    exeFile.close();
    textFile.close();
    combinedFile.close();

    // Display the directory of the created combined file
#ifdef _WIN32
    if (GetCurrentDirectoryA(MAX_PATH, cwd) != 0) {
        cout << "Combined executable file created at: " << cwd << "\\" << combinedFileName << endl;
    } else {
        cerr << "Error getting current directory." << endl;
        return 1;
    }
#elif __linux__
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        cout << "Combined executable file created at: " << cwd << "/" << combinedFileName << endl;
    } else {
        cerr << "Error getting current directory." << endl;
        return 1;
    }
#endif

    system("pause");
}
