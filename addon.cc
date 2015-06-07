#include <nan.h>
#include <iostream>
#include <Eigen/Dense>
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

	if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsFloat32Array() ||
		!args[3]->IsNumber() || !args[4]->IsNumber() || !args[5]->IsFloat32Array() ||
		!args[6]->IsFloat32Array()) {
		NanThrowTypeError("Wrong arguments");
		NanReturnUndefined();
	}
	size_t rows1= size_t(args[0]->NumberValue());
	size_t cols1 = size_t(args[1]->NumberValue());
	Local<Float32Array> arr1 = args[2].As<Float32Array>();
	Local<ArrayBuffer> buffer1 = arr1->Buffer();
	ArrayBuffer::Contents contents1 = buffer1->Externalize();
	std::cout << "alalal" << std::endl;
	float* data1 = static_cast<float*>(contents1.Data());
	std::cout << "After cast." << std::endl;
	CMf first(data1, rows1, cols1);

	size_t rows2 = size_t(args[3]->NumberValue());
	size_t cols2 = size_t(args[4]->NumberValue());
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

void Init(Handle<Object> exports) {
	exports->Set(NanNew("MatMul"), NanNew<FunctionTemplate>(MatMul)->GetFunction());
}

NODE_MODULE(addon, Init)
