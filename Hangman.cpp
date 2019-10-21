#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
std::string getRandomWord(){
    std::string filename = "words.txt";
    std::fstream stream;
    std::string word = "";
    stream.open(filename, stream.in);
    if(!stream.is_open()){
        throw "file doesn't exist";
    }
    std::vector<std::string> words;
    while(!stream.eof()){
        std::string line;
        std::getline(stream, line);
        words.emplace_back(line);
    }
    std::random_device random_dev;
    std::mt19937 generator(random_dev());
    std::shuffle(words.begin(), words.end(), generator);
    word = words[0];
    word = word.substr(0, word.size() - 1); //remove endline character
    return word;
}
void hangman(std::string word){
    std::string letters = "";
    std::vector<char> availableLetters;
    for(char i = 'a'; i < 'z'; i++){
        availableLetters.emplace_back(i);
    }
    system("clear");
    letters = std::string(word.size(), '_');
    int guesses = word.size() + 4;
    while(1){
        bool correct = false;
        std::cout << letters << "\n";
        for(char c : availableLetters){
            std::cout << c;
        }
        std::cout << std::endl;
        std::string guess = "";
        std::cout << "Guess a letter/word? ";
        std::cin >> guess;
        if(guess == word){
            std::cout << "You won!\n";
            break;
        }
        std::replace(availableLetters.begin(), availableLetters.end(), guess[0], ' ');
        for(int i = 0; i < word.size(); i++){
            if(guess[0] == word[i]){
                letters[i] = word[i];
                correct = true;
            }
        }
        if(correct){
            std::cout << "CORRECT! ";
        }
        else{
            guesses--;
            std::cout << "WRONG! ";
        }
        std::cout << guesses << " guesses left\n";
        if(guesses == 0){
            std::cout << "You lose!\n" << word << std::endl;
            break;
        }
    }
}
int main(){
    try{
        hangman(getRandomWord());
    }
    catch(const char* msg){
        std::cout << msg << std::endl;
    }
}