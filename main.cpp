#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <algorithm>

const int number_of_words = 6229;
const std::string filename = "dictionary.txt";

void playGame();
void displayGuesses(std::vector<std::string> guesses, std::string word);
bool indict(std::string word, std::string filename);

int main() {
    std::cout << "********************" << "\n";
    std::cout << "****** WORDLE ******" << "\n";
    std::cout << "********************" << "\n";

    playGame();
}

void playGame() {
    std::ifstream dict;
    dict.open(filename);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, number_of_words);

    int number = dist(rng);

    int counter = 0;
    std::string word;

    while (std::getline(dict, word)) {
        
        counter++;

        if (counter == number) {
            break;
        }
    }

    dict.close();

    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    std::vector<std::string> guesses;

    std::cout << "\n__________________\n\n";
    displayGuesses(guesses, word);
    std::cout << "\n__________________\n\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "\n ENTER YOUR GUESS: ";
        std::string guess;
        std::getline(std::cin, guess);
        if (guess.length() > 5 || guess.length() < 5) {
            std::cout << "\n__________________\n\n";
            std::cout << "That word is not 5 letters";
            std::cout << "\n__________________\n\n";
            --i;
            displayGuesses(guesses, word);
            continue;
        }
        std::transform(guess.begin(), guess.end(), guess.begin(), ::tolower);
        if (indict(guess, "dictionary.txt") == false) {
            std::cout << "\n__________________\n\n";
            std::cout << "That word does not exist";
            std::cout << "\n__________________\n\n";
            --i;
            displayGuesses(guesses, word);
            continue;
        }
        guesses.push_back(guess);
        std::cout << "\n__________________\n\n";
        displayGuesses(guesses, word);
        std::cout << "\n__________________\n\n";
        if (word == guess) {
            std::cout << "YOU WIN!" << "\n";
            return;
        }
    }
    std::cout << "YOU LOST!" << "\n";
    return;

}

void displayGuesses(std::vector<std::string> guesses, std::string word) {
    for (int i = 1; i <= 5; i++) {
        if (i > guesses.size()) {
            std::cout << "Guess " << i << ": _ _ _ _ _" << "\n";
        } else {

            std::cout << "Guess " << i << ": ";
            for (int j = 0; j < 5; j++) {
                if (guesses.at(i-1)[j] == word[j]) {
                    std::cout << "\033[32m" << guesses.at(i-1)[j] << "\033[0m ";
                } else if (word.find(guesses.at(i-1)[j]) != std::string::npos) {
                    std::cout << "\033[33m" << guesses.at(i-1)[j] << "\033[0m ";
                } else {
                    std::cout << guesses.at(i-1)[j] << " ";
                }
            }
            std::cout << "\n";
        }
    }
}

bool indict(std::string word, std::string filename) {
    std::string line;
    std::ifstream file(filename); 
    while (std::getline(file, line)) {
        if (line == word) {
            return true;
        }
    }
    return false;
}