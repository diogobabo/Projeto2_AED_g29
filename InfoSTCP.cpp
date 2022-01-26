//
// Created by Diogo Babo on 25/01/2022.
//

#include "InfoSTCP.h"
#include <fstream>
#include <sstream>
#include <iostream>

void InfoSTCP::readLines(std::string filename) {
    std::fstream lineFile;
    std::fstream lineSpec;
    lineFile.open(filename);
    if(!lineFile) {
        throw "lineFile error";
    }
    std::string s;
    getline(lineFile,s);
    while(getline(lineFile,s)) {
        std::string code,name;
        std::stringstream str(s);
        std::string ff;
        std::fstream lineDirO;
        std::fstream lineDirI;
        std::string nomeFich = "line";
        getline(str,code,',');
        getline(str,name);
        std::cout << code;
        std::cout << name;
        nomeFich += "_" + code;
        std::string nomeFichO = nomeFich; // direcao 0
        std::string nomeFichI = nomeFich; // direcao 1
        nomeFichO += "_0.csv"; // nome ficheiro dir 0 top
        nomeFichI += "_1.csv"; // nome ficheiro dir 1 top
        lineDirO.open(nomeFichO);
        if(!lineSpec) {
            throw "line0 error";
        }
        std::string n;
        getline(lineDirO,n);
        int num = stoi(n);
        for(int i = 0; i < num; i++) {
            std::string codStop;
            std::cout << codStop;
            getline(lineDirO,codStop);
        }
        lineDirI.open(nomeFichI);
        if(!lineDirI.peek() == EOF) {
            getline(lineDirI,n);
            num = stoi(n);
            for(int j = 0; j < num; j++) {
                std::string codStopI;
                std::cout << codStopI;
                getline(lineDirI,codStopI);
            }
        }
    }
}
