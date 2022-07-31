__Objetivo__: 

Implementar el algoritmo Rijndael


__Desarrollo__:


1. Implementa el cifrado en bloque para bloques y claves de 128 bits (que se representan como matrices de estado
de 4x4 bytes):
• Expansión de la clave obteniendo 10 subclaves a partir de la clave original usando la constante de iteración
• Etapa inicial: AddRoundKey entre el bloque de entrada y la clave original
• 9 Iteraciones de:
1. SubBytes — usando la S-Caja
2. ShiftRow
3. MixColumn — multiplicando una matriz por los cuatro bytes de cada columna, operando con bytes.
4. AddRoundKey — con la subclave correspondiente a la iteración
• Etapa final:
1. SubBytes
2. ShiftRows
3. AddRoundKey — con la última subclave


![image](https://user-images.githubusercontent.com/72351056/182037461-d880f0e8-8893-4c0e-bdfb-4f00bc799ba7.png)
