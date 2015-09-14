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
console.log(data2[0], " ",data2[2]);
console.log(data2[1], " ",data2[3]);

for (var i = 0; i < 9; i++) {
	data3[i] = 0.0;
}

console.log("-------------data3--------------------")
console.log(data3[0], " ",data3[2]);
console.log(data3[1], " ",data3[3]);

console.log('Res:', addon.MatMul2(2,2,data1,2,2,data2, data3));
console.log('After');

console.log("-------------data1--------------------")
console.log(data1[0], " ",data1[2]);
console.log(data1[1], " ",data1[3]);
console.log("-------------data2--------------------")
console.log(data2[0], " ",data2[2]);
console.log(data2[1], " ",data2[3]);
console.log("-------------data3--------------------")
console.log(data3[0], " ",data3[2]);
console.log(data3[1], " ",data3[3]);

console.log("\n\n-------------testing eigenvalues--------------------\n")
var eigenTest = smalloc.alloc(9, smalloc.Types.Float);
var eigenTestResult = smalloc.alloc(6, smalloc.Types.Float);
for (var i = 0; i < 9; i++) {
	eigenTest[i] = i + 1.0;
}
eigenTest[0] = 0.8;
eigenTest[1] = 0.05;
eigenTest[2] = 0.0;
eigenTest[3] = -0.05;
eigenTest[4] = 1.0;
eigenTest[5] = 0.05;
eigenTest[6] = -0.05;
eigenTest[7] = 0.0;
eigenTest[8] = 1.0;

addon.GetEigenValues(3,3,eigenTest,eigenTestResult);

for (var i = 0; i < 5 ; i+=2) {
	console.log(eigenTestResult[i] +"+i " + eigenTestResult[i+1]);
}





