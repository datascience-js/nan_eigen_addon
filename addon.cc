#include <nan.h>

using namespace v8;

NAN_METHOD(MatMul) {
	NanScope();

	if (args.Length() < 2) {
		NanThrowTypeError("Wrong number of arguments");
		NanReturnUndefined();
	}

	if (!args[0]->IsNumber() || !args[1]->IsFloat32Array()) {
		NanThrowTypeError("Wrong arguments");
		NanReturnUndefined();
	}
	Local<Float32Array> arr = args[1].As<Float32Array>();
	float arg0 = args[0]->NumberValue();

	Local<ArrayBuffer> buffer = arr->Buffer();
	ArrayBuffer::Contents contents = buffer->Externalize();
	float* data = static_cast<float*>(contents.Data());
	for (size_t i = 0, n = arr->Length(); i < n; i += 1) {
		data[i] = data[i] + arg0;
	}

	Local<Float32Array> num = NanNew(arr);

	NanReturnValue(num);
}

void Init(Handle<Object> exports) {
	exports->Set(NanNew("MatMul"), NanNew<FunctionTemplate>(MatMul)->GetFunction());
}

NODE_MODULE(addon, Init)
