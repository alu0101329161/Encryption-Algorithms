/* Autor: Joseph Gabino Rdríguez
Compilacion y ejecución: make run */
#include <bitset>
#include <iostream>
#include <math.h>
#include<string> 
#include<vector> 

// Tipo de algoritmo utilizado
static int opcion;
// Byte de algoritmo SNOW3G
static std::bitset<8> snow3G("10101001");
// Byte de algoritmo AES
static std::bitset<8> AES("00011011");
// Almacenamos el resultado para luego sumarlos
static std::vector<std::bitset<8>> resultado;

// Realizamos 8 desplazamientos
void
Desplazamiento(std::bitset<8>& byte1, std::bitset<8>& byte2, int travel) {
    bool especial = false;
    if(byte1[7] == 1) {especial = true;} // Comprobamos si el bit más significativo es uno
    byte1<<=1; // Desplazamiento a la izquierda
    if(especial) { // Reducimos en modulo
        if(opcion == 0) {
            byte1 = byte1 ^ snow3G;
        } else {
            byte1 = byte1 ^ AES;
        }
    }
    if(byte2[travel] == 1) {{resultado.push_back(byte1);}} // Nos interesa el resultado
}

// Calculamos el producto e imprimimos
void
Producto(std::bitset<8>& byte1, std::bitset<8>& byte2) {

    if(byte2[0] == 1){ resultado.push_back(byte1);} // Si es uno no hay desplazamiento y guardamos el resultado

    for(int travel = 1; travel < 8; travel++){ // Realizamos los 8 desplazamientos
        Desplazamiento(byte1, byte2, travel);
    }
    for(int travel = 0; travel < resultado.size(); travel++ ) {
        std::cout<< resultado[travel] << " ";
    }
    std::cout<< ""<< std::endl;

    // Creamos bitset donde almacenar
    std::bitset<8> result;
    result = resultado[0];
    std::cout<< resultado[0]<< std::endl;

    for(int travel = 1; travel < resultado.size(); travel++ ) {
        std::cout<< result << "^" << resultado[travel]<< std::endl;
        result = result ^ resultado[travel];
        std::cout<< result << std::endl;
    }
    std::cout<<"Multiplicacion: "<< result << " " << result.to_ulong()<< std::endl;
}

int main() {

    // Parámetros de entrada
    int input1, input2;
    // Primer byte de entrada y conversion a decimal y luego binario
    std::cout << "Introduzca el primer Byte" << std::endl;
    std::cin>>std::hex>>input1;
    std::bitset<8> byte1(input1);
    // Segundo byte de entrada y conversion a binario y luego binario
    std::cout << "Introduzca el segundo Byte" << std::endl;
    std::cin>>std::hex>>input2;
    std::bitset<8> byte2(input2);
    // Eleccion del tipo de algoritmo
    std::cout << "SNOW3G[0] O AES[1]" << std::endl;
    while(true) {
        std::cin>>opcion;
        if(opcion == 0 || opcion == 1){break;}
        std::cout<<"Vuelva a intentarlo: "<<std::endl;
    }

    std::cout<<"RESULTADO: "<<std::endl;
    // Realizamos la operacion entre los dos operadores
    std::cout<<"Byte [ byte1 ]: " << byte1 << std::endl;
    std::cout<<"Byte [ byte2 ]: " << byte2 << std::endl;
    if(opcion == 1) {
        std::cout<<"Byte [ Algorimto ]: " << AES << std::endl;
    } else {
        std::cout<<"Byte [ Algorimto ]: " << snow3G << std::endl;
    }
    Producto(byte1, byte2);
}