#include <cstdint>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <thread>
#include <chrono>

#define GPIO_DIR "/sys/class/gpio/"
#define DESKTOP_DIR "/home/ikcelod/Desktop/"

using namespace std;

class ppmTransmit{

	public:
	
	ppmTransmit(unsigned output_pin, short num_channels);
	~ppmTransmit(void);
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
	void startTransmission(void);
	void endTransmission(void);
	

	private:
	
	
	ofstream fileOutput;
	std::thread* transmitThread;
	std::string gpioExport;
	std::string gpioUnexport;
	std::string gpioPinDirection;
	std::string gpioPinValue;
	unsigned outputPin;
	unsigned blankTime = 2100;
	unsigned minChannelValue = 1000;
	unsigned maxChannelValue = 2000;
	unsigned maxError = 10;
	short numChannels;
	unsigned* channelValues;
	bool transmitting = false;
	void transmit(void);
	// uint64_t getSystemTime(void);
};
