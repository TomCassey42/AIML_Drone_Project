#ifndef GPIOPIN_H
#define GPIOPIN_H

#include <iostream>
#include <fstream>
#include <chrono>

#define GPIO_DIR "/sys/class/gpio/"

using namespace std;
class gpioPin{

	public:

	gpioPin(unsigned pin_number);
	gpioPin(unsigned val, const char* direction);
	~gpioPin(void);
	void setValue(unsigned val);
	unsigned getValue(void);
	void setDirection(const char* direction);
	string getDirection(void);
	unsigned waitForRisingEdge(void);
	unsigned waitForFallingEdge(void);

	private:
	
	void wait(unsigned usecs);
	ofstream fileOutput;
	ofstream valueOutput;
	ifstream valueInput;
	string gpioExportPath = string(GPIO_DIR) + string("export");
	string gpioUnexportPath = string(GPIO_DIR) + string("unexport");
	string gpioPinDirectionPath;
	string gpioPinValuePath;
	unsigned pin_number_;
	unsigned value_;
	string direction_;

};

#endif
