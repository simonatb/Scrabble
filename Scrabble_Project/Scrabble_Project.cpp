#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int const MAX = 20;
int const DEFAULT = 10;

//Get size 
int GetLength(string word) {
    int i = 0;
    while (word[i]) {
        i++;
    }
    return i;
}

//Validations
bool ValidAnswerExit(int answer) {
    return(answer == 0 || answer == 1 || answer == 2);
}
bool ValidateChanges(int change) {
    return (change >= 3 && change <= MAX);
}
bool ValidAnswer(int answer) {
    return(answer == 0 || answer == 1);
}


//Checks if the word is composed of the given letters
bool isStringInArray(const char* letters, string word, int letterCount) {
    int size = GetLength(word);

    int alphabet[26] = { 0 };
    for (int i = 0;i < letterCount;i++) {
        alphabet[letters[i] - 'a']++;

    }

    for (int i = 0;i < size;i++) {
        alphabet[word[i] - 'a']--;

    }

    for (int j = 0;j < 26;j++) {
        if (alphabet[j] < 0) {
            return false;
        }
    }
    return true;
}
bool isStringInFile(const char* filename, string word) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line.find(word) != string::npos) {
            file.close(); // Close the file after finding the string
            return true;  // Return true if the string is found
        }
    }

    file.close(); // Close the file if the string is not found
    return false;
}
//Gameplay word validation
bool GameplayValidation(char* lettersPtr, string word, char* filenamePtr, int letterCount) {
    return (isStringInArray(lettersPtr, word, letterCount) == 1 && isStringInFile(filenamePtr, word) == 1);
}
//Random letters generator
char getRandomLetter() {

    int randomValue = rand() % 26;

    return 'a' + randomValue;
}

void CurrentRandomLetters(char letters[], int letterCount) {
    for (int i = 1; i <= letterCount; i++) {
        char randomValue = getRandomLetter();
        letters[i] = randomValue;
        cout << randomValue << " ";
    }
    cout << endl;
}


void Menu();

void ScrabbleGame(int rounds, int letterCount, char* filenamePtr) {
    int points = 0;
    string word;
    char array[MAX];
    char* letters = array;
    
    for (int i = 1; i <= rounds; i++) {
        cout << "Round " << i << "   points: " << points << "   letters:";
        CurrentRandomLetters(letters, letterCount);

        do {
            cin >> word;
            if (GameplayValidation(letters, word, filenamePtr, letterCount) == 0) {
                cout << "Invalid. Try again!\n";
            }
        } while (GameplayValidation(letters, word, filenamePtr, letterCount) == 0);
        points += GetLength(word);
        cout << "Your points are: " << points << endl;

    }
    cout << "Your total points are: " << points << endl;
    cout << "Returning to menu!" << endl;

    Menu();
}
void Rounds(int& rounds) {
    int answer = 0;
    cout << "Do you want to change the number of rounds? (1 for yes/0 for no)\n";
    do {
        cin >> answer;
        if (ValidAnswer(answer) == 0) {
            cout << "Invalid answer \n";

        }
    } while (ValidAnswer(answer) == 0);
    if (answer == 1) {
        cout << "How many rounds you want to play? \n";

        do {
            cin >> rounds;
            if (ValidateChanges(rounds) == 0) {
                cout << "Invalid answer \n";

            }
        } while (ValidateChanges(rounds) == 0);
    }
}

void Letters(int& letterCount) {
    int answer = 0;
    cout << "Do you want to change the number of letters you are given? (1 for yes/0 for no)\n";
    do {
        cin >> answer;
        if (ValidAnswer(answer) == 0) {
            cout << "Invalid answer \n";

        }
    } while (ValidAnswer(answer) == 0);

    if (answer == 1) {
        cout << "How many letters you want to be given? \n";

        do {
            cin >> letterCount;
            if (ValidateChanges(letterCount) == 0) {
                cout << "Invalid answer \n";

            }
        } while (ValidateChanges(letterCount) == 0);
    }
}
bool isLowerCase(const string& str) {
    for (char ch : str) {

        if (!(ch >= 'a' && ch <= 'z')) {
            return false;
        }
    }
    return true;
}
void AddWord(const char* filename) {
    int answer = 0;
    cout << "Do you want to add a word to the dictionary? (1 for yes/0 for no)\n";
    do {
        cin >> answer;
        if (ValidAnswer(answer) == 0) {
            cout << "Invalid answer \n";

        }
    } while (ValidAnswer(answer) == 0);
    if (answer == 1) {
        cout << "Type in the word (only lowercase):\n";
        string NewWord;
        do {
            cin >> NewWord;
            if (isLowerCase(NewWord) == 0) {
                cout << "Invalid word. Only lowercase letters. \n";
            }

        } while (isLowerCase(NewWord) == 0);
        ofstream MyFile(filename, ios::app);
        MyFile << NewWord << endl;
        MyFile.close();

    }
}
void Settings(char filename[]) {

    char* filenamePtr = filename;
    int answer = 0;
    int rounds = DEFAULT;
    int letterCount = DEFAULT;

    Rounds(rounds);
    Letters(letterCount);
    AddWord(filename);

    cout << "Let's play scrabble now!";
    ScrabbleGame(rounds, letterCount, filenamePtr);
}

void Menu() {

    char filename[] = "scrabble.txt";
    int answer = 0;
    cout << "Do you want to start a new game or open settings? (0 for settings/1 for new game/2 for exiting the program) \n";
    do {
        cin >> answer;
        if (ValidAnswerExit(answer) == 0) {
            cout << "Invalid answer \n";

        }
    } while (ValidAnswerExit(answer) == 0);
    if (answer == 1) {
        int rounds = DEFAULT;
        int letterCount = DEFAULT;
        ScrabbleGame(rounds, letterCount, filename);
    }
    else if (answer == 2) {

        exit(0);
    }
    else Settings(filename);
}
int main() {
  
    Menu();
   
}