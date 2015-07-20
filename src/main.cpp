#include "bitset.h"

#include <iostream>

int main() {
	Wick::Bitset myBitset(100);
	
	myBitset.setBit(0, true);

	std::cout << myBitset.getBit(0) << std::endl;
	
	myBitset.setBit(0, false);
	
	std::cout << myBitset.getBit(0) << std::endl;
	
	myBitset.setBit(99, true);

	std::cout << myBitset.getBit(99) << std::endl;
	
	myBitset.setBit(99, false);
	
	std::cout << myBitset.getBit(99) << std::endl;
	
	myBitset.setBit(3, true);

	std::cout << myBitset.getBit(3) << std::endl;
	
	myBitset.setBit(3, false);
	
	std::cout << myBitset.getBit(3) << std::endl;
	
	myBitset.setBit(7, true);

	std::cout << myBitset.getBit(7) << std::endl;
	
	myBitset.setBit(7, false);
	
	std::cout << myBitset.getBit(7) << std::endl;
	
	try {
		myBitset.setBit(100, true);	
	} catch(const std::invalid_argument& ia) {
		std::cerr << ia.what() << std::endl;
	}
	
	try {
		myBitset.setBit((unsigned char) -1, true);	
	} catch(const std::invalid_argument& ia) {
		std::cerr << ia.what() << std::endl;
	}
	
	for(unsigned int i = 0; i < 16; i++)
		myBitset.setBit(i, true);
	
	myBitset.clearBits(2, 2);
	myBitset.clearBits(5, 7);
	
	std::cout << "Partial clear:" << (unsigned int)myBitset.getBlock(0) << std::endl;
	
	myBitset.clearBits(0, 16);
	
	std::cout << "Full clear:" << (unsigned int)myBitset.getBlock(0) << std::endl;
	
	myBitset.setBits(0, 255, 8);
	myBitset.setBits(8, 255, 8);
	myBitset.setBits(16, 255, 8);
	
	std::cout << (unsigned int)myBitset.getBlock(0) << std::endl;
	std::cout << (unsigned int)myBitset.getBlock(1) << std::endl;
	std::cout << (unsigned int)myBitset.getBlock(2) << std::endl;
	
	myBitset.clearBits(3,2);
	
	std::cout << (unsigned int)myBitset.getBlock(0) << std::endl;
	std::cout << (unsigned int)myBitset.getBlock(1) << std::endl;
	std::cout << (unsigned int)myBitset.getBlock(2) << std::endl;
	
	return 0;
}
