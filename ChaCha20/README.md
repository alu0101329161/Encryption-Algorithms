# chacha20

```typescript
/* eslint-disable max-len */

export function encodeMessage(str: string): string[] | undefined {
  const alfabeto: string[] = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"];
  if (str.length % 5 !== 0) {
    return undefined;
  }

  let result = "";
  const cifrado: string[] = [];

  for (let step = 1; step <= str.length; step++) {
    if (alfabeto.indexOf(str[step - 1]) === -1) {
      return undefined;
    }

    result += alfabeto[alfabeto.length - 1 - alfabeto.indexOf(str[step - 1])];

    if (step % 5 === 0) {
      cifrado.push(result);
      result = "";
    }
  }
  return cifrado;
}

console.log(encodeMessage("abcdefghig"));

export function decodeMessage(array: string[]): string | undefined {
  const alfabeto: string[] = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"];
  if (array.length === 0) {
    return undefined;
  }

  for (let step = 0; step < array.length; step++) {
    if (array[step].length !== 5) {
      return undefined;
    }
  }

  let result: string = "";
  let variable: number = 0;

  for (let step = 0; step < array.length; step++) {
    for (let index = 0; index < array[step].length; index++) {
      variable = alfabeto.indexOf(array[step][index]);
      if (variable === -1) {
        return undefined;
      }
      result += alfabeto[alfabeto.length - 1 - variable];
    }
  }

  return result;
}

/* console.log(decodeMessage(["zyxwv", "utsrt"]));
 */

type TypeComplex = [number, number];


export function sumComplex(numberOne: TypeComplex, numberTwo: TypeComplex): TypeComplex {
  return [numberOne[0] + numberTwo[0], numberOne[1] + numberTwo[1]];
}

/* console.log(sumComplex([1, 2], [3, 4])); */


export function restComplex(numberOne: TypeComplex, numberTwo: TypeComplex): TypeComplex {
  return [numberOne[0] - numberTwo[0], numberOne[1] - numberTwo[1]];
}

/* console.log(restComplex([1, 2], [3, 4])); */

export function productComplex(numberOne: TypeComplex, numberTwo: TypeComplex): TypeComplex {
  return [numberOne[0] * numberTwo[0] - numberOne[1] * numberTwo[1], numberOne[0] * numberTwo[1] + numberOne[1] * numberTwo[0]];
}
/* console.log(productComplex([5, 2], [2, -3])); */

export function divideComplex(numberOne: TypeComplex, numberTwo: TypeComplex): TypeComplex {
  const real: number = (numberOne[0] * numberTwo[0] + numberOne[1] * numberTwo[1]) / (Math.pow(numberTwo[0], 2) + Math.pow(numberTwo[1], 2));
  const imaginaria: number = (numberOne[1] * numberTwo[0] - numberOne[0] * numberTwo[1])/(Math.pow(numberTwo[0], 2) + Math.pow(numberTwo[1], 2));

  return [real, imaginaria];
}

/* console.log(divideComplex([3, 2], [1, -2])); */

export function escalarProductComplex(numberOne: TypeComplex, numberTwo: number): TypeComplex {
  return [numberOne[0] * numberTwo, numberOne[1] * numberTwo];
}

/* console.log(escalarProductComplex([2, 3], 4)); */
```
