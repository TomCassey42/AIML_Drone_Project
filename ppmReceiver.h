#include <cstdint>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include "gpioPin.h"

#define GPIO_DIR "/sys/class/gpio/"
#define DESKTOP_DIR "/home/ikcelod/Desktop/"

using namespace std;

class ppmReceiver{

	public:
	
	ppmReceiver(unsigned input_pin, short num_channels);
	~ppmReceiver(void);
	void wait(unsigned usecs);
	short getNumChannels(void);
	void setNumChannels(unsigned num);
	unsigned getBlankTime(void);
	void setBlankTime(unsigned val);
	unsigned getChannelValue(unsigned chan);
	unsigned setChannelValue(unsigned val, unsigned chan);
	unsigned* getChannelValues(void);
	unsigned getMinChannelValue(void);
	void setMinChannelValue(unsigned val);
	unsigned getMaxChannelValue(void);
	void setMaxChannelValue(unsigned val);
	unsigned getMaxError(void);
	void setMaxError(unsigned val);
	void startReception(void);
	void endReception(void);
	

	private:
	
	
	std::thread* receiveThread;
	gpioPin* inputPin;
	unsigned blankTime = 2100;
	unsigned minChannelValue = 1000;
	unsigned maxChannelValue = 2000;
	unsigned maxError = 10;
	short numChannels;
	unsigned* channelValues;
	unsigned microsAtPreviousPulse;
	unsigned microsAtPulse;
	unsigned pulseCounter;
	bool receiving = false;
	void receive(void);
};
