#include "ppmTransmit.h"

ppmTransmit::ppmTransmit(unsigned output_pin, short num_channels){	
	outputPin = output_pin;
	numChannels = num_channels;
	channelValues = new unsigned[num_channels];

	ofstream fileOutput;
	
	gpioExport = string(GPIO_DIR) + string("export");
	gpioPinDirection = string(GPIO_DIR) + string("gpio") + 
		std::to_string(output_pin) + string("/direction");
	gpioPinValue = string(GPIO_DIR) + string("gpio") + 
		std::to_string(output_pin) + string("/value");
	gpioUnexport = string(GPIO_DIR) + string("unexport");

	fileOutput.open(gpioExport);
	fileOutput << output_pin;
	fileOutput.close();
	
	fileOutput.open(gpioPinDirection);
	fileOutput << "out";
	fileOutput.close();

	fileOutput.open(gpioPinValue);
	fileOutput << 0;
	fileOutput.close();

}

ppmTransmit::~ppmTransmit(){
	fileOutput.open(gpioPinValue);
	fileOutput << 0;
	fileOutput.close();
	fileOutput.open(gpioUnexport);
	fileOutput << outputPin;
	fileOutput.close();
}

short ppmTransmit::getNumChannels(void){
	return numChannels;
}
void ppmTransmit::setNumChannels(unsigned num){
	numChannels = num;
}
unsigned ppmTransmit::getBlankTime(void){
	return blankTime;
}
void ppmTransmit::setBlankTime(unsigned val){
	blankTime = val;
}
unsigned ppmTransmit::getChannelValue(unsigned chan){
	return channelValues[chan];
}
unsigned ppmTransmit::setChannelValue(unsigned val, unsigned chan){
	channelValues[chan] = val;
}
unsigned* ppmTransmit::getChannelValues(void){
	return channelValues;
}
unsigned ppmTransmit::getMinChannelValue(void){
	return minChannelValue;
}
void ppmTransmit::setMinChannelValue(unsigned val){
	minChannelValue = val;
}
unsigned ppmTransmit::getMaxChannelValue(void){
	return maxChannelValue;
}
void ppmTransmit::setMaxChannelValue(unsigned val){
	maxChannelValue = val;
}
unsigned ppmTransmit::getMaxError(void){
	return maxError;
}
void ppmTransmit::setMaxError(unsigned val){
	maxError = val;
}
void ppmTransmit::startTransmission(void){
	transmitting = true;
	transmitThread = new thread([&](){
		while (transmitting){
			transmit();
		}
		
	});
}
void ppmTransmit::endTransmission(void){
	transmitting = false;
	transmitThread->join();
}
void ppmTransmit::wait(unsigned usecs){
	auto startClock = chrono::high_resolution_clock::now();
	while((chrono::high_resolution_clock::now() - startClock).count() /1000 < usecs);
}
void ppmTransmit::transmit(void){
	unsigned channelVal;
	fileOutput.open(gpioPinValue);
	fileOutput << 1;
	fileOutput.flush();
	wait(400);
	fileOutput << 0;
	fileOutput.flush();
	for (int i = 0; i < numChannels; i++){
		channelVal = getChannelValue(i);
		if (channelVal < minChannelValue - maxError) {
			channelVal = minChannelValue - maxError;
		} else if (channelVal > maxChannelValue + maxError) {
			channelVal = maxChannelValue + maxError;
		}
		wait(channelVal - 400);
		fileOutput << 1;
		fileOutput.flush();
		cout << i << "  " << channelVal << "\n";
		wait(400);
		fileOutput << 0;
		fileOutput.flush();
		
	}
	fileOutput.close();
	wait(blankTime+100);
}

