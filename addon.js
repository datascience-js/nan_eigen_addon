var addon = require('bindings')('addon.node')

var mat1 = new Float32Array([1.1,1.1,1.1,1.1]);
var mat2 = new Float32Array([1.0,1.0,1.0,1.0]);
var res = new Float32Array([0.0,0.0,0.0,0.0]);

console.log('Before ', mat1, mat2, res)
console.log('Res:', addon.MatMul(2,2,mat1,2,2,mat2, res))
console.log('After', mat1, mat2, res)

console.log('---------------------Before smalloc--------------------------')
var smalloc = require('smalloc');
var data1 = smalloc.alloc(4, smalloc.Types.Float);
var data2 = smalloc.alloc(4, smalloc.Types.Float);
var data3 = smalloc.alloc(4, smalloc.Types.Float);

data1[0] = 1.0;
data1[1] = 1.0;
data1[2] = 1.0;
data1[3] = 1.0;

console.log("-------------data1--------------------")
console.log(data1[0], " ",data1[1]);
console.log(data1[2], " ",data1[3]);

data2[0] = 1.0;
data2[1] = 1.0;
data2[2] = 1.0;
data2[3] = 1.0;

console.log("-------------data2--------------------")
console.log(data2[0], " ",data2[1]);
console.log(data2[2], " ",data2[3]);

data3[0] = 0.0;
data3[1] = 0.0;
data3[2] = 0.0;
data3[3] = 0.0;

console.log("-------------data3--------------------")
console.log(data3[0], " ",data3[1]);
console.log(data3[2], " ",data3[3]);

//console.log('Before ', mat1, mat2, res);
console.log('Res:', addon.MatMul2(2,2,data1,2,2,data2, data3));
console.log('After');

console.log("-------------data1--------------------")
console.log(data1[0], " ",data1[1]);
console.log(data1[2], " ",data1[3]);
console.log("-------------data2--------------------")
console.log(data2[0], " ",data2[1]);
console.log(data2[2], " ",data2[3]);
console.log("-------------data3--------------------")
console.log(data3[0], " ",data3[1]);
console.log(data3[2], " ",data3[3]);
