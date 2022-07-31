// Autor: Joseph Gabino Rodríguez
// g++ -std=c++11 -o prueba main.cc RC4.cc RC4.h


#include "RC4.h"


// Contructor que almacena la memoria que vamos a ocupar en la
// distintas variables de 0 a 256
rc4::rc4 (std::vector<uint8_t> semilla):
    S_(256, 0),
    K_(256, 0)
{}

// Destructor
rc4::~rc4(void){}

// Algoritmo donde dejamos S_ y k_ con sus respectivos valores y 
// luego realizamos el intercambio de valores para dejar S_
// preparado
void
rc4::KeyShedulingAlgorithm (std::vector<uint8_t> semilla) {

	for (int travel = 0; travel < S_.size();travel++){
		S_[travel] = travel;
		K_[travel] = semilla[travel%semilla.size()];
	}

	std::cout<<"\n"<< "S = ";
	PrintVector(S_);

	std::cout<<"\n"<<"K = ";
	PrintVector(K_);

	int j=0;
	for (int i=0; i<S_.size();i++){

		j = (j+S_[i]+K_[i])%S_.size();
		std::cout<<"S["<<i<<"]="<<int(S_[i])<<" "<<"K["<<i<<"]="<<int(K_[i])<<" produce f= "<<j<<" y ";
		std::swap(S_[i],S_[j]);
		std::cout<<"S["<<i<<"]="<<int(S_[i])<<" "<<"S["<<j<<"]="<<int(S_[j])<<std::endl;
	}

	std::cout<<"\n"<< "S = ";
	PrintVector(S_);

}


// Una vez tenemos S_ podemos comenzar a cifrar el mensaje recorriendo
// el mensaje y por cada posicion hallamos t y en S_(t) es el valor 
// por el cual haremos la operacion XOR con el mensaje
std::vector<uint8_t> 
rc4::CipherSequenceGeneration (std::vector<uint8_t> mensaje) {

	unsigned t = 0, f = 0, i_ = 0;
	std::vector<uint8_t> mensaje_cifrado(mensaje.size(),0);
	end_box_.resize(mensaje.size(),0);

	for(int j = 0; j < mensaje.size(); j++) {
		
		i_ = (i_+1)%256;
		f = (f+S_[i_])%256;
		std::swap(S_[i_],S_[f]); // Uso metodo swap de librería std::vector
		t = (S_[i_]+S_[f])%256;
		end_box_[j] = (S_[t]); // Vamos guardando la clave de cifrado
		mensaje_cifrado[j] = mensaje[j] ^ end_box_[j]; // Operacion Xor

	    // Creamos objetos de la bitset para pasar a binario los valores de cifrado
		std::bitset<8> bitS((S_[(S_[i_]+S_[f])%256]));
		std::bitset<8> bitM(mensaje[j]);
		std::bitset<8> bitC(mensaje_cifrado[j]);

		// Salida pedida para ver la traza de la ejecución
		std::cout<<"Byte "<<j+1<<" de secuencia cifrante: Salida = S["<<t<<"] = "<<int(S_[t])<<"\t"<< bitS<< std::endl;
		std::cout<<"Byte "<<j+1<<" de texto original: Entrada = M["<<j+1<<"] = "<<int(mensaje[j])<<"\t"<< bitM << std::endl;
		std::cout<<"Byte "<<j+1<<" de texto cifrado: Salida = C["<<j+1<<"] = "<<int(mensaje_cifrado[j])<<"\t"<< bitC << std::endl;

	}
	return mensaje_cifrado;
}

// Impirmir los vector S_, K_
void
rc4::PrintVector(std::vector<uint8_t> data) {
	std::cout<<"[";
	for (int travel = 0;travel < data.size(); travel++) {
		if(travel == data.size() - 1) std::cout << int(data[travel]);
		else                          std::cout << int(data[travel]) << ", ";
	}
	std::cout<<"]"<<"\r\n"<<std::endl;
}

// Getter para retornar la secuencia cifrada
std::vector<uint8_t> 
rc4::GetEndKey (void) {
	return end_box_;
}




















































