#include "ppmReceiver.h"
#include "gpioPin.h"

ppmReceiver::ppmReceiver(unsigned input_pin, short num_channels){	
	inputPin = new gpioPin(input_pin, "in");
	numChannels = num_channels;
	channelValues = new unsigned[num_channels+1];
}

ppmReceiver::~ppmReceiver(){

}

short ppmReceiver::getNumChannels(void){
	return numChannels;
}
void ppmReceiver::setNumChannels(unsigned num){
	numChannels = num;
}
unsigned ppmReceiver::getBlankTime(void){
	return blankTime;
}
void ppmReceiver::setBlankTime(unsigned val){
	blankTime = val;
}
unsigned ppmReceiver::getChannelValue(unsigned chan){
	return channelValues[chan];
}
unsigned ppmReceiver::setChannelValue(unsigned val, unsigned chan){
	channelValues[chan] = val;
}
unsigned* ppmReceiver::getChannelValues(void){
	return channelValues;
}
unsigned ppmReceiver::getMinChannelValue(void){
	return minChannelValue;
}
void ppmReceiver::setMinChannelValue(unsigned val){
	minChannelValue = val;
}
unsigned ppmReceiver::getMaxChannelValue(void){
	return maxChannelValue;
}
void ppmReceiver::setMaxChannelValue(unsigned val){
	maxChannelValue = val;
}
unsigned ppmReceiver::getMaxError(void){
	return maxError;
}
void ppmReceiver::setMaxError(unsigned val){
	maxError = val;
}
void ppmReceiver::startReception(void){
	receiving = true;
	receiveThread = new thread([&](){
		while (receiving){
			receive();
		}
		
	});
}
void ppmReceiver::endReception(void){
	receiving = false;
	receiveThread->join();
}
void ppmReceiver::wait(unsigned usecs){
	auto startClock = chrono::high_resolution_clock::now();
	while((chrono::high_resolution_clock::now() - startClock).count() /1000 < usecs);
}
void ppmReceiver::receive(void){
	unsigned channelVal;
	inputPin->waitForRisingEdge();
	//cout << "woot";
	microsAtPulse = chrono::high_resolution_clock::now().time_since_epoch().count()/1000;
	if(microsAtPulse - microsAtPreviousPulse > blankTime){
		pulseCounter = 0;
	} else {
		if (pulseCounter <= numChannels){
			if((microsAtPulse - microsAtPreviousPulse > minChannelValue - maxError) && 					(microsAtPulse - microsAtPreviousPulse > minChannelValue - maxError)){
				setChannelValue(microsAtPulse - microsAtPreviousPulse, pulseCounter);
			}
		}
	}
	pulseCounter++;
	microsAtPreviousPulse = microsAtPulse;
	
}

