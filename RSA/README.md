__Objetivo__: 

> Implementar el cifrado de clave pública RSA.


__Desarrollo__:
1. Implementa el cifrado RSA de forma que:
• El programa debe solicitar el texto del mensaje a cifrar, los parámetros p, q y d, comprobar
que p y q son números primos (con el test de Lehman-Peralta) y que d es primo con φ(n)
(con el algoritmo de Euclides extendido).
• El programa debe mostrar la traza completa del algoritmo, es decir, el parámetro e
obtenido con el algoritmo de Euclides extendido, y los números correspondientes al
mensaje cifrado, obtenidos utilizando el algoritmo de exponenciación rápida.
Nota: Para la codificación numérica del texto considerar alfabeto sin Ñ en base 26 (A…Z:
0…25), y dividir en bloques de tamaño j-1 según el valor de n, de forma que 26j-1<n<26j
. Así,
por ejemplo, si j-1=4, ABCD equivale a 0*26^3+1*26^2+2*26+3=731. Si el último bloque
resultante para cifrar no es de tamaño j-1, se añade una letra nula, la X por ejemplo.



![image](https://user-images.githubusercontent.com/72351056/182037643-c464e4c8-69ad-4f18-bf47-ecbe7f4109ea.png)

