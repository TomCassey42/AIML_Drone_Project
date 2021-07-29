#include "gpioPin.h"

gpioPin::gpioPin(unsigned pin_number, const char* direction){
	pin_number_ = pin_number;
	direction_ = direction;
	
	gpioPinDirectionPath = string(GPIO_DIR) + string("gpio") + 
		std::to_string(pin_number) + string("/direction");
	gpioPinValuePath = string(GPIO_DIR) + string("gpio") + 
		std::to_string(pin_number) + string("/value");

	fileOutput.open(gpioExportPath);
	fileOutput << pin_number_;
	fileOutput.close();

	valueOutput.open(gpioPinValuePath);
	valueInput.open(gpioPinValuePath);

	fileOutput.open(gpioPinDirectionPath);
	fileOutput << direction_;
	fileOutput.close();
}
gpioPin::gpioPin(unsigned pin_number){
	pin_number_ = pin_number;

	gpioPinDirectionPath = string(GPIO_DIR) + string("gpio") + 
		std::to_string(pin_number) + string("/direction");
	gpioPinValuePath = string(GPIO_DIR) + string("gpio") + 
		std::to_string(pin_number) + string("/value");
	valueOutput.open(gpioPinValuePath);
	valueInput.open(gpioPinValuePath);

	fileOutput.open(gpioExportPath);
	fileOutput << pin_number_;
	fileOutput.close();
}
gpioPin::~gpioPin(void){
	fileOutput.open(gpioUnexportPath);
	fileOutput << pin_number_;
	fileOutput.close();
	valueOutput.close();
	valueInput.close();
}
void gpioPin::setValue(unsigned val){
	value_ = val;
	valueOutput << value_;
	valueOutput.flush();
}
unsigned gpioPin::getValue(void){
	char str;
	valueInput.get(str);
	valueInput.seekg(0);
	value_ = str - '0';
	return value_;
}
void gpioPin::setDirection(const char* direction){
	direction_ = direction;
	fileOutput.open(gpioPinDirectionPath);
	fileOutput << direction_;
	fileOutput.close();
}
string gpioPin::getDirection(void){
	return direction_;
}
void gpioPin::wait(unsigned usecs){
	auto startClock = chrono::high_resolution_clock::now();
	while((chrono::high_resolution_clock::now() - startClock).count() /1000 < usecs);
}
unsigned gpioPin::waitForRisingEdge(void){
	auto startClock = chrono::high_resolution_clock::now();
	while (getValue());
	while (!getValue());
	return (chrono::high_resolution_clock::now() - startClock).count() / 1000;
}
unsigned gpioPin::waitForFallingEdge(void){
	auto startClock = chrono::high_resolution_clock::now();
	while (!getValue());
	while (getValue());
	return (chrono::high_resolution_clock::now() - startClock).count() / 1000;
}
