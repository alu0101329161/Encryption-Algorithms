// Autor: Joseph Gabino Rodríguez
// g++ -std=c++11 -o prueba main.cc RC4.cc RC4.h

#include "RC4.h"


int main(void) {

    std::vector<uint8_t> msg_cifrado;
    int size,value,type;
    srand(time(NULL));

    std::cout<< "Introduzca el tamaño del mensaje original"<<std::endl;
    std::cin>>size;

	std::vector<uint8_t> msg(size, 0);
        for(int travel = 0; travel <= size-1; travel++) {
            std::cout<<"mensaje["<<travel<<"] = ";
            std::cin>>value;
            msg[travel] = value;
        }

    std::cout<< "Generacion aleatoria[1] o manual [2]"<<std::endl;
    std::cin>>type;


    std::vector<uint8_t> semilla(size, 0);
    if(type == 1) {
            for(int travel = 0; travel <= size-1; travel++) {
                semilla[travel] = rand()%255;
            }
    } else {
        for(int travel = 0; travel <= size-1; travel++) {
            std::cout<<"semilla["<<travel<<"] = ";
            std::cin>>value;
            if(value > 255) {
                std::cout<< "Numero fuera del limite será reemplazado por otro"<<std::endl;
            }
            semilla[travel] = value;
        }
    }
    int pausar = 0;

    // Llamamos al constructor inicializando los vectores
	rc4 A(semilla);

	std::cout << "El mensaje original es: ";
    A.PrintVector(msg);
	std::cout << std::endl << "La semilla es: ";
    A.PrintVector(semilla);

    // Ejecución de la traza
	std::cout<<"=======Inicializacion======="<<std::endl;
	A.KeyShedulingAlgorithm(semilla);
	std::cout<<"=======Generación de secuencia cifrante y texto cifrado======="<<std::endl;
	msg_cifrado = A.CipherSequenceGeneration(msg);
	std::cout<<"============"<<std::endl;

    // Mensaje cifrado y clave de cifrado real(sacada de la semilla) 
	std::cout << std::endl << "La clave de cifrado es: ";
    A.PrintVector(A.GetEndKey());
	std::cout << std::endl << "El mensaje cifrado es: ";
    A.PrintVector(msg_cifrado);
}

