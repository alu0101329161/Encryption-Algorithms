// Autor: Joseph Gabino Rodríguez
// g++ -std=c++11 -o prueba RC4.cc RC4.h

#include <vector>
#include <iostream>
#include <iomanip>
#include <bitset>

// Clase implementada para aplicar el cifrado RC4 mediante los algoritmos 
// KSA que inicializa los dos vector y realiza el intercambio de posiciones
// y el algoritmo PRGA que nos permite hallar la secuencia para luego aplicar
// la operacion de XOR
class rc4{

    public:

        rc4(std::vector<uint8_t> key);
        ~rc4 (void);
        
        void KeyShedulingAlgorithm (std::vector<uint8_t> key);
        std::vector<uint8_t> CipherSequenceGeneration(std::vector<uint8_t> mensaje);
        std::vector<uint8_t> GetEndKey (void);
        void PrintVector(std::vector<uint8_t> data);

    private:

        std::vector<uint8_t> S_{0}; // Vector con los numeros de 0 a 255
        std::vector<uint8_t> K_{0}; // Vector que almacena la llave repitiendo hasta la posicion 255
        std::vector<uint8_t> end_box_{0}; // Vector con la clave de cifrado
};