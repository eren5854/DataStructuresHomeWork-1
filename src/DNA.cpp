/**
* @file DNA.cpp
* @description DNA.txt dosyasından aldığı kromozomları çaprazlayan, 
*              genleri mutasyon işlemine tabi tutan, otomatik işlemler yapan ve 
*              ekrana yazdırma işlemini yapan program.
* @course 1. Öğretim A Grubu
* @assignment 1. Ödev
* @date 15.11.2024
* @author İhsan Eren Delibaş eren.delibas@ogr.sakarya.edu.tr
*/

#include "../include/DNA.h"
#include <fstream>
#include <iostream>
#include <string>

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

DNA::DNA() : head(nullptr) {}

void DNA::addChromosome(const std::string& chromosome) {
    std::string modifiedChromosome = chromosome;
    removeSpaces(modifiedChromosome);

    Node* newNode = new Node(modifiedChromosome);
    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

void DNA::crossOver(int idx1, int idx2) {
    Node* chrom1 = head;
    Node* chrom2 = head;

    for (int i = 0; i < idx1 && chrom1; ++i) chrom1 = chrom1->next;
    for (int i = 0; i < idx2 && chrom2; ++i) chrom2 = chrom2->next;

    if (!chrom1 || !chrom2) {
        std::cerr <<RED<< "Invalid index!!\n"<<RESET;
        return;
    }
    std::cout<<CYAN<<"1. selected chromosome: "<<RESET<<chrom1->chromosome<<std::endl;
    std::cout<<CYAN<<"2. selected chromosome: "<<RESET<<chrom2->chromosome<<std::endl;

    int len1 = chrom1->chromosome.size();
    int len2 = chrom2->chromosome.size();
    
    int mid1 = len1 / 2;
    int mid2 = len2 / 2;

    std::string part1a = chrom1->chromosome.substr(0, mid1);
    std::string part1b = chrom1->chromosome.substr(mid1 + (len1 % 2));

    std::string part2a = chrom2->chromosome.substr(0, mid2);
    std::string part2b = chrom2->chromosome.substr(mid2 + (len2 % 2));

    std::string newChrom1 = part1a + part2b;
    std::string newChrom2 = part1b + part2a;

    addChromosome(newChrom1);
    addChromosome(newChrom2);

    std::cout<<GREEN<<"Crossover is succesfully."<<RESET<<std::endl;
    std::cout<<BLUE<<"New chromosomes: "<<RESET<<std::endl;
    std::cout<<newChrom1<<std::endl<<newChrom2<<std::endl;
    saveToFile("DNA.txt");
}

void DNA::mutate(int row, int col) {
    Node* current = head;
    int currentIndex = 0;

    while (current && currentIndex < row) {
        current = current->next;
        currentIndex++;
    }

    if (!current) {
        std::cerr<< RED << "Invalid row number!!\n"<<RESET;
        return;
    }

    if (col < 0 || col >= current->chromosome.size()) {
        std::cerr<< RED << "Invalid column number!!\n"<<RESET;
        return;
    }

    std::cout<<"Current chromosome: "<<current->chromosome<<std::endl;

    current->chromosome[col] = 'X';
    std::cout<< GREEN << "Mutate is succesfully"<< RESET <<std::endl;
    std::cout<<BLUE<<"New chromosome: " << RESET<< current->chromosome << std::endl;
    saveToFile("DNA.txt");

}

void DNA::processOperations(const std::string& operationsFile) {
    std::cout<< BLUE << "Auto process file is opening...\n"<<RESET<<std::endl;
    std::ifstream file(operationsFile);
    if (!file.is_open()) {
        std::cerr<< RED << "Auto process file not open!!.\n"<<RESET;
        return;
    }

    std::cout << GREEN << "Auto process file open is succesfully." << RESET << std::endl;

    char operationType;
    int row1, row2;
    int count = 1;
    while (file >> operationType >> row1 >> row2) {
        if (operationType == 'C') {
            std::cout<<MAGENTA<<count <<". process: "<<RESET<<BLUE<< "Crossover" <<RESET<<std::endl;
            crossOver(row1, row2);
        } else if (operationType == 'M') {
            std::cout<<MAGENTA<<count <<". process: "<<RESET<<BLUE<< "Mutate" <<RESET<<std::endl;
            mutate(row1, row2);
        } else {
            std::cerr<<RED << "Unknown transaction type: " <<RESET<< operationType << "\n";
        }
        std::cout<<MAGENTA<<"-----------------------------------------"<<RESET<<std::endl;
        count++;
    }
    count = 1;
    file.close();
}

void DNA::writeToScreen() {
    Node* temp = head;
    std::string result;

    while (temp) {
        const std::string& chromosome = temp->chromosome;

        if (chromosome.empty()) {
            temp = temp->next;
            continue;
        }

        char firstGene = *chromosome.begin();
        char selectedGene = firstGene;

        for (auto it = chromosome.rbegin(); it != chromosome.rend(); ++it) {
            if (*it < firstGene) {
                selectedGene = *it;
                break;
            }
        }

        result += selectedGene;
        temp = temp->next;
    }

    std::cout << result << std::endl;
}


void DNA::loadFromFile(const std::string& filename) {
    clearPopulation();
    std::ifstream file(filename);
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            removeSpaces(line);
            addChromosome(line);
        }
        file.close();
    } else {
        std::cerr << "File not open.\n";
    }
}

void DNA::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        Node* temp = head;
        while (temp) {
            std::string spacedChromosome;
            for (char ch : temp->chromosome) {
                spacedChromosome += ch;
                spacedChromosome += ' ';
            }
            file << spacedChromosome << std::endl;
            temp = temp->next;
        }
        file.close();
        std::cout<< GREEN << "The population was recorded in the "<< RESET << YELLOW << filename << RESET << GREEN <<" file." << RESET << std::endl;
    } else {
        std::cerr<<RED << "File not open: " << RESET << filename << std::endl;
    }
}

void DNA::clearPopulation() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void DNA::removeSpaces(std::string& chromosome) {
    std::string temp;
    for (char ch : chromosome) {
        if (ch != ' ') {
            temp += ch;
        }
    }
    chromosome = temp;
}


void DNA::printPopulation() {
    Node* temp = head;
    int lineNumber = 0;
    
    while (temp) {
        std::cout << lineNumber << " - " << temp->chromosome << std::endl;
        temp = temp->next;
        lineNumber++;
    }
}



