#include <iostream>
#include <cstring>
#include <fstream>
#include <limits>
#include <algorithm>

//Structure

struct state {
    char name[30];
    int languageCount;
    char language[30];
    char currency[20];
    double usdRate;
};

//Helpful functions

void clearInputLine() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readInt() {
    int x;
    while (true) {
        if (std::cin >> x) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }
        std::cout << "Error: enter a digit.\n";
        clearInputLine();
    }
}

double readDouble() {
    double x;
    while (true) {
        if (std::cin >> x) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }
        std::cout << "Error: enter a digit.\n";
        clearInputLine();
    }
}

void readLine(char text[], int size) {
    while (true) {
        std::cin.getline(text, size);

        if (std::cin.fail()) {
            std::cout << "Error: line is too long.\n";
            clearInputLine();
            continue;
        }

        if (std::strlen(text) == 0) {
            std::cout << "Error: line cannot be empty.\n";
            continue;
        }

        return;
    }
}

//Main Functions - create/delete

void createFile(const char* fName) {
    std::ofstream f(fName, std::ios::binary);
    f.close();
}

bool deleteFile(const char* fName) {
    return std::remove(fName) == 0;
}

//If exists

bool fileExists(const char* fName) {
    std::ifstream f(fName, std::ios::binary);
    return f.is_open();
}

//Count records in file

int countRecords(const char* fName) {
    std::ifstream f(fName, std::ios::binary);

    f.seekg(0, std::ios_base::end);
    int k = f.tellg() / sizeof(state);
    f.close();

    return k;
}

//Read File

void readFile(const char* fName, state st[], int n) {
    std::ifstream f(fName, std::ios::binary);

    for (int i = 0; i < n; i++) {
        f.read((char*)&st[i], sizeof(st[i]));
    }

    f.close();
}

void enterStruct(state st[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "\nCountry name: ";
        readLine(st[i].name, 30);

        std::cout << "Official language count: ";
        st[i].languageCount = readInt();

        std::cout << "Language: ";
        readLine(st[i].language, 30);

        std::cout << "Currency: ";
        readLine(st[i].currency, 20);

        std::cout << "USD rate: ";
        st[i].usdRate = readDouble();
    }
}

//Write file

void addRecordsToFile(const char* fName, state st[], int n) {
    std::ofstream f(fName, std::ios::binary | std::ios::app);

    for (int i = 0; i < n; i++) {
        f.write((char*)&st[i], sizeof(st[i]));
    }

    f.close();
}

//Remove some records from file

void removeRecordsFromFile(const char* fName, state st[], int n, char (*namesToDelete)[30], int m) {
    std::ofstream f(fName, std::ios::binary);

    for (int i = 0; i < n; i++) {
        int o = 0;
        for (int j = 0; j < m; j++) {
            if (std::strcmp (st[i].name, namesToDelete[j]) == 0) {
                o++;
            }
        }
        if (o > 0) {
            continue;
        }
        else {
            f.write((char*)&st[i], sizeof(st[i]));
        }
    }
    
     f.close();
}

//Print

void printRecord(const state& st) {
    std::cout << "\nCountry: " << st.name;
    std::cout << "\nOfficial language count: " << st.languageCount;
    std::cout << "\nLanguage: " << st.language;
    std::cout << "\nCurrency: " << st.currency;
    std::cout << "\nUSD rate: " << st.usdRate << "\n";
}


void printAllRecords(state st[], int n) {
    for (int i = 0; i < n; i++) {
        printRecord(st[i]);
    }
}

//Show countries with more than one official language

void showCountriesWithMoreThanOneLanguage(state st[], int n) {
    for (int i = 0; i < n; i++) {
        if (st[i].languageCount > 1) {
            printRecord(st[i]);
        }
    }
}

//Show countries with a low USD exchange rate

void findCountriesWithLowUsdRate (state st[], int n, double userrate) {
    for (int i = 0; i < n; i++) {
        if (st[i].usdRate < userrate) {
            printRecord(st[i]);
        }
    }
}

//Sort Countries

void sortCountries(state st[], int n) {
    std::sort(st, st + n, [](const state& a, const state& b) {
        return strcasecmp(a.name, b.name) < 0;
    });
}

int main() {
    char fName[80];
    int k = 0;
    state* st = nullptr;

    while (true) {
        std::cout << "\n1: Create file\n";
        std::cout << "2: Add record(s) to the file\n";
        std::cout << "3: Delete file\n";
        std::cout << "4: Delete record(s) from the file\n";
        std::cout << "5: Show all records from the file\n";
        std::cout << "6: Show countries with more than one official language\n";
        std::cout << "7: Show countries with a low USD exchange rate\n";
        std::cout << "8: Show countries in alphabetical order\n";
        std::cout << "0: Exit\n";

        k = readInt();

        switch (k) {

            case 1: {
                std::cout << "\nEnter a file name: ";
                readLine(fName, 80);

                if (fileExists(fName)) {
                     std::cout << "File with the same name already exists.\n";
                      break;
                }

                createFile(fName);
                std::cout << "\nFile " << fName << " created successfully.\n";
                break;
            }

            case 2: {
                std::cout << "\nEnter a file name: ";
                readLine(fName, 80);

                if (!fileExists(fName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }

                std::cout << "\nEnter the number of states you want to add: ";
                int n = readInt();

                st = new state[n];

                enterStruct(st, n);
                addRecordsToFile(fName, st, n);

                std::cout << "\nRecords were saved successfully.\n";

                delete[] st;
                st = nullptr;
                
                break;
            }

            case 3: {
                std::cout << "\nEnter a file name: ";
                readLine(fName, 80);

                if (!fileExists(fName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }

                if(deleteFile(fName)) 
                std::cout << "File deleted successfully.";
                else std::cout << "Error. Could not delete file.";

                break;
            }

            case 4: {
                std::cout << "\nEnter a file name: ";
                readLine(fName, 80);

                if (!fileExists(fName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }

                int n = countRecords(fName);
                st = new state[n];
                readFile(fName, st, n);

                std::cout << "Enter a number of records you want to remove: ";
                int m = readInt();
                char (*namesToDelete)[30] = new char[m][30];
                
                for (int i = 0; i < m; i++) {
                     std::cout << "Enter country name " << i + 1 << ": ";
                     readLine(namesToDelete[i], 30);
                }

                removeRecordsFromFile(fName, st, n, namesToDelete, m);

                delete[] st;
                st = nullptr;
                delete[] namesToDelete;
                namesToDelete = nullptr;

                break;
            }

            case 5: {
                std::cout << "\nEnter a file name: ";
                readLine(fName, 80);

                if (!fileExists(fName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }
                
                int n = countRecords(fName);
                st = new state[n];
                readFile(fName, st, n);

                std::cout << "All records from the file:\n";
                printAllRecords(st, n);
                
                delete[] st;
                st = nullptr;

                break;
            }

            case 6: {
                std::cout << "\nEnter a file name: ";
                readLine(fName, 80);

                if (!fileExists(fName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }

                int n = countRecords(fName);
                st = new state[n];
                readFile(fName, st, n);

                std::cout << "Countries with more than one official language:\n";
                showCountriesWithMoreThanOneLanguage(st, n);
                
                delete[] st;
                st = nullptr;

                break;
            }

            case 7: {
                std::cout << "\nEnter a file name: ";
                readLine(fName, 80);

                if (!fileExists(fName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }

                int n = countRecords(fName);
                st = new state[n];
                readFile(fName, st, n);

                std::cout << "Enter the USD exchange rate: ";
                double userrate = readDouble();
                std::cout << "Countries lower USD exchange rate:\n";
                findCountriesWithLowUsdRate(st, n, userrate);
                
                delete[] st;
                st = nullptr;

                break;
            }

            case 8: {
                std::cout << "\nEnter a file name: ";
                readLine(fName, 80);

                if (!fileExists(fName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }

                int n = countRecords(fName);
                st = new state[n];
                readFile(fName, st, n);

                std::cout << "Countries in alphabetical order:\n";
                sortCountries(st, n);
                printAllRecords(st, n);
                
                delete[] st;
                st = nullptr;

                break;
            }

            default:
            std::cout << "Error: wrong menu option.\n";
            break;

            case 0:
                return 0;
        }
    }
}