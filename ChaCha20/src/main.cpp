// Autor:Josep Gabino Rodríguez
//  g++ -std=c++11 -o main main.cc
// make run Compila y ejecuta

#include <iostream>
#include <stdint.h> 
#include <string.h> 
#include <inttypes.h>
#include <math.h>
#include <sstream>

// Rota el entero 'a' de 32 bits 'b' bits a la izquierda
#define RtoL(a, b) \
        ((a << b) | (a >> (32 - b)))

// Definicion de la funcion Quarter-Round del ChaCha20
#define chachaQR(a, b, c, d)   (  \
    a += b, d ^= a, d = RtoL(d, 16), \
    c += d, b ^= c, b = RtoL(b, 12), \
    a += b, d ^= a, d = RtoL(d,  8), \
    c += d, b ^= c, b = RtoL(b,  7))

// Imprimimos el vector
void
PrintVector(uint32_t var[]) {
    int count = 0;
    for(int index = 0; index < 16; index++ ) {
        std::cout<<std::hex<<var[index]<< " ";
        count ++;
        if(count >= 4) {
            std::cout<<std::endl;
            count = 0;
        }
    } 
}

// Sacamos el caracter  correspondiente
int caracterHexadecimalADecimal(char caracter) {
  if (isdigit(caracter))
    return caracter - '0';
  return 10 + (toupper(caracter) - 'A');
}

// Convertimos de Hexadecimal a decimal
unsigned long long 
hexadecimalADecimal(std::string cadenaHexadecimal, int longitud) {
  unsigned long long decimal = 0;
  int potencia = 0;
  for (int i = longitud - 1; i >= 0; i--) {
    // Obtener el decimal, por ejemplo para A es 10, para F 15 y para 9 es 9
    // Elevar 16 a la potencia que se va incrementando, y multiplicarla por el
    // valor
    unsigned long long elevado = pow(16, potencia) * caracterHexadecimalADecimal(cadenaHexadecimal[i]);;
    // Agregar al número
    decimal += elevado;
    // Avanzar en la potencia
    potencia++;
  }
  return decimal;
}
// Filtramos la entrada pasada por parámetros
std::string
filtrarEntrada(std::string str) {
    std::string new_str;
    for(int i = 0; i < str.length(); i++) {
        switch (str[i])
        {
            case ':':
            break;
            case ' ':
                new_str.push_back(' ');
            break;
            default:    
                new_str.push_back(str[i]);
            break;
        }
    }
    return new_str;
}
void
LitleEndian(std::string new_str, uint32_t almacen[]) {
    std::string lectura;
    int count = 0;
    std::stringstream input_stringstream(new_str);// Convertir la cadena a un stream
    while (getline(input_stringstream, lectura, ' '))
    {
        uint32_t x = hexadecimalADecimal(lectura, lectura.size());
        almacen[count]=__builtin_bswap32(x);
        count ++;
    } 
}
int main() {
    // Inicializamos el tamño de los campos de la matrix
    uint32_t chachaKey[8],        // 8 palabras
             chachacount [1],    // 1 palabra
             chachaNonce[3],    // 3 palabras
             InitialState[16],
             FinalState[16];  // 16 palabras
    uint32_t chachaConst[4] = // 4 palabras
        { 
            0x61707865,
            0x3320646e,
            0x79622d32,
            0x6b206574
        };
    std::string str, new_str;

    // Recogemos los datos
    std::cout<<"Introduzcla la clave de 256 bits"<<std::endl; // Litle Endian
    std::cin.ignore();
    std::getline(std::cin,str);
    new_str = filtrarEntrada(str);
    LitleEndian(new_str, chachaKey);               

    std::cout<<"Introduzcla contador de 32 bits"<<std::endl;
    std::getline(std::cin,str);
    new_str = filtrarEntrada(str);
    LitleEndian(new_str, chachacount);

    std::cout<<"Introduzca Nonce de 96 bits"<<std::endl;
    std::getline(std::cin,str);
    new_str = filtrarEntrada(str);
    LitleEndian(new_str, chachaNonce);

    // Copiamos en la matrix los respectivos campos
    memcpy(&InitialState, chachaConst, sizeof(chachaConst)); // 4 x 32 = 128 en bytes = 16 CONSTANTES
    memcpy(&InitialState[4], chachaKey, sizeof(chachaKey)); // 8 x 32 = 256 en bytes = 32 CLAVE LITLE ENDIAN
    memcpy(&InitialState[12], chachacount, sizeof(chachacount)); // Contador LITLE ENDIAN
    memcpy(&InitialState[13], chachaNonce, sizeof(chachaNonce)); // NONCE LITLE ENDIAN

    std::cout<<"=========Estado Inicial========="<<std::endl;
    PrintVector(InitialState);

    // Hacemos una copia para luego sumarla al final
    memcpy(FinalState, InitialState, sizeof(InitialState)); // 16x32 = 512 en bytes = 64

    // Iteramos 20 veces 
    for(int i = 0; i < 20; i+=2)
    {
        chachaQR(InitialState[0], InitialState[4],  InitialState[8], InitialState[12]);
        chachaQR(InitialState[1], InitialState[5], InitialState[9], InitialState[13]);
        chachaQR(InitialState[2], InitialState[6], InitialState[10], InitialState[14]);
        chachaQR(InitialState[3], InitialState[7], InitialState[11], InitialState[15]);
        chachaQR(InitialState[0], InitialState[5], InitialState[10], InitialState[15]);
        chachaQR(InitialState[1], InitialState[6], InitialState[11], InitialState[12]);
        chachaQR(InitialState[2], InitialState[7], InitialState[8], InitialState[13]);
        chachaQR(InitialState[3], InitialState[4], InitialState[9], InitialState[14]);
    }
    std::cout<<"=========Estado final tras las 20 iteraciones =========="<<std::endl;

    PrintVector(InitialState);

    // Sumamos la copia al estado Final
    std::cout<<"=========Estado de salida del generador========="<<std::endl; 
    for(int i = 0; i< 16; i++) {
        FinalState[i] = InitialState[i] + FinalState[i];
    }
    PrintVector(FinalState);  
}