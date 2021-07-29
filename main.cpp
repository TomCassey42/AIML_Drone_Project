#include "ppmTransmit.h"
#include "gpioPin.h"
#include "ppmReceiver.h"
#include <iostream>
#/*include "NvInfer.h"
#include "NvInfer.h"
#include "NvUtils.h"*/
#include <thread>

#/*include <cuda_runtime_api.h>
#include "argsParser.h"
#include "buffers.h"
#include "common.h"
#include "logger.h"
#include "NvOnnxParser.h"*/

using namespace std;

/*class Logger : public ILogger{
	void log(Severity severity, const char* msg) override{
		if(severity != Severity::kINFO)
			std::cout << msg << std::endl;
		}
} gLogger;*/

int main(int argc, char** argv){
	// Wait for system start up
	std::this_thread::sleep_for(15000ms);

	cout << "Initializing channel values...\n" << flush;
	ppmTransmit ppm(79, 6);
	ppmReceiver receiver(50, 6);
	ppm.setChannelValue(1500, 1);
	ppm.setChannelValue(1500, 2);
	ppm.setChannelValue(1000, 3);
	ppm.setChannelValue(1500, 4);
	ppm.setChannelValue(1000, 5);
	ppm.setChannelValue(1000, 6);
	ppm.setMaxError(-20);

	// Hold initial values
	std::this_thread::sleep_for(1000ms);

	cout << "Arming drone.\n" << flush;
	ppm.startTransmission();
	receiver.startReception();
	ppm.setChannelValue(2000, 5);

	// Waiting for drone to ARM
	std::this_thread::sleep_for(10000ms);

	cout << "Throttling for hover\n" << flush;
	ppm.setChannelValue(1500, 3);
	std::this_thread::sleep_for(10000ms);

	cout << "Hovering\n" << flush;
	ppm.setChannelValue(1750, 3);
	std::this_thread::sleep_for(1500ms);

	cout << "Release throttle 1\n" << flush;
	ppm.setChannelValue(1650, 3);
	std::this_thread::sleep_for(1000ms);

	cout << "Release throttle 2\n" << flush;
	ppm.setChannelValue(1600, 3);
	std::this_thread::sleep_for(4000ms);
	
	cout << "Release throttle 3\n" << flush;
	ppm.setChannelValue(1500, 3);
	std::this_thread::sleep_for(2000ms);

	cout << "Nominal value\n" << flush;
	ppm.setChannelValue(1000, 3);
	std::this_thread::sleep_for(1000ms);
	
	// Manual control
	while(true){
		cout 
			<< receiver.getChannelValue(1) << " "
			<< receiver.getChannelValue(2) << " "
			<< receiver.getChannelValue(3) << " "
			<< receiver.getChannelValue(4) << " "
			<< receiver.getChannelValue(5) << " "
			<< receiver.getChannelValue(6) << "\n";
		ppm.setChannelValue(receiver.getChannelValue(1), 1);
		ppm.setChannelValue(receiver.getChannelValue(2), 2);
		ppm.setChannelValue(receiver.getChannelValue(3), 3);
		ppm.setChannelValue(receiver.getChannelValue(4), 4);
		ppm.setChannelValue(receiver.getChannelValue(5), 5);
		ppm.setChannelValue(receiver.getChannelValue(6), 6);
	}
	/*std::this_thread::sleep_for(10000ms);
	ppm.setChannelValue(2000, 5);
	std::this_thread::sleep_for(10000ms);
	ppm.setChannelValue(1500, 3);
	std::this_thread::sleep_for(10000ms);*/
	ppm.endTransmission();
	//gpioPin pin79(79, "in");
	/*IBuilder* builder = createInferBuilder(gLogger);
const auto explicitBatch = 1U << static_cast<uint32_t>(NetworkDefinitionCreationFlag::kEXPLICIT_BATCH);  
INetworkDefinition* network = builder->createNetworkV2(explicitBatch);
nvonnxparser::IParser* parser = 
nvonnxparser::createParser(*network, gLogger);
const char* str = "/home/ikcelod/jetson-inference/python/training/detection/ssd/models/my-data3/ssd-mobilenet.onnx";
parser->parseFromFile(&*str, (int)ILogger::Severity::kWARNING);
	for (int i = 0; i < parser->getNbErrors(); ++i)
	{
		std::cout << parser->getError(i)->desc() << std::endl;
	}
IBuilderConfig* config = builder->createBuilderConfig();
config->setMaxWorkspaceSize(1 << 20);
ICudaEngine* engine = builder->buildEngineWithConfig(*network, *config);
IHostMemory *serializedModel = engine->serialize();
ofstream p("my_engine.engine");
p.write((const char*)serializedModel->data(),serializedModel->size());
p.close();*/
//std::vector<char> trtModelStream_;
//size_t size{ 0 };

/*std::ifstream file("my_engine.engine", std::ios::binary);
if (file.good())
{
file.seekg(0, file.end);
size = file.tellg();
file.seekg(0, file.beg);
trtModelStream_.resize(size);
std::cout << "size" << trtModelStream_.size() << std::endl;
file.read(trtModelStream_.data(), size);
file.close();
}*/
//std::cout << "size" << size;
/*IRuntime* runtime = createInferRuntime(gLogger);
assert(runtime != nullptr);
ICudaEngine* engine = runtime->deserializeCudaEngine(trtModelStream_.data(), size, nullptr);
IExecutionContext *context = engine->createExecutionContext();
void* buffers[3];
auto binding_size0 = 270000*sizeof(float);
auto binding_size1 = 6000*sizeof(float);
auto binding_size2 = 12000*sizeof(float);
cudaMalloc(&buffers[0], binding_size0);
cudaMalloc(&buffers[1], binding_size1);
cudaMalloc(&buffers[2], binding_size2);*/
//cout << buffers[1];
//cudaStream_t stream;
//cudaStreamCreate(&stream);
/*buffers[inputIndex] = inputBuffer;
buffers[outputIndex] = outputBuffer;*/
/*switch(engine->getBindingDataType(2)){
	case nvinfer1::DataType::kFLOAT:
		cout << "kFLOAT \n";
		break;
	case nvinfer1::DataType::kHALF:
		cout << "kHALF \n";
		break;
	case nvinfer1::DataType::kINT8:
		cout << "kINT8 \n";
		break;
	case nvinfer1::DataType::kINT32:
		cout << "kINT32 \n";
		break;
	case nvinfer1::DataType::kBOOL:
		cout << "kBOOL \n";
		break;
}*/
//std::this_thread::sleep_for(10000ms);
//void* bufferTest = malloc(6000*sizeof(float));
//float* bufferTest2 = static_cast<float*>(buffers[1]);
/*cudaMemcpy(bufferTest, buffers[1], 6000*sizeof(float), cudaMemcpyDeviceToHost);
for(int i = 0; i < 40; i++){
cout << ((float*)bufferTest)[i] << endl;
}
context->enqueueV2(buffers, stream, nullptr);
cudaMemcpy(bufferTest, buffers[1], 6000*sizeof(float), cudaMemcpyDeviceToHost);
for(int i = 0; i < 40; i++){
cout << ((float*)bufferTest)[i] << endl;*/
//}
}


