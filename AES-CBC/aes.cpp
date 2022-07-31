/**
 * @file main.cpp
 * @author Joseph Gabino Rodríguez (alu0101329161@ull.edu.es)
 * @brief 
 * @version 0.1
 * @date 2022-03-28
 * 
 * @copyright Copyright (c) 2022
 * https://www.youtube.com/watch?v=tzj1RoqRnv0&t=74s
 * 
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>

using std::cout; using std::cin;
using std::endl; using std::string;

// Almacenamos la clave, mensaje, mensaje cifrado en un vector de caracteres
std::vector<std::vector<unsigned char>> clave_, texto_, texto_2, iv_, texto_cf_;
// Almacenamos la clave expandida en un vector de caracteres
std::vector<std::vector<std::vector<unsigned char>>> clave_exp_;
// Indicamos la iteracion actual
unsigned int iter_ = 0;

int cantidad_guiones = 0;

// Caja S para realizar sustituciones
unsigned char cajaS_[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

// Caja para Rcon para aplicar xor en las subclaves
unsigned char cajaRcon_[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

// Generamos las 10 subclaves
void 
GenerarSubclaves(void){
	unsigned char aux_columna[4],aux;

	// Asigamos tamaño a la clave espandida
	for (int i=0; i<11; i++)
    	clave_exp_[i].resize(4, std::vector<unsigned char>(4));

	// auxmos la clave original en la primera posicion de nuestro clave_exp_
	for (auto i=0; i<4; i++){
		for (auto j=0; j<4; j++)
			clave_exp_[0][j][i] = clave_[j][i];
	}

	// Generamos las subclaves ROOTWORD SUBYTE Y XOR ENTRE CLAVE, COLUMNA Y RCON
	for (auto i=1; i <= 10; i++){

		//En el caso de la primera columna de cada columna, auxmos la columna anterior en una variable de aux
		for (auto j=0; j<4; j++)
			aux_columna[j]=clave_exp_[i-1][j][3];

		// RootWord
		aux = aux_columna[0];
		aux_columna[0] = aux_columna[1];
		aux_columna[1] = aux_columna[2];
		aux_columna[2] = aux_columna[3];
		aux_columna[3] = aux;

		// SubByte
		aux_columna[0] = cajaS_[aux_columna[0]];
		aux_columna[1] = cajaS_[aux_columna[1]];
		aux_columna[2] = cajaS_[aux_columna[2]];
		aux_columna[3] = cajaS_[aux_columna[3]];

		// Rcon
		aux_columna[0] ^= cajaRcon_[i -1];

		// Tenemos que sustituir los bytes de la clave expandida con los de la matriz anterior de la clave expandida
		// y con los bytes calculados realizando un XOR
		clave_exp_[i][0][0] = clave_exp_[i-1][0][0] ^ aux_columna[0];
		clave_exp_[i][1][0] = clave_exp_[i-1][1][0] ^ aux_columna[1];
		clave_exp_[i][2][0] = clave_exp_[i-1][2][0] ^ aux_columna[2];
		clave_exp_[i][3][0] = clave_exp_[i-1][3][0] ^ aux_columna[3];

		// Recorremos las columnas de la 2 a la 3
		for (auto j=1; j<4; j++){
			// Recorremos cada fila copiando en una variable auxiliar la columna de la matriz anterior
			for (auto k=0; k<4; k++){
				aux_columna[k]=clave_exp_[i-1][k][j];
			}
			// Recorremos cada fila de la matriz de la clave expandida, almacenando en ella el resultado de aplicar un XOR 
            // entre la columna anterior y la de la matriz anterior
			for (auto k=0; k<4; k++){
				clave_exp_[i][k][j] = clave_exp_[i][k][j-1] ^ aux_columna[k];
			}
		}
	}
}


// Metodo que aplica una XOR al texto cifrado con la clave expandida
void 
addRoundKey(void) {
	for (auto i=0; i<4; i++)
		for (auto j=0; j<4; j++)
			texto_cf_[j][i] ^= clave_exp_[iter_][j][i];		
}

//Metodo que sustituye un byte del texto cifrado por su correspondiente en la Caja S
void
subBytes(void) {
	for (auto i=0; i<4; i++)
		for (auto j=0; j<4; j++)
			texto_cf_[j][i] = cajaS_[texto_cf_[j][i]];
}

//Metodo que mueve bytes a la izquierda las matrices del texto cifrado
void 
shiftRow(void){
    // Elemento que va a servir para gaurdar valores temporalmente
	unsigned char aux;

    // Muevo el primer byte al final
	aux = texto_cf_[1][0];
	texto_cf_[1][0] = texto_cf_[1][1];
	texto_cf_[1][1] = texto_cf_[1][2];
	texto_cf_[1][2] = texto_cf_[1][3];
	texto_cf_[1][3] = aux;

    // Muevo los dos primeros byte al final
	aux = texto_cf_[2][0];
	texto_cf_[2][0] = texto_cf_[2][2];
	texto_cf_[2][2] = aux;
	aux = texto_cf_[2][1];
	texto_cf_[2][1] = texto_cf_[2][3];
	texto_cf_[2][3] = aux;

    // Muevo los tres primeros bytes al final
	aux = texto_cf_[3][0];
	texto_cf_[3][0] = texto_cf_[3][3];
	texto_cf_[3][3] = texto_cf_[3][2];
	texto_cf_[3][2] = texto_cf_[3][1];
	texto_cf_[3][1] = aux;
}

// Metodo que aplica una transformacion lineal al texto cifrado
void 
mixColumn(void){

	// Copias del texto cifrado
	unsigned char a[4];
    // Array 'a' multiplicando por 2 cada elemneto de a
	unsigned char b[4];
	unsigned char h;

	//Doble bucle para recorrer una matriz completa de una sola llamada al metodo
	for (auto i=0; i<4; i++){
		for (auto j=0; j<4; j++){
			//Copiamos en a el texto cifrado
			a[j] = texto_cf_[j][i];

			//Multiplicacion entre el byte del texto cifrado y 128 para comprobar si el byte del texto es mayor que 128
			h = texto_cf_[j][i] & 0x80; 

			//Multiplicamos por 2 (desplazamos un byte) el byte del texto cifrado y lo dejamos en la variable auxiliar b
			b[j] = texto_cf_[j][i] << 1;

			//En caso de que el byte sea mayor de 127 aplicamos una XOR con 27
			if(h == 0x80)
				b[j] = b[j] ^0x1b;
		}

		//Realizamos todas las XOR correspondientes para cada uno de los elementos de nuestra columna, ya que cada fila tiene un valor distinto
		texto_cf_[0][i] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
		texto_cf_[1][i] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
		texto_cf_[2][i] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];
		texto_cf_[3][i] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
	}
}

// Metodo que imprime el texto cifrado y las subclaves
void
Print(void){
	// Impirmir texto cifrado
	std::cout << std::endl << "Texto cifrado:  ";
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++)
			std::cout << std::hex << std::setfill('0') << std::setw(2) << int(texto_cf_[j][i]);
	}
	// Impirmir clave
	std::cout << "  Subclave " << iter_ << ":     ";
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++)
			std::cout << std::hex << std::setfill('0') << std::setw(2) << int(clave_exp_ [iter_][j][i]);
	}
}

// Metodo que se encarga de llamar a los metodos para realizar el encriptado completo
void 
encriptar(void){

	addRoundKey();
	Print();// Imprimimos la primera matrix de claves y texto cifrado

	//Llamamos a cada metodo por separado 9 veces. Se aumenta el contador de iteraciones, necesario para moverse por la clave expandida
	for (auto i=1;i<10;i++){
		iter_++;
		subBytes();
		shiftRow();
		mixColumn();
		addRoundKey();
		Print();
	}
	//En la ultima iteracion aplicamos los mismos metodos que antes, salvo que ahora no realizamos 
	iter_++;
	subBytes();
	shiftRow();
	addRoundKey();
	Print();
	std::cout << std::endl;
	iter_ = 0;
}


void 
RecibirEntrada() {
	std::string str, new_str;
    std::cout<<"Introduzcla la clave 16 bytes en hexadecimal"<<std::endl;
    std::getline(std::cin,str);
    std::vector<std::vector<unsigned char>> clave(4, std::vector<unsigned char>(4));
    str = "00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F";
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
    
    
	// Guardar los valores de str en la clave
	for (size_t i = 0; i < str.size(); i+=2) {
		std::string byte = str.substr(i, 2);
		unsigned char c = (unsigned char)strtol(byte.c_str(), NULL, 16);
		clave[i/2%4][i/2/4] = c;
	}
	
	std::vector<std::vector<unsigned char>> vectorIV(4, std::vector<unsigned char>(4));
	std::cout<<"IV: (16 bytes en hexadecimal)"<<std::endl;
    std::getline(std::cin,str);
    str = "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00";
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
    
    // Guardar los valores de str en el texto
	for (size_t i = 0; i < str.size(); i+=2) {
		std::string byte = str.substr(i, 2);
		unsigned char c = (unsigned char)strtol(byte.c_str(), NULL, 16);
		vectorIV[i/2%4][i/2/4] = c;
	}
    
    std::vector<std::vector<unsigned char>> texto(4, std::vector<unsigned char>(4));
	std::cout<<"Bloque de Texto 1(16 bytes en hexadecimal)"<<std::endl;
    std::getline(std::cin,str);
    str = "00 11 22 33 44 55 66 77 88 99 AA BB CC DD EE FF";
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());

	// Guardar los valores de str en el texto
	for (size_t i = 0; i < str.size(); i+=2) {
		std::string byte = str.substr(i, 2);
		unsigned char c = (unsigned char)strtol(byte.c_str(), NULL, 16);
		texto[i/2%4][i/2/4] = c;
	}
	
	std::vector<std::vector<unsigned char>> texto2(4, std::vector<unsigned char>(4));
	std::cout<<"Bloque de Texto 2(16 bytes en hexadecimal)"<<std::endl;
    std::getline(std::cin,str);
    str = "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 --";
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());

	// Guardar los valores de str en el texto
	for (size_t i = 0; i < str.size(); i+=2) {
		std::string byte = str.substr(i, 2);
		if(byte == "--") {
		    texto2[i/2%4][i/2/4] = 0;
		} else {
    		unsigned char c = (unsigned char)strtol(byte.c_str(), NULL, 16);
    		texto2[i/2%4][i/2/4] = c;
    		cantidad_guiones ++;
		}
	}


	// Guardar los valores obtenidos en las variables globales
    clave_ = clave;
    texto_ = texto;
    texto_2 = texto2;
    texto_cf_ = texto;
    iv_ = vectorIV;
    clave_exp_.resize(11);
}

int main() {
    int eleccion = 1;
    std::cout << "Desea CBC con[1] o sin Stealing[2]"<<std::endl;
    std::cin>>eleccion;
    std::cin.ignore();
    if(eleccion == 2) {
        std::cout << "---Practica 6 AES AND CBC----"<<std::endl;
    	RecibirEntrada();
    	//En la iteracion 0 solo expandimos la clave(10 subclaves) y aplicamos una XOR al texto cifrado con la clave expandida
    	GenerarSubclaves();
    	// Realizamos xor entre vectorIV y Bloque 1
    	for (auto i=0; i<4; i++)
    	    for (auto j=0; j<4; j++)
    		texto_cf_[j][i] ^= iv_[j][i];	
    	// Aplicamos AES
    	encriptar();
    	// Actualizamos el nuevo anterior
    	iv_ = texto_cf_;
    	std::cout << std::endl << "Bloque 1 texto cifrado:  ";
    	for (int i=0; i<4; i++){
    		for (int j=0; j<4; j++)
    			std::cout << std::hex << std::setfill('0') << std::setw(2) << int(texto_cf_[j][i]);
    	}
    	// Xor entre nuevoIV y Bloque 2
    	for (auto i=0; i<4; i++)
    	  for (auto j=0; j<4; j++)
    	  iv_[j][i] ^= texto_2[j][i];	
    	texto_cf_ = iv_;
    	encriptar();
    	std::cout << std::endl << "Bloque 2 texto cifrado:  ";
    	for (int i=0; i<4; i++){
    		for (int j=0; j<4; j++)
    			std::cout << std::hex << std::setfill('0') << std::setw(2) << int(texto_cf_[j][i]);
    	}
		std::cout<< " "<<std::endl;
    } else {
	
    	std::cout << "---Practica 6 Cipher stealing ----"<<std::endl;
    	RecibirEntrada();
    	//En la iteracion 0 solo expandimos la clave(10 subclaves) y aplicamos una XOR al texto cifrado con la clave expandida
    	GenerarSubclaves();
    	// Realizamos xor entre vectorIV y Bloque 1
    	for (auto i=0; i<4; i++)
    	    for (auto j=0; j<4; j++)
    		texto_cf_[j][i] ^= iv_[j][i];	
    	// Aplicamos AES
    	encriptar();
    	// Actualizamos el nuevo anterior
    	iv_ = texto_cf_;
    	int contador = 0;
    	std::cout << std::endl << "Bloque 2 texto cifrado:  ";
    	for (int i=0; i<4; i++) {
    		for (int j=0; j<4; j++) {
    		    if(contador < cantidad_guiones) {
    			std::cout << std::hex << std::setfill('0') << std::setw(2) << int(texto_cf_[j][i]);
    		    } else {
    		        std::cout << "--";
    		    }
    			contador ++;
    			
    		}
    	}
    	// Xor entre nuevoIV y Bloque 2
    	for (auto i=0; i<4; i++)
    	  for (auto j=0; j<4; j++)
    	  iv_[j][i] ^= texto_2[j][i];	
    	texto_cf_ = iv_;
    	encriptar();
    	std::cout << std::endl << "Bloque 1 texto cifrado:  ";
    	for (int i=0; i<4; i++){
    		for (int j=0; j<4; j++)
    			std::cout << std::hex << std::setfill('0') << std::setw(2) << int(texto_cf_[j][i]);
    	}
    }
	std::cout<< " "<<std::endl;
}
