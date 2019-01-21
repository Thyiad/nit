var addon = require("../build/Release/nit-addon");

const obj = {
  hands: ['AsAc', 'KsKc'],
  board: '2d2s2c'
}

console.log(addon.calculateOdds(obj))
