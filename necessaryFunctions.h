#ifndef NECESSARYFUNCTIONS_H
#define NECESSARYFUNCTIONS_H

#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <cctype> 
#include <vector>

void drawHangman(int wrongGuesses);
void guess_a_letter(std::string current_word, char user_letter_guess, int *p_match_array, int* p_wrong_guesses);
int guess_a_word(std::string current_word, std::string user_word_guess, int* p_wrong_guesses);
void print_word(std::string current_word,int *p_match_array);
int is_win(int *p_match_array, int size);

#endif
