#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <cctype> 
#include <vector>
#include <ctime>
#include<windows.h>
#include "necessaryFunctions.h"

int main() {

    std::mt19937 rng;
    rng.seed(std::time(0));
    auto toUpper = [](unsigned char c) { return std::toupper(c); };
    std::string user_word_guess, current_word;
    std::uniform_int_distribution<> distrib;
    std::string *selected_array;

    std::string cities[10] {"ANKARA","ISTANBUL", "AFYONKARAHISAR", "BALIKESIR", "BURSA","ADANA", "KAHRAMANMARAS", "KONYA","GAZIANTEP", "IZMIR"};
    std::string books[14] {"DON QUIXOTE","CRIME AND PUNISHMENT", "MOBY DICK", "THE ADVENTURES OF HUCKLEBERRY FINN", "WAR AND PEACE","A TALE OF TWO CITIES", "FATHERS AND SONS", "THE THREE MUSKETEERS","THE LILY OF THE VALLEY", "ANNA KARENINA", "HARRY POTTER","THE LORD OF THE RINGS ","THE LITTLE PRINCE", "ANIMAL FARM"};
    std::string movies[19] {"AVATAR","STAR WARS", "JURASSIC WORLD", "MISSION IMPOSIBLE", "THE LION KING","THE AVENGERS", "FIGHT CLUB", "OPPENHEIMER","BARBIE", "TITANIC","THE GODFATHER","FAST AND FURIOUS","MATRIX", "INTERSTELLAR","THE CHAOS CLASS", "AYLA", "TERMINATOR", "TOY STORY","HOME ALONE" };
    std::string capitals[36] {"ANKARA","BERLIN", "ATHENS", "PARIS", "LONDON","WASHINGTON", "ROME", "VIENNA","PRAGUE", "BUDAPEST", "DUBLIN","OSLO", "LISBON","LUXEMBOURG","MOSCOW","MADRID","STOCKHOLM","OTTAWA","MEXICO CITY","HONG KONG","NEW DELHI","TOKYO","SEOUL","PYONGYANG","BAKU","CANBERRA","OUAGADOUGOU","KINSHASA","CAIRO","BRUSSELS","COPHAGEN","SOFIA","HELSINKI","AMSTERDAM","WARSAW","KYIV"};
    std::string countries[36] { "TURKIYE", "GERMANY", "GREECE", "FRANCE", "UNITED KINGDOM", "UNITED STATES", "ITALY", "AUSTRIA", "CZECH REPUBLIC", "HUNGARY", "IRELAND", "NORWAY", "PORTUGAL", "LUXEMBOURG", "RUSSIA", "SPAIN", "SWEDEN", "CANADA", "MEXICO", "HONG KONG", "INDIA", "JAPAN", "SOUTH KOREA", "NORTH KOREA", "AZERBAIJAN", "AUSTRALIA", "BURKINA FASO", "DEMOCRATIC REPUBLIC OF THE CONGO", "EGYPT", "BELGIUM", "DENMARK", "BULGARIA", "FINLAND", "NETHERLANDS", "POLAND", "UKRAINE" };
    
    int in_game = 1;
    int user_choice, current_word_index, selected_array_size;
    

    while(in_game){
        system("cls");
        std::cout << "Welcome to Hangman Game. I am happy to see you here :)\n"<< std::endl;
        std::cout << "Choose a category to start the game. Enter the number of category you would like to play:\n" << std::endl;
        std::cout <<"\t1- Movies" << std::endl;
        std::cout <<"\t2- Books" << std::endl;
        std::cout <<"\t3- World's Capitals" << std::endl;
        std::cout <<"\t4- Countries" << std::endl;
        std::cout <<"\t5- Cities of Turkiye\n" << std::endl;
        std::cout << "Press 9 to see the rules" << std::endl;
        std::cout << "Press 0 to exit: " << std::endl;
        
        while (!(std::cin >> user_choice)) {
                std::cout << "Invalid input. Please enter a number: ";
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining characters
        }
        
        system("cls");
        switch (user_choice)
        {
        case 0:
            in_game = 0;
            break;

        case 1:
            selected_array = movies;
            selected_array_size = sizeof(movies)/ sizeof(movies[0]);
            std::cout<< "\t\t\t\t\t\t Here is a movie for you. Good luck :) Let the game begin!\n"<<std::endl;
            break;

        case 2:
            selected_array = books;
            selected_array_size = sizeof(books)/ sizeof(books[0]);
            std::cout<< "\t\t\t\t\t\t Here is a book for you. Good luck :) Let the game begin!\n"<<std::endl;
            break;

        case 3:
            selected_array = capitals;
            selected_array_size = sizeof(capitals)/ sizeof(capitals[0]);
            std::cout<< "\t\t\t\t\t\t Here is a World's capital for you. Good luck :) Let the game begin!\n"<<std::endl;
            break;

        case 4:
            selected_array = countries;
            selected_array_size = sizeof(countries)/ sizeof(countries[0]);
            std::cout<< "\t\t\t\t\t\t Here is a country for you. Good luck :) Let the game begin!\n"<<std::endl;
            break;

        case 5:
            selected_array = cities;
            selected_array_size = sizeof(cities)/ sizeof(cities[0]);
            std::cout<< "\t\t\t\t\t\t Here is a city from Turkiye for you. Good luck :) Let the game begin!\n"<<std::endl;
            break;
        case 9:

            system("cls");
            std::cout <<"Welcome to 'Da Rules' for Hangman! " << std::endl;
            std::cout <<"1- When the game starts, a random word related to the category chosen by you will be selected" << std::endl;
            std::cout <<"2- At the beginning, you'll see a blank word, and your task is to reveal the complete word to win. " << std::endl;
            std::cout <<"3- To uncover the word, guess one letter in each turn by entering '1'. " << std::endl;
            std::cout <<"4- Each correct guess reveals the letter's position in the word, while each incorrect guess adds a part to the hangman drawing. (You have 9 incorrect guess attempts.)" << std::endl;
            std::cout <<"5- If you want to guess the whole word, press '2' and enter your guess.";
            std::cout <<"But remember, if you can not guess it right, you will lose the game.You only have one shot. Use it wisely :)" <<std::endl;
            std::cout <<"6- And last but not least, do not forget to have fun :) Good luck and enjoy the game!" <<std::endl;
            std::cout <<"Press any key to continue..." <<std::endl;
            std::cin >> user_word_guess;
            system("cls");
            break;
          
        default:
            std::cout << "Invalid choice, please try again";
            in_game = 2;
            break;
        }
        
        while(user_choice > 0 && user_choice<=5 ){

            int user_guess_type;
            distrib = std::uniform_int_distribution <> (0, selected_array_size - 1);
            current_word_index = distrib(rng);
            current_word = *(selected_array + current_word_index);
            int win_flag = 0;
            char user_letter_guess;
            int *p_match_array {new(std::nothrow) int[current_word.length()]{}};
            int wrong_guesses = 9;
            int* p_wrong_guesses = &wrong_guesses;

            for(size_t i = 0; i < current_word.length(); i++){
                if (current_word[i] == ' '){
                   p_match_array[i] = 1;
                }
            }

            print_word(current_word, p_match_array);

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

                    system("cls");
                    user_letter_guess = std::toupper(user_letter_guess);
                    guess_a_letter(current_word, user_letter_guess, p_match_array, p_wrong_guesses);
                    win_flag = is_win(p_match_array, current_word.length());
                    print_word(current_word, p_match_array); 
                    drawHangman(9- wrong_guesses);

                } else if(user_guess_type == 2){

                    std::cout << "Enter your guess: ";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    std::getline(std::cin, user_word_guess);
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

            while (!(std::cin >> user_choice)) {
                    std::cout << "Invalid input. Please enter a number: ";
                    std::cin.clear(); 
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining characters
            }

            switch (user_choice) {
                case 1:
                    std::cout << "";
                    break;
                case 2:
                    user_choice = 10;
                    break;
                case 0:
                    in_game = 0;
                    break;
                default:
                    std::cout << "Invalid input. Returning to the main menu." << std::endl;
                    Sleep(680);
                    user_choice = 10;
                    break;                 
                    
            }
            system("cls");
            
            delete [] p_match_array;
            p_match_array = nullptr;
        }
    }
        std::cout << "That was fun!! See you again :)";  
        Sleep(680);
        return 0;
}


