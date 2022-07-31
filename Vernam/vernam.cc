// Autor: Joseph Gabino Rodríguez
// g++ -std=c++11 -o prueba vernam.cc

#include <iostream>
#include <vector>
#include <bitset>


// Convertir el string a binario
std::string 
ConversionBinaries(std::string str) {

    std::string value;
    for (int travel = 0; travel < str.length(); travel++) {

        // Para cada letra uso bitset que lo pasa a binario
        std::bitset<8> bitset(str[travel]);
        // Concateno al final y uso to_string de clase bitset
        value.append(bitset.to_string());

    }
    return value;

}

// Convertir de binario a string
std::string 
ConversionTextNew(std::string str) {

    std::string aux; 
    for (unsigned travel = 0; travel <= str.size() -7; travel += 8) {

        // Cadenas de longitud 8
        std::bitset<8> bit (str.substr(travel, 8));
        // Funcion de la clase bitset que permite cambiar de binario a entero
        aux += char(bit.to_ulong());

    }
    return aux;

}

// Imprimir caracteres fuera del rango de ASCII
std::string 
NonPrintableCharacter(std::string str) {

    std::string value;
    // Para cada letra miro si su codigo ASCII es imprimible
    for (int travel = 0; travel < str.length(); travel++) {
        if(int(str[travel]) >= 32 && int(str[travel]) <= 126)
            value +=str[travel];
        else
            value +='X';
    }
    return value;

}

// Usamos el poerador XOR y encriptamos el mensaje
std::string 
OperatorXor(std::string str, std::string key) {
    
    std::string aux, result;
    for (int travel = 0; travel < str.length(); travel++) {
        // Paso a int y luego a char restando y sumando
        aux = (str[travel] - '0') ^ (key[travel] - '0') + '0';
        result += aux; 
    }
    return result;

}

// Generar clave aleatoria del tamaño del mensaje
std::string
RamdonKey(int size) {

    srand(time(NULL));
    std::string key_random("", size);
    for (int travel = 0; travel < size; travel++) {

        // Paso a char el numero devuelto por rand
        key_random[travel] = rand()%2 + '0';
        
    }
    return key_random;

}

void
AlgorithmVernam(int type) {

    std::string str,key,str_binaries,str_cifrado;
    bool boolean_key = true;

    if(type == 1) std::cout<< "Introduzca mensaje original" << std::endl;
    else          std::cout<< "Introduzca mensaje cifrado" << std::endl;
    std::cin.ignore();
    getline(std::cin,str);
        
    str_binaries = ConversionBinaries(str);
    if(type == 1) std::cout << "Mensaje original en binario: " << str_binaries <<std::endl;
    else          std::cout << "Mensaje cifrado en binario: " << str_binaries <<std::endl;

    std::cout << "Longitud del mensaje en binario: " << str_binaries.size() <<std::endl;


    std::cout << "Introduzca una clave aleatoria o introduzca[1] para clave aleatoria" << std::endl;
    getline(std::cin,key);

    // En caso de que la clave no este en formato boolean lo convertimos
    for(int i = 0; i< key.size(); i ++) {
        if(key[i] == '0' || key[i] == '1') boolean_key = true;
        else boolean_key = false; break;
    }

    if(boolean_key == false) key = ConversionBinaries(key);

    if(key.size() == 1) key = RamdonKey(str.size()*8);

    std::cout << "la clave elegida es: "<< key << std::endl;

    // Si no son del mismo tamaño no podemos aplicar XOR
    if(str_binaries.size() != key.size()) {
        std::cerr << "La clave no es del mismo tamaño que el mensaje" << std::endl;
        exit(1);
    }

    str_cifrado = OperatorXor(str_binaries, key);
    if(type == 1) std::cout << "Mensaje cifrado en binario: " << str_cifrado <<std::endl;
    else          std::cout << "Mensaje original en binario: " << str_cifrado <<std::endl;
    
    // Uso de funcion NonPrintCharacter para no impirmir caracteres no imprimibles
    if(type == 1) std::cout << "Mensaje cifrado en texto: " << NonPrintableCharacter(ConversionTextNew(str_cifrado))<<std::endl;
    else          std::cout << "Mensaje original: " << NonPrintableCharacter(ConversionTextNew(str_cifrado))<<std::endl;
}

int main(void)
{
    int iterative = 1;

    while(iterative == 1 || iterative == 2) {

        std::cout<<"Si quiere Cifrar pulse [1], Descifrar pulse [2], salir [3]"<<"\n\n"<<std::endl;
        std::cin>>iterative;

        if(iterative == 1) AlgorithmVernam(1);
        else if (iterative == 2) AlgorithmVernam(2);
    }
}
