/**
* @file DNA.h
* @description DNA.txt dosyasından aldığı kromozomları çaprazlayan, 
*              genleri mutasyon işlemine tabi tutan, otomatik işlemler yapan ve 
*              ekrana yazdırma işlemini yapan program.
* @course 1. Öğretim A Grubu
* @assignment 1. Ödev
* @date 15.11.2024
* @author İhsan Eren Delibaş eren.delibas@ogr.sakarya.edu.tr
*/

#ifndef DNA_H
#define DNA_H

// #include <string>
// #include <vector>

#include <iostream>
using namespace std;

class DNA {
public:
    DNA();
    void addChromosome(const string& chromosome);
    void crossOver(int idx1, int idx2);
    void printPopulation();
    void loadFromFile(const string& filename);
    void mutate(int row, int col);
    void saveToFile(const string& filename);
    void clearPopulation();
    void removeSpaces(string& chromosome);
    void processOperations(const string& operationsFile);
    void writeToScreen();

private:
    struct Node {
        string chromosome;
        Node* next;
        Node(const string& c) : chromosome(c), next(nullptr) {}
    };
    
    Node* head;
};

#endif
