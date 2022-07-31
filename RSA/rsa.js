
/**
 * Calcula la inversa de un número b módulo un número a, tal que a > b, 
 * empleando el algorimto de Euclides extendido
 * @param {*} b 
 */
 const InverseOf = function(b) {
    this.module = function(a) {
      return extendedEuclidean(a, b).inverse;    
    };
  };

/**
 * Exponenciación rápidaa
 * @param {number} a Base
 * @param {number} b Exponente
 * @param {number} m Módulo
 */
const fastModularExponentiation = function(a, b, m) {
    let x = 1;
    let y = a % m;
  
    while (b > 0) {
      if (b % 2 == 0) {
        y = (y * y) % m;
        b = b / 2;
      } else {
        x = (x * y) % m;
        b--;
      }
    }
    return x;
  };

/**
 * Devuelve un entero pseudoaleatorio entre dos límites
 * @param {number} min límite inferior
 * @param {number} max límite superior
 * @returns 
 */
 function getRandomInt(min, max) {
    return Math.floor(Math.random() * (max - min)) + min; // You can remove the Math.floor if you don't want it to be an integer
  }

/**
 * Realiza el test de miller entrendiendo si un número es primo
 * @param {*} p primo
 * @param {*} k numero de veces q se comprueba si es primo
 * @returns 
 */
const testMillerRabin = function(p, k = 100) {
    let s = 0;
    let d = p - 1;
    while (d % 2 === 0) {
        d /= 2;
        s++;
    }
    for (let i = 0; i < k; i++) {
        let a = Math.floor(Math.random() * (p - 2)) + 1;
        let x = fastModularExponentiation(a, d, p);
        if (x === 1 || x === p - 1) continue;
        for (let j = 0; j < s - 1; j++) {
            x = fastModularExponentiation(x, 2, p);
            if (x === 1) return false;
            if (x === p - 1) break;
        }
        if (x !== p - 1) return false;
    }
    return true;
};

console.log(testMillerRabin(17, 1000));

/**
 * Testea si un número es primo
 * @param {*} p numero a comprobar 
 * @param {*} k numero de veces que se comprueba si es primo
 * @returns 
 */
const testLehmanPeralta = function(p, k = 100) {
    let count = 0
    if (p % 2 == 0 || p % 3 == 0 || p % 5 == 0 || p % 7 == 0 ||
      p % 11 == 0) return false;
    for(let i = 0; i < k; i++) {
        let a = Math.floor(Math.random() * (p - 2)) + 1;
        let x = fastModularExponentiation(a, (p - 1)/2, p);
        if(x == 1) count ++;
        else if(x == -1) return false;
    }
    if(count == k) return false;
    return true;
  };

console.log(testLehmanPeralta(17, 1000));

/**
 * Calcula el inverso de un número a módulo b
 * @param {*} a dividendo 
 * @param {*} b divisor
 * @returns 
 */
const extendedEuclidean = function(a, b) {
  const x = [undefined, a, b];
  const z = [0, 1];

  let i = 2;
  let remainder = x[i-1] % x[i];

  while (remainder !== 0) {
    x.push(remainder);
    
    let temp = ((- x[i-1] / x[i]) | 0) * z[i-1] + z[i-2];
    
    // Se maneja el caso de que el resultado seanegativo
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
  };
};



/**
 * Cifrar mediante RSA
 * @param {*} base 
 * @param {*} alph 
 */
const RSA = function() {
  // Base en la que está el mensaje definida por enunciado
  this.base = 26;

  // Alfabeto de entrada
  this.alph = {'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4, 'F': 5, 'G': 6, 'H': 7, 'I': 8, 'J': 9, 'K': 10, 'L': 11, 'M': 12,
    'N': 13, 'O': 14, 'P': 15, 'Q': 16, 'R': 17, 'S': 18, 'T': 19, 'U': 20, 'V': 21, 'W': 22, 'X': 23, 'Y': 24, 'Z': 25,};

  /**
   * Calcula el tamaño de los bloques
   * @param {number} base base en la que se quiere codificar el mensaje
   * @param {number} n módulo
   */
  this.getBlockSize = function(base, n) {
    return (Math.log(n) / Math.log(base)) | 0;
  };

  /**
   * Devuelve el bloque codificado
   * @param {string} block 
   * @returns {number} Bloque codificado
   */
  this.encodeBlock = function(block) { // REVISADO

    const alphLength = Object.values(this.alph).length;
    const codifiedChars = block.split('').map((c, i) => {
      const temp1 = this.alph[c];
      const temp2 = Math.pow(alphLength, block.length - 1 - i); // 26^j-1
      const codifiedChar = temp1 * temp2; // Multiplicamos los valores
      return codifiedChar;
    });

    return codifiedChars.reduce((total, cur) => total + cur); // Sumatorio de los valores
  };

  /**
  * Devuelve el bloque decodificado
  * @param {number} block 
  * @returns {string} bloque decodificado
  */
  this.decodeBlock = function(block) {
    const alphKeys = Object.keys(this.alph);
    return block.toString(26).split('').map((c) => alphKeys[parseInt(c, alphKeys.length)]).join('');
  };


  /**
   * Divide el mensaje en bloques de tamaño blockSize
   * @param {string} msg 
   * @param {number} blockSize 
   * @returns {string[]} Array con el mensaje separado en bloques
   */
  this.splitMessage = function(msg, blockSize) {
    const splittedMessage = [];
    const msgChars = msg.toUpperCase().split('').filter((c) => Object.keys(this.alph).includes(c));
    const numOfChars = msgChars.length;

    for (let i = 0; i < numOfChars / blockSize; i++) {
      splittedMessage.push(msgChars.splice(0, blockSize).join(''));
    }

    return splittedMessage;
  };

  /**
   * Cifra un bloque codificado en decimal
   * @param {number} block Bloque a cifrar (en decimal)
   * @param {number} e 
   * @param {number} n 
   * @returns 
   */
  this.cipherBlock = function(block, e, n) {
    return fastModularExponentiation(block, e, n);
  };


  /**
   * Descifra un bloque (en decimal)
   * @param {number} block 
   * @param {number} d Entero primo con fi(n)
   * @param {number} n Módulo
   * @returns 
   */
  this.decipherBlock = function(block, d, n) {
    return fastModularExponentiation(block, d, n);
  };

  /**
   * Cifra un mensaje
   * @param {string} clearText Texto en claro
   * @param {number} p Número primo
   * @param {number} q Número primo
   * @param {number} d Entero primo con fi(n)
   * @returns 
   */
  this.cipher = function(clearText, p, q, d) {
    // Verificar que p y q son números primos con el test de primalidad de Lehman y Peralta
    if (!testMillerRabin(p)) {
      console.log(`Error: ${p} no es primo`);
      return;
    }

    if (!testMillerRabin(q)) {
      console.log(`Error: ${q} no es primo`);
      return;
    }

    const n = p * q; // Calculamos n
    const fiN = (p - 1) * (q - 1); // calculamos fi
    const e = new InverseOf(d).module(fiN); // calculamos e
  

    const blockSize = this.getBlockSize(this.base, n); // Sacamos los tamaños de los bloques

    // dividimos los bloques en base al tamaño anterior
    const splittedBlocks = this.splitMessage(clearText, blockSize).map((block) => block);
    // codificamos los bloques
    const encodedBlocks = splittedBlocks.map((block) => this.encodeBlock(block));
    console.log(encodedBlocks)
    const cipheredBlocks = encodedBlocks.map((block) => this.cipherBlock(block, e, n));
    console.log(cipheredBlocks)
    const decipheredMsg = cipheredBlocks.map((block) => this.decipherBlock(block, d, n));

    const decodedMsg = decipheredMsg.map((block) => this.decodeBlock(block)).join('');

    console.log(`Se comprueba que p y q son primos \n` +
        `Se comprueba que d es primo con fi(n) = ${fiN}\n` +
        `Se calcula e = ${e}\n` +
        `Como n = ${n}, se divide el texto en bloques de ${blockSize} caracteres\n` +
        `Se pasa cada bloque a decimal para poder cifrar, obteniendo ${encodedBlocks.join(', ')}\n` +
        `Se calcula en decimal el texto cifrado : ${cipheredBlocks}\n`);

  };
};


console.clear();
const rsa = new RSA();
rsa.cipher("MANDADINEROS", 421, 7, 1619);
console.log("------------------------")
const rsa2 = new RSA();
rsa2.cipher("AMIGO MIO", 2347, 347, 5);

/**
 * console.log(`Se comprueba que p y q son primos \n` +
`Se comprueba que d es primo con fi(n) = ${fiN}\n` +
`Se calcula e = ${e}\n` +
`Como n = ${n}, se divide el texto en bloques de ${blockSize} caracteres\n` +
`Se pasa cada bloque a decimal para poder cifrar, obteniendo ${encodedBlocks.join(', ')}\n` +
`Se calcula en decimal el texto cifrado : ${cipheredBlocks}\n` +
`Descifrado: ${decipheredMsg}\n` +
`Completo: ${decodedMsg}`);
 */
