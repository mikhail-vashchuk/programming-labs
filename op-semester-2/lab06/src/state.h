#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

struct State {
    char name[30];
    int languageCount;
    char language[30];
    char currency[20];
    double usdRate;
};

void clearInputLine();
int readInt();
double readDouble();
void readLine(char [], int);
void createFile(const char*);
bool deleteFile(const char*);
bool fileExists(const char*);
int countRecords(const char*);
void readFile(const char*, State [], int);
void inputStates(State [], int n);
void addRecordsToFile(const char*, const State [], int);
int removeRecordsFromFile(const char*, const State [], int, const char (*)[30], int);
void printRecord(const State&);
void printAllRecords(const State[], int);
void showCountriesWithMoreThanOneLanguage(const State[], int);
void showCountriesWithUsdRateBelow(const State[], int, double);
int compareIgnoreCase(const char [], const char []);
void sortCountries(State[], int);

#endif // STATE_H_INCLUDED