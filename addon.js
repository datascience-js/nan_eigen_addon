var addon = require('bindings')('addon.node')
var arr = new Float32Array([1.1,3.1]);

console.log('Before ', arr)
console.log('This should be eight:', addon.add(777.777, arr))
console.log('After', arr)