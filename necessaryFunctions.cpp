#include "necessaryFunctions.h"
#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <cctype> 
#include <vector>

void drawHangman(int wrongGuesses) {
    std::vector<std::string> hangman;

    switch (wrongGuesses) {
    
    case 0:
        hangman = {
            "  ",
            "  ",
            "       ",
            "      ",
            "      ",
            ""
        };
        break;

    case 1:
        hangman = {
            "  ",
            "  ",
            "       ",
            "      ",
            "      ",
            " _______"
        };
        break;

    case 2:
        hangman = {
            "   ",
            "   |    ",
            "   |     ",
            "   |    ",
            "   |    ",
            " __|____"
        };
        break;

    case 3:
        hangman = {
            "   _______",
            "   |/    |",
            "   |     ",
            "   |    ",
            "   |    ",
            " __|____"
        };
        break;

    default:
        hangman = {
            "   _______",
            "   |/    |",
            "   |     " + std::string(wrongGuesses >= 4 ? "O" : ""),
            "   |    " + std::string(wrongGuesses >= 5 ? "/" : " ") + (wrongGuesses >= 6 ? "|" : "") + (wrongGuesses >= 7 ? "\\" : ""),
            "   |    " + std::string(wrongGuesses >= 8 ? "/" : "") + " " + std::string(wrongGuesses >= 9 ? "\\" : ""),
            " __|____"
        };
        break;
    }

    std::cout << std::endl;
    for (const std::string& line : hangman) {
        std::cout << "\t\t\t\t\t\t" << line << std::endl;
    }
}

void guess_a_letter(std::string current_word, char user_letter_guess, int *p_match_array, int* p_wrong_guesses){

    int correct_guess_flag = 0;
    int same_guess_flag = 0;

    for (size_t i = 0; i < current_word.length(); i++){
        if ( current_word[i] == user_letter_guess){
            if(p_match_array[i] == 0){
                p_match_array[i] = 1;
                correct_guess_flag = 1; 
            } else{
                same_guess_flag = 1;
            }   
        }               
    }
    
    if (correct_guess_flag == 1){
        std::cout << "Right guess!!\n" << std::endl;
    }else if(same_guess_flag == 0){
        *p_wrong_guesses = *p_wrong_guesses - 1;
        std::cout << "Wrong guess, remaining chances: " << *p_wrong_guesses<< "\n" << std::endl;
    } else {
        *p_wrong_guesses = *p_wrong_guesses - 1;
        std::cout << "Oops! You've already guessed that letter. remaining chances: " << *p_wrong_guesses<< "\n";
    }
}

void print_word(std::string current_word,int *p_match_array){
    std::cout <<"\t\t\t\t\t\t";
    for (size_t i=0; i<current_word.length(); i++){
    
            if(p_match_array[i] == 1){
                std::cout << current_word[i] << " ";
            }else{
                std::cout << "_ ";
            }
    }
}

int is_win(int *p_match_array, int size){
    int win_flag = 1;
    for(size_t i = 0; i < size; i++){
        if ( p_match_array[i] == 0){
            win_flag = 0;
            break;
        }
    }   
    return win_flag;
} 

int guess_a_word(std::string current_word, std::string user_word_guess, int* p_wrong_guesses){

    if (current_word == user_word_guess){
        return 1;
    } else{
        *p_wrong_guesses = 0;
        return 0;
    }
}
