
/* Autor:: Joseph Gabino Rodríguez 
*  Ejecucion: node GenerationCA.js
* Requerimentos node npm install
*/


// Creamos el objeto que realizamos las operaciones
const CA_Generator = function () {
  // Array de pares con los satelites
  this.satelites = [[2, 6], [3, 7], [4, 8], [5, 9], [1, 9], [2, 10],
  [1, 8], [2, 9], [3, 10], [2, 3], [3, 4], [5, 6], [6, 7], [7, 8],
  [8, 9], [9, 10], [1, 4], [2, 5], [3, 6], [4, 7], [5, 8], [6, 9],
  [1, 3], [4, 6], [5, 7], [6, 8], [7, 9], [8, 10], [1, 6], [2, 7],
  [3, 8], [4, 9]].map((elements) => [elements[0] - 1, elements[1] - 1]);

  // Polinomios que vamos a implementar
  this.polinomio1 = [2, 9]; // 1 + x^3 + x^10
  this.polinomio2 = [1, 2, 5, 7, 8, 9]; // 1 + x^2 + x^3 + x^6 + x^8 + x^9 + x^10

  // Realizamos la operacion recibiendo el id del satelite
  // y la longitud de la secuencia resultante
  this.generate = (IDsatelite, Longitud) => {
    this.log = [];
    // En la primera iteracion rellenamos con unos y suponemos un array de
    // longitud 10
    let lfsr1 = new Array(10).fill(1);
    let lfsr2 = new Array(10).fill(1);

    // Vamos guardando el array de la secuencia
    // C/A PRN1
    let CA_Code = [];
    const prn1 = this.satelites[IDsatelite - 1];

    for (let i = 0; i < Longitud; i++) { // Hacemos tantas operaciones como la indicada por teclado
      // Vamos guardando todos los estados posibles
      let objeto = {
        lfsr1: {
          estados: [...lfsr1], // Vamos guardando los diferentes estados del array
          realimentacion: undefined    // Guardamos la realimentacion es decir el bit que sale
        },
        lfsr2: {
          estados: [...lfsr2], // Repetimos el proceso con el segundo array
          realimentacion: undefined
        },
        caSeq: undefined
      };

      // Solucion final que vamos guardando en CA_Code
      const caSeq = lfsr1[9] ^ lfsr2[9];  // [9]
      CA_Code.push(caSeq)

      // Realizamos el desplazamiento en ambos arrays
      lfsr1.rotateNrealimentacion(this.polinomio1);
      lfsr2.rotateNrealimentacion(this.polinomio2);

      // Guardamos los estados en el objeto
      objeto.lfsr1.realimentacion = lfsr1[0];
      objeto.lfsr2.realimentacion = lfsr2[0];
      objeto.caSeq = caSeq;
      this.log.push(objeto);
    }
    return CA_Code;
  }
  // COgemos las posiciones 9 del primer lsdfr y el
  // resultado del satelite en el lsfr2
  Array.prototype.getElementsByIndex = function (item) {
    let elements = [];
    item.forEach(index => {
      elements.push(this[index]);
    });
    return elements;
  }

  // Hacemos un xor entre las posiciones
  Array.prototype.xorElementsByIndex = function (item) {
    return this.getElementsByIndex(item).reduce((xor, cur) => xor ^ cur);
  }

  Array.prototype.rotateNrealimentacion = function (item) {
    // Quitamos el ultimo elemento hago el XOR
    this.unshift(this.xorElementsByIndex(item));
    // Introduzco por delante
    this.pop();
  }
  // Generación aleatoria
  this.random = (min, max) => {
    return Math.floor((Math.random() * (max - min + 1)) + min);
  }

/*     this.ej = function (its) {
    const poly = [3, 5, 7, 10].map((p) => p - 1);
    const lfsr = [1, 0, 0, 1, 0, 1, 0, 0, 0, 1];

    for (let i = 0; i < its; i++) {
      console.log('LFSR: ', lfsr, '  Salida: ', lfsr[9]);
      lfsr.rotateNrealimentacion(poly);
    }
  } 
  this.log = [];
  this.foo = function(seed, polynom) {
    const lfsr = [...seed];
    let result = [];
    for (let i = 0; i < 10; i++) {
      result.push(lfsr[4]);
      result.rotateNrealimentacion(polynom);
    }
    return [lfsr, result];
  };  */
};
  // Imprimimos por consola la información
  console.log("Secuencia C/A PRN1")
  let value = "";
  const caGen = new CA_Generator();
  var readlineSync = require('readline-sync');
  let idsatelite = readlineSync.question("Introduzca el ID de satelite que quiere emplear: ")
  let longitud = readlineSync.question("Introduzca la longitud de la secuencia de salida: ")
  console.log(caGen.generate(idsatelite, longitud))

  // Recorremos el objeto objeto y para cada posicion retornamos el estado
  // la realimentacion y por útimo la secuencia C/A
  caGen.log.forEach( objeto => {
    value += '|'+objeto.lfsr1.estados.toString() + '   ';
    value += objeto.lfsr1.realimentacion + '             ';
    value += objeto.lfsr2.estados.toString() + '   ';
    value += objeto.lfsr2.realimentacion + '             ';
    value += objeto.caSeq + '|' + '\n';
  });
    console.log("LSFR1               REALIMENTACION  LSFR2               REALIMENTACION SECUENCIA")
    console.log(value)

// console.log(caGen.foo([1,0,0,0,0], [0, 3, 4]));
// console.table(caGen);
// console.log(caGen.ej(14));