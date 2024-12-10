/**
* @file main.cpp
* @description DNA.txt dosyasından aldığı kromozomları çaprazlayan, 
*              genleri mutasyon işlemine tabi tutan, otomatik işlemler yapan ve 
*              ekrana yazdırma işlemini yapan program.
* @course 1. Öğretim A Grubu
* @assignment 1. Ödev
* @date 15.11.2024
* @author İhsan Eren Delibaş eren.delibas@ogr.sakarya.edu.tr
*/

#include "../include/DNA.h"
#include <iostream>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"

void displayMenu()
{
    std::cout << CYAN << BOLD << "---- DNA Operations Menu ----" << RESET << std::endl;
    std::cout << YELLOW << "1 - " << GREEN << "View DNA.txt file" << RESET << std::endl;
    std::cout << YELLOW << "2 - " << GREEN << "Crossover" << RESET << std::endl;
    std::cout << YELLOW << "3 - " << GREEN << "Mutate" << RESET << std::endl;
    std::cout << YELLOW << "4 - " << GREEN << "Auto process (Islemler.txt)" << RESET << std::endl;
    std::cout << YELLOW << "5 - " << GREEN << "Print to screen" << RESET << std::endl;
    std::cout << YELLOW << "0 - " << RED << "Exit" << RESET << std::endl;
    std::cout << BLUE << UNDERLINE << "Enter your choice: " << RESET;
}

int main()
{
    std::system("cls");
    DNA dna;
    int choice;
    std::string filename = "DNA.txt";
    std::string operationFile = "Islemler.txt";

    while (true)
    {
        displayMenu();
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            std::system("cls");
            dna.loadFromFile(filename);
            dna.printPopulation();
            std::cout << GREEN << "DNA.txt file loaded successfully!" << RESET << std::endl;
            dna.clearPopulation();
            break;
        case 2:
            std::system("cls");
            dna.loadFromFile(filename);
            int row1, row2;
            std::cout << MAGENTA << "Enter the row numbers of 2 chromosomes, leaving a space between them (Ex:58 54): " << RESET << std::endl;
            std::cin >> row1 >> row2;
            dna.crossOver(row1, row2);
            dna.clearPopulation();
            break;
        case 3:
            std::system("cls");
            dna.loadFromFile(filename);
            int row, col;
            std::cout << MAGENTA << "Enter the row and column numbers of the selected gene, leaving a space between them (Ex:58 1): " << RESET << std::endl;
            std::cin >> row >> col;
            dna.mutate(row, col);
            dna.clearPopulation();
            break;
        case 4:
            std::system("cls");
            dna.loadFromFile(filename);
            dna.processOperations(operationFile);
            dna.clearPopulation();
            break;
        case 5:
            std::system("cls");
            dna.loadFromFile(filename);
            dna.writeToScreen();
            dna.clearPopulation();
            break;
        case 0:
            std::cout << RED << "Exiting..." << RESET << std::endl;
            dna.clearPopulation();
            std::system("cls");
            return 0;
        default:
            std::cerr << RED << "Invalid option. Try again.\n"
                      << RESET;
            break;
        }
    }
    return 0;
}