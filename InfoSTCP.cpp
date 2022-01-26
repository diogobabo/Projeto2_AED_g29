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
        std::fstream lineDir;
        std::string nomeFicheiro = "../dataset/line";
        getline(str,code,',');
        getline(str,name,',');
        nomeFicheiro += "_" + code + "_" + "0.csv";

        // LER FICHEIRO 0
        lineDir.open(nomeFicheiro);
        if(!lineDir) {
            exit(EXIT_FAILURE);
        }

        std::string codeStop;
        getline(lineDir,codeStop); // ignorar primeira linha
        while(getline(lineDir,codeStop)) { //aqui dentro crias as linhas
            std::cout << codeStop << std::endl;
        }
        lineDir.close();

        // LER FICHEIRO 1
        nomeFicheiro.replace(nomeFicheiro.size() - 5,1,"1");
        lineDir.open(nomeFicheiro);
        if(!lineDir){
            exit(EXIT_FAILURE);
        }

        getline(lineDir,codeStop); // ignorar primeira linha
        while(getline(lineDir,codeStop)) { //aqui dentro crias as linhas
            std::cout << codeStop << std::endl;
        }
        lineDir.close();
    }
}
