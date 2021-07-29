#include "ppmTransmit.h"
//#include "gpioPin.h"

ppmTransmit::ppmTransmit(unsigned output_pin, short num_channels){	
	outputPin = new gpioPin(output_pin, "out");
	numChannels = num_channels;
	channelValues = new unsigned[num_channels];
}

ppmTransmit::~ppmTransmit(){

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
	return channelValues[chan-1];
}
unsigned ppmTransmit::setChannelValue(unsigned val, unsigned chan){
	channelValues[chan-1] = val;
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
	outputPin->setValue(1);
	wait(700);
	outputPin->setValue(0);
	for (int i = 1; i <= numChannels; i++){
		channelVal = getChannelValue(i);
		if (channelVal < minChannelValue - maxError) {
			channelVal = minChannelValue - maxError;
		} else if (channelVal > maxChannelValue + maxError) {
			channelVal = maxChannelValue + maxError;
		}
		wait(channelVal - 700);
		outputPin->setValue(1);
		wait(700);
		outputPin->setValue(0);
		
	}
	wait(blankTime+100);
}

