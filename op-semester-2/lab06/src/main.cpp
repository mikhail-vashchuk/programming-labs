#include <iostream>
#include "state.h"

int main() {
    char fileName[80];
    int k = 0;
    State* states = nullptr;

    while (true) {
        std::cout << "\n1: Create file\n";
        std::cout << "2: Add record(s) to the file\n";
        std::cout << "3: Delete file\n";
        std::cout << "4: Delete record(s) from the file\n";
        std::cout << "5: Show all records from the file\n";
        std::cout << "6: Show countries with more than one official language\n";
        std::cout << "7: Show countries with a USD rate below a given value\n";
        std::cout << "8: Show countries in alphabetical order\n";
        std::cout << "0: Exit\n";

        k = readInt();

        switch (k) {

            case 1: {
                std::cout << "\nEnter a file name: ";
                readLine(fileName, 80);

                if (fileExists(fileName)) {
                     std::cout << "File with the same name already exists.\n";
                      break;
                }

                createFile(fileName);
                std::cout << "\nFile " << fileName << " created successfully.\n";
                break;
            }

            case 2: {
                std::cout << "\nEnter a file name: ";
                readLine(fileName, 80);

                if (!fileExists(fileName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }

                std::cout << "Enter the number of states you want to add: ";
                int n;
                
                while (true) {
                    n = readInt();
                    
                    if (n <= 0) {
                        std::cout << "Error: number must be greater than zero.\n";
                    }
                    else {
                        break;
                    }
                }

                states = new State[n];

                inputStates(states, n);
                addRecordsToFile(fileName, states, n);

                std::cout << "\nRecords were saved successfully.\n";

                delete[] states;
                states = nullptr;
                
                break;
            }

            case 3: {
                std::cout << "\nEnter a file name: ";
                readLine(fileName, 80);

                if (!fileExists(fileName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }

                if (deleteFile(fileName)) 
                std::cout << "File deleted successfully.\n";
                else std::cout << "Error. Could not delete file.\n";

                break;
            }

            case 4: {
                std::cout << "\nEnter a file name: ";
                readLine(fileName, 80);

                if (!fileExists(fileName)) {
                    std::cout << "Error: file does not exist.\n";
                    break;
                }

                int n = countRecords(fileName);

                if (n == 0) {
                    std::cout << "File is empty. There are no records to remove.\n";
                    break;
                }

                states = new State[n];
                readFile(fileName, states, n);

                int m;
                while (true) {
                    std::cout << "Enter a number of records you want to remove: ";
                    m = readInt();

                    if (m <= 0) {
                        std::cout << "Error: number must be greater than zero.\n";
                    }
                    else if (m > n) {
                        std::cout << "Error: there are only " << n << " record(s) in the file.\n";
                    }
                    else {
                        break;
                    }
                }

                char (*namesToDelete)[30] = new char[m][30];

                for (int i = 0; i < m; i++) {
                    std::cout << "Enter country name " << i + 1 << ": ";
                    readLine(namesToDelete[i], 30);
                }

                int removed = removeRecordsFromFile(fileName, states, n, namesToDelete, m);
                
                if (removed == 0) {
                    std::cout << "No matching records were found.\n";
                } 
                else {
                    std::cout << "Removed " << removed << " record(s).\n";
                }

                delete[] states;
                states = nullptr;
                delete[] namesToDelete;
                namesToDelete = nullptr;

                break;
            }

            case 5: {
                std::cout << "\nEnter a file name: ";
                readLine(fileName, 80);

                if (!fileExists(fileName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }
                
                int n = countRecords(fileName);

                if (n == 0) {
                    std::cout << "File is empty.\n";
                    break;
                }

                states = new State[n];
                readFile(fileName, states, n);
                
                std::cout << "All records from the file:\n";
                printAllRecords(states, n);
                
                delete[] states;
                states = nullptr;

                break;
            }

            case 6: {
                std::cout << "\nEnter a file name: ";
                readLine(fileName, 80);

                if (!fileExists(fileName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }

                int n = countRecords(fileName);

                if (n == 0) {
                    std::cout << "File is empty.\n";
                    break;
                }

                states = new State[n];
                readFile(fileName, states, n);

                std::cout << "Countries with more than one official language:\n";
                showCountriesWithMoreThanOneLanguage(states, n);
                
                delete[] states;
                states = nullptr;

                break;
            }

            case 7: {
                std::cout << "\nEnter a file name: ";
                readLine(fileName, 80);

                if (!fileExists(fileName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }

                int n = countRecords(fileName);

                if (n == 0) {
                    std::cout << "File is empty.\n";
                    break;
                }

                states = new State[n];
                readFile(fileName, states, n);

                std::cout << "Enter the maximum USD rate: ";
                double userRate = readDouble();
                std::cout << "Countries with a USD rate below " << userRate << ":\n";
                showCountriesWithUsdRateBelow(states, n, userRate);

                delete[] states;
                states = nullptr;

                break;
            }

            case 8: {
                std::cout << "\nEnter a file name: ";
                readLine(fileName, 80);

                if (!fileExists(fileName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }

                int n = countRecords(fileName);

                if (n == 0) {
                    std::cout << "File is empty.\n";
                    break;
                }
                states = new State[n];
                readFile(fileName, states, n);

                std::cout << "Countries in alphabetical order:\n";
                sortCountries(states, n);
                printAllRecords(states, n);
                
                delete[] states;
                states = nullptr;

                break;
            }

            case 0:
                return 0;

            default:
                std::cout << "Error: wrong menu option.\n";
                break;

        }
    }
}
