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

class ppmTransmit{

	public:
	
	ppmTransmit(unsigned pin_number, short num_channels);
	~ppmTransmit(void);
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
	void startTransmission(void);
	void endTransmission(void);
	

	private:
	
	std::thread* transmitThread;
	gpioPin* outputPin;
	unsigned blankTime = 2100;
	unsigned minChannelValue = 1000;
	unsigned maxChannelValue = 2000;
	unsigned maxError = 10;
	short numChannels;
	unsigned* channelValues;
	bool transmitting = false;
	void transmit(void);
	void wait(unsigned usecs);
};
