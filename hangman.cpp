#include "hangman.h"
#include <iostream>
#include <string>
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

