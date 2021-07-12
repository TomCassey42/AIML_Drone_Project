#include "ppmTransmit.cpp"

int main(int argc, char** argv){
	ppmTransmit ppm(79, 3);
	ppm.setChannelValue(1200, 0);
	ppm.setChannelValue(1500, 1);
	ppm.setChannelValue(1100, 2);
	ppm.startTransmission();
	std::this_thread::sleep_for(10000ms);
	ppm.endTransmission();
}
