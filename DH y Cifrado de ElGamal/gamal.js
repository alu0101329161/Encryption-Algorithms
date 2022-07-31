/**
 * Funcion de Euclides extendida para el calculo
 * del inverso
 * @param {*} a diviendo
 * @param {*} b divisor
 * @returns 
 */
const ExtendedEuclidean = function(a, b) {
    const x = [undefined, a, b];
    const z = [0, 1];
  
    let i = 2;
    let remainder = x[i-1] % x[i];
  // el resto no de 0
    while (remainder !== 0) {
      x.push(remainder);
      
      let temp = ((- x[i-1] / x[i]) | 0) * z[i-1] + z[i-2];
      
      // Se maneja el caso de que sea negativo
      while (temp < 0) {
        temp += a;
      }
      
      z.push(temp % a);
  
      i++;
      remainder = x[i-1] % x[i];
    }
  
    return {
      get mcd() {
        return this.x[this.x.length-1];
      },
      get inverse() {
        if (this.mcd === 1) return this.z[this.z.length-1];
        return null;
      }, 
  
      x: [...x],
      z: [...z],
    }
  };


/**
 * Calcula la inversa de un número b módulo un número a, tal que a > b, 
 * empleando el algorimto de Euclides extendido
 * @param {*} b 
 */
const InverseOf = function(b) {
    this.module = function(a) {
      return ExtendedEuclidean(a, b).inverse;    
    }
  }
  
  // console.log(new InverseOf(12).module(19));
  
  /**
   * Exponenciación rápida
   * @param {number} a Base
   * @param {number} b Exponente
   * @param {number} m Módulo
   */
const FastModularExponentiation = function(a, b, m) {
    let x = 1;
    let y = a % m;
  
    while (b > 0 && y > 1) {
      if (b % 2 !== 0) {
        x = (x * y) % m;
        b--;
      } else {
        y = (y * y) % m;
        b = b / 2;
      }
    }
    return x
  }
  // console.log(new FastModularExponentiation(2, 100, 29));
  // console.log(FastModularExponentiation(2, 28, 79)); //--> 13



const ElGamal = function() {
    // Objeto para logger la información y mostrarla en la página
      this.log = [];
      
      // User A: msg, random secretK, K = (a^x)^k (mod p)
      // User B: random secretX, K = (a^k)^x (mod p)
      // Encrypted msg = Km (mod p)
      // Decrypted msg = K^-1(Km) (mod p)
    
      /**
       * 
       * @param {number} primeP Número primo PY
       * @param {number} intA Número entero a
       * @param {number} secretK Número aleatorio privado de A
       * @param {number} secretX Número aleatorio privado de B
       * @param {number} msg Mensaje a cifrar
       * @returns 
       */
      this.run = function(primeP, intA, secretK, secretX, msg) {
        // Valores que conoce el sujeto (receptor) B
        const userB = {
          id: 'Bob',
          privateX: secretX, // Valor privado de B
          publicToSend: FastModularExponentiation(intA, secretX, primeP), // Valor público de B
        }
        console.log("Calculamos el valor publico de Bob: " + userB.publicToSend)
        // Vallores que conoce el usuario A (emisor)
        const userA = {
          id: 'Alice',
          privateK: secretK, // Valor privado de A
          publicToSend: FastModularExponentiation(intA, secretK, primeP), // Valor público de A
          
          sharedKey: FastModularExponentiation(userB.publicToSend, secretK, primeP), // Clave compartida con B
          msg: msg, // Mensaje a cifrar
        }
        console.log("Calculamos el valor publico de Alice y su clave compartida con el valor de BOB: " + userA.publicToSend + " "+ userA.sharedKey)
        userA.encryptedMsg = (userA.sharedKey * userA.msg) % primeP; // Mensaje encriptado
        console.log("Alice encripta el mensaje: " + userA.encryptedMsg)
    
        userB.sharedKey = FastModularExponentiation(userA.publicToSend, secretX, primeP); // Clave compartida con A
        console.log("Calculamos la clave compartida de bob: " + userB.sharedKey)

        // Descifrado del mensaje
        let sharedKeyInverse = new InverseOf(userB.sharedKey).module(+primeP);
        if (sharedKeyInverse) {
          userB.decryptedMsg = sharedKeyInverse * userA.encryptedMsg % primeP;
          userB.decryptedMsg = userB.decryptedMsg < 0 ? primeP + userB.decryptedMsg : userB.decryptedMsg;
          userB.sharedKeyInverse = sharedKeyInverse;
        } else {
          console.log('No inverse');
        }
        console.log("Bob halla la inversa y desencripta el mensaje: " + userB.sharedKeyInverse +", "+ userB.decryptedMsg)

        console.log(userB);
        console.log(userA);
      };
    };

elgamal = new ElGamal()
var readlineSync = require('readline-sync');
let primeP = readlineSync.question(" Numero primo PY: ")
let intA = readlineSync.question("Numero entero a: ")
let secretK = readlineSync.question("Numero aleatorio privado de A: ")
let secretX = readlineSync.question(" Numero aleatorio privado de B: ")
let msg = readlineSync.question("Mensaje a cifrar: ")

elgamal.run(+primeP, +intA, +secretK, +secretX, +msg);