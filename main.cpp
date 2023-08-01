#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <cctype> 

void guess_a_letter(std::string current_word, char user_letter_guess, int *p_match_array, int* p_wrong_guesses);
int guess_a_word(std::string current_word, std::string user_word_guess, int* p_wrong_guesses);
void print_word(std::string current_word,int *p_match_array);
int is_win(int *p_match_array, int size);

int main() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::string cities[10] {"ANKARA","ISTANBUL", "AFYONKARAHISAR", "BALIKESIR", "BURSA","ADANA", "KAHRAMANMARAS", "KONYA","GAZIANTEP", "IZMIR"};
    std::uniform_int_distribution<> distrib(0, ((sizeof(cities)/ sizeof(cities[0])) -1));
    auto toUpper = [](unsigned char c) { return std::toupper(c); };
    int in_game = 1;
    std::string user_word_guess;

    while(in_game){
        std::cout << "Welcome to Hangman Game.\nPress 1 to start the game\nPress 2 to see the rules\nPress 0 to exit: ";

        while (!(std::cin >> in_game)) {
                std::cout << "Invalid input. Please enter a number: ";
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining characters
        }

        if(in_game == 2){

            system("cls");
            std::cout <<"Welcome to 'Da Rules' for Hangman! " << std::endl;
            std::cout <<"1- When the game starts, a random word related to the topic chosen by you will be selected" << std::endl;
            std::cout <<"2- At the beginning, you'll see a blank word, and your task is to reveal the complete word to win. " << std::endl;
            std::cout <<"3- To uncover the word, guess one letter in each turn by entering '1'. " << std::endl;
            std::cout <<"4- Each correct guess reveals the letter's position in the word, while each incorrect guess adds a part to the hangman drawing." << std::endl;
            std::cout <<"5- If you want to guess the whole word, press '2' and enter your guess.";
            std::cout <<"But remember, if you can not guess it right, you will lose the game.You only have one shot. Use it wisely :)" <<std::endl;
            std::cout <<"6- And last but not least, do not forget to have fun :) Good luck and enjoy the game!" <<std::endl;
            std::cout <<"Press any key to continue..." <<std::endl;
            std::cin >> user_word_guess;
            system("cls");

        }
        
        while(in_game==1){

            int user_guess_type;
            int current_word_index = distrib(gen);
            int win_flag = 0;
            char user_letter_guess;
            std::string current_word = cities[current_word_index];
            int *p_match_array {new(std::nothrow) int[current_word.length()]{}};
            int wrong_guesses = 10;
            int* p_wrong_guesses = &wrong_guesses;
            std::cout<< "Let the game begin!\n"<<std::endl;
            
            for(size_t i = 0; i < current_word.length(); i++){
                if (current_word[i] == ' '){
                    std::cout<< " ";
                } else {
                std::cout<< "_ "; 
                }
                
            }

            while(wrong_guesses > 0 && win_flag == 0){

                std::cout << "\n\nPress 1 to guess a letter, press 2 to guess the word:  ";

                while (!(std::cin >> user_guess_type)) {
                    std::cout << "Invalid input. Please enter a number.\n";
                    std::cin.clear(); 
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                }

                if(user_guess_type == 1){

                    std::cout << "Enter your guess: ";

                    while (!(std::cin >> user_letter_guess) || std::cin.peek() != '\n') {
                        std::cout << "Invalid input. Please enter a single letter: ";
                        std::cin.clear(); 
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    }
                    user_letter_guess = std::toupper(user_letter_guess);
                    guess_a_letter(current_word, user_letter_guess, p_match_array, p_wrong_guesses);
                    win_flag = is_win(p_match_array, current_word.length());
                    print_word(current_word, p_match_array); 

                } else if(user_guess_type == 2){

                    std::cout << "Enter your guess: ";
                    std::cin >> user_word_guess;
                    std::transform(user_word_guess.begin(), user_word_guess.end(), user_word_guess.begin(), toUpper);
                    win_flag = guess_a_word(current_word, user_word_guess, p_wrong_guesses);
                    
                }else{
                    std::cout << "\nInvalid input, please try again" << std::endl;
                }    
                    
            }

            if( win_flag == 1){
                std::cout << "\nCongratulations, you won :)" << std::endl;
            }else {
                std::cout << "\nSorry :( you lost. The answer was: " << current_word <<  std::endl;
            }

            std::cout << "\nDo you want to play again with same topic? (1: Yes, 2: No, go to the main menu, 0: Exit the game): ";

            while (!(std::cin >> in_game)) {
                    std::cout << "Invalid input. Please enter a number: ";
                    std::cin.clear(); 
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining characters
            }
            
            delete [] p_match_array;
            p_match_array = nullptr;
        }
    }
        std::cout << "That was fun!! See you again :)";  
        return 0;
}

void guess_a_letter(std::string current_word, char user_letter_guess, int *p_match_array, int* p_wrong_guesses){

    int correct_guess_flag = 0;

    for (size_t i = 0; i < current_word.length(); i++){

            if ( current_word[i] == user_letter_guess){
                p_match_array[i] = 1;
                correct_guess_flag = 1;
            }               
    }
    
    if (correct_guess_flag != 1){
        *p_wrong_guesses = *p_wrong_guesses - 1;
        std::cout << "Wrong guess, remaining chances: " << *p_wrong_guesses<< "\n" << std::endl;
    }else{
        std::cout << "Right guess!!\n" << std::endl;
    }
}

void print_word(std::string current_word,int *p_match_array){

    for (size_t i=0; i<current_word.length(); i++){
        if (current_word[i] == ' '){
            std::cout << " ";
        }else{
            if(p_match_array[i] == 1){
                std::cout << current_word[i] << " ";
            }else{
                std::cout << "_ ";
            }
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