#include <nan.h>
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues> 
#include <complex>
using namespace v8;


NAN_METHOD(MatMul) {
	NanScope();
	using CMf = Eigen::Map <const Eigen::MatrixXf >;
	using Mf = Eigen::Map <Eigen::MatrixXf >;
	//Map<MatrixXf> mf(pf, rows, columns);

	if (args.Length() < 7) {
		NanThrowTypeError("Wrong number of arguments");
		NanReturnUndefined();
	}

	if (!args[0]->IsUint32() || !args[1]->IsUint32() || !args[2]->IsFloat32Array() ||
		!args[3]->IsUint32() || !args[4]->IsUint32() || !args[5]->IsFloat32Array() ||
		!args[6]->IsFloat32Array()) {
		NanThrowTypeError("Wrong arguments");
		NanReturnUndefined();
	}
	size_t rows1(args[0]->Uint32Value());
	size_t cols1(args[1]->Uint32Value());
	Local<Float32Array> arr1 = args[2].As<Float32Array>();
	Local<ArrayBuffer> buffer1 = arr1->Buffer();
	ArrayBuffer::Contents contents1 = buffer1->Externalize();
	float* data1 = static_cast<float*>(contents1.Data());
	std::cout << "After cast." << std::endl;
	CMf first(data1, rows1, cols1);

	size_t rows2(args[3]->Uint32Value());
	size_t cols2(args[4]->Uint32Value());
	Local<Float32Array> arr2 = args[5].As<Float32Array>();
	Local<ArrayBuffer> buffer2 = arr2->Buffer();
	ArrayBuffer::Contents contents2 = buffer2->Externalize();
	float* data2 = static_cast<float*>(contents2.Data());
	CMf second(data2, rows2, cols2);

	Local<Float32Array> resFArray = args[6].As<Float32Array>();
	Local<ArrayBuffer> resBuff = resFArray->Buffer();
	ArrayBuffer::Contents resContents = resBuff->Externalize();
	float* resRawData = static_cast<float*>(resContents.Data());
	
	Mf res(resRawData, rows1, cols2);
	res = second * first;
	//ArrayBuffer::Contents c
	Local<Float32Array> num = NanNew(resFArray);
	std::cout << "Before return." << std::endl;
	NanReturnValue(num);
}

NAN_METHOD(MatMul2){
	NanScope();
	using CMf = Eigen::Map <const Eigen::MatrixXf >;
	using Mf = Eigen::Map <Eigen::MatrixXf >;
	//Map<MatrixXf> mf(pf, rows, columns);

	if (args.Length() < 7) {
		NanThrowTypeError("Wrong number of arguments");
		NanReturnUndefined();
	}

	if (!args[0]->IsUint32() || !args[1]->IsUint32() ||/* !args[2]->IsFloat32Array() ||*/
		!args[3]->IsUint32() || !args[4]->IsUint32()   /*||  !args[5]->IsFloat32Array() ||
													   !args[6]->IsFloat32Array()*/) {
		NanThrowTypeError("Wrong arguments");
		NanReturnUndefined();
	}
	size_t rows1(args[0]->Uint32Value());
	size_t cols1(args[1]->Uint32Value());
	
	
	Local<Object> matrix1Buff = args[2].As<Object>();
	float *data1 = nullptr;
	size_t length1 = 0;

	if (matrix1Buff->HasIndexedPropertiesInExternalArrayData()) {
		length1 = size_t(matrix1Buff->GetIndexedPropertiesExternalArrayDataLength());
		data1 = static_cast<float*>(matrix1Buff->GetIndexedPropertiesExternalArrayData());
	}
	CMf first(data1, rows1, cols1);

	size_t rows2(args[3]->Uint32Value());
	size_t cols2(args[4]->Uint32Value());

	Local<Object> matrix2Buff = args[5].As<Object>();
	float *data2 = nullptr;
	size_t length2 = 0;

	if (matrix2Buff->HasIndexedPropertiesInExternalArrayData()) {
		length2 = size_t(matrix2Buff->GetIndexedPropertiesExternalArrayDataLength());
		data2 = static_cast<float*>(matrix2Buff->GetIndexedPropertiesExternalArrayData());
	}

	CMf second(data2, rows2, cols2);
	
	Local<Object> matrixResBuff = args[6].As<Object>();
	float *resRawData = nullptr;
	size_t lengthRes = 0;

	if (matrixResBuff->HasIndexedPropertiesInExternalArrayData()) {
		lengthRes = size_t(matrixResBuff->GetIndexedPropertiesExternalArrayDataLength());
		resRawData = static_cast<float*>(matrixResBuff->GetIndexedPropertiesExternalArrayData());
	}
	
	Mf res(resRawData, rows1, cols2);
	res = second * first;
	Local<Boolean> b = NanNew(true);
	NanReturnValue(b);
}


NAN_METHOD(GetEigenValues){
	using CMf = Eigen::Map <const Eigen::MatrixXf >;
	using Mf = Eigen::Map <Eigen::MatrixXf >;
	using EMf = Eigen::Map <Eigen::EigenSolver<const Eigen::MatrixXf>::EigenvalueType>;

	if (args.Length() != 4) {
		NanThrowTypeError("Wrong number of arguments");
		NanReturnUndefined();
	}

	if (!args[0]->IsUint32() || !args[1]->IsUint32()) {
		NanThrowTypeError("Wrong arguments");
		NanReturnUndefined();
	}
	size_t rows1(args[0]->Uint32Value());
	size_t cols1(args[1]->Uint32Value());

	Local<Object> matrix1Buff = args[2].As<Object>();
	float *data1 = nullptr;
	size_t length1 = 0;

	if (matrix1Buff->HasIndexedPropertiesInExternalArrayData()) {
		length1 = size_t(matrix1Buff->GetIndexedPropertiesExternalArrayDataLength());
		data1 = static_cast<float*>(matrix1Buff->GetIndexedPropertiesExternalArrayData());
	}
	CMf first(data1, rows1, cols1);

	Local<Object> matrixResBuff = args[3].As<Object>();
	float *resRawData = nullptr;
	size_t lengthRes = 0;

	if (matrixResBuff->HasIndexedPropertiesInExternalArrayData()) {
		lengthRes = size_t(matrixResBuff->GetIndexedPropertiesExternalArrayDataLength());
		resRawData = static_cast<float*>(matrixResBuff->GetIndexedPropertiesExternalArrayData());
	}
	EMf eigenResults(reinterpret_cast<std::complex<float>*>(resRawData)/*very ugly but well defined afaik */, rows1, 1);
	Eigen::EigenSolver<Eigen::MatrixXf> eigenSolver(first, false);

	eigenResults = eigenSolver.eigenvalues();
	Local<Boolean> b = NanNew(true);
	NanReturnValue(b);
}


void Init(Handle<Object> exports) {
	exports->Set(NanNew("MatMul"), NanNew<FunctionTemplate>(MatMul)->GetFunction());
	exports->Set(NanNew("MatMul2"), NanNew<FunctionTemplate>(MatMul2)->GetFunction());
	exports->Set(NanNew("GetEigenValues"), NanNew<FunctionTemplate>(GetEigenValues)->GetFunction());
}

NODE_MODULE(addon, Init)
