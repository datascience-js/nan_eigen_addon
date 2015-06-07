var addon = require('bindings')('addon.node')

var mat1 = new Float32Array([1.1,1.1,1.1,1.1]);
var mat2 = new Float32Array([1.0,1.0,1.0,1.0]);
var res = new Float32Array([0.0,0.0,0.0,0.0]);

console.log('Before ', mat1, mat2, res)
console.log('Res:', addon.MatMul(2,2,mat1,2,2,mat2, res))
console.log('After', mat1, mat2, res)


/*var smalloc = require('smalloc');
var data1 = smalloc.alloc(4, smalloc.Types.Float);
var data2 = smalloc.alloc(4, smalloc.Types.Float);
var data3 = smalloc.alloc(4, smalloc.Types.Float);

console.log('Before ', mat1, mat2, res)
console.log('Res:', addon.MatMul(2,2,mat1,2,2,mat2, res))
console.log('After', mat1, mat2, res) */