__Objetivo__: 

> Implementar la multiplicación binaria usada tanto en SNOW 3G como en AES.


__Desarrollo__:


> En SNOW 3G las dos multiplicaciones de 32 bits por 32 bits implicadas en el LFSR se corresponden con
productos de polinomios en módulo x8+x7+x5+x3+1, que pueden ser implementadas como una sucesión de
desplazamientos de bytes y XORs con el byte A916=101010012.


> En AES la multiplicación de bytes utilizada se corresponde con el producto de polinomios en módulo
x8+x4+x3+x+1, que puede ser implementado como una sucesión de desplazamientos de bytes y XORs con el
byte 1B16=000110112.

> En ambos casos, implica aplicar operación distributiva sobre los dos bytes multiplicandos, usando para ello
el byte de menor peso, y luego para cada bit 1 de ese byte, desplazar a izquierda el otro byte, de forma que
cada vez que su bit más significativo antes del desplazamiento sea 1, hay que hacer, tras el desplazamiento,
una XOR bit a bit con el byte A9 o 1B. 


![image](https://user-images.githubusercontent.com/72351056/182037400-ad4c963c-d93b-4fa9-b49b-32bfd51af717.png)
