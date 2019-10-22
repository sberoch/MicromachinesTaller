//
// Created by alvaro on 28/9/19.
//

#ifndef HONEYPOT_SERVERFILE_H
#define HONEYPOT_SERVERFILE_H


#include <fstream>
#include <unordered_map>

class File {
private:
    std::ifstream readingFile;

    //Abre el archivo a partir del string openingFile.
    void openFile(const std::string& openingFile);
public:
    //Abre el archivo readingFile, a partir del fileName.
    explicit File(const std::string& fileName);

    //Cierra el archivo.
    ~File();

    //Crea un hashmap, a partir de la combinacion clave-valor del archivo.
    std::unordered_map<std::string, std::string> createMap();
};


#endif //HONEYPOT_SERVERFILE_H
