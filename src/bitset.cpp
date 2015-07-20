#include "bitset.h"

#include <stdexcept>

Wick::Bitset::Bitset(unsigned int aLength) {
	unsigned int aBytes = aLength / theBlockSize;
	
	if( aLength % theBlockSize != 0) {
		aBytes += 1;
	}
	
	theInner = std::unique_ptr<BlockType[]>(new BlockType[aBytes]);
	theLength = aLength;
}

void Wick::Bitset::setBit(unsigned int aBitIndex, bool aVal) {
	if(theLength <= aBitIndex ) {
		throw std::invalid_argument("setBit:Requested bit is outside range");
	}
	
	unsigned int myBlockIndex = aBitIndex / theBlockSize;
	unsigned int myBitMask = 1 << (aBitIndex % theBlockSize);
	
	if(aVal) {
		theInner[myBlockIndex] |= myBitMask;
	} else {
		theInner[myBlockIndex] &= ~(myBitMask);
	}
}

bool Wick::Bitset::getBit(unsigned int aBitIndex) {
	if(theLength <= aBitIndex ) {
		throw std::invalid_argument("getBit:Requested bit is outside range");
	}
	
	unsigned int myBlockIndex = aBitIndex / theBlockSize;
	unsigned int myBitMask = 1 << (aBitIndex % theBlockSize);
	
	if((theInner[myBlockIndex] & myBitMask) == 0) {
		return false;
	} else {
		return true;
	}
}

void Wick::Bitset::setBits(unsigned int aBitIndex, BlockType aBits, unsigned int aLength) {
	if(aLength > theBlockSize) {
		throw std::invalid_argument("setBits:Length of bits to set is too long");
	} else if(theLength <= aBitIndex) {
		throw std::invalid_argument("setBits:Requested bit is outside range");
	} else if(theLength <= aBitIndex + aLength) {
		throw std::invalid_argument("setBits:The index plus the length exceeds to bitset length");
	}
		
	unsigned int myBlockIndex = aBitIndex / theBlockSize;
	int myEndBit = (aBitIndex % theBlockSize) + aLength - theBlockSize;
	Wick::BlockType myMask = theMaxBlockValue; // 11111111
		
	if(myEndBit > 0) {
		// clear the data in the area that we're going to read data into
		theInner[myBlockIndex + 1] &= (theMaxBlockValue >> myEndBit);
		// set the bits in the spill over area
		theInner[myBlockIndex + 1] |= (aBits << (aLength - myEndBit));
	} else {
		// leave an empty space at the end of the mask for data left in the byte
		myMask <<= theBlockSize - aLength;
	}
	
	// shift the mask to the starting position of the clear
	myMask >>= (aBitIndex % theBlockSize);
	// clear the data in the area we're about to read data into
	theInner[myBlockIndex] &= ~myMask;
	// read in the data in the starting block
	theInner[myBlockIndex] |= (aBits >> (aBitIndex % theBlockSize));	
}

void Wick::Bitset::clearBits(unsigned int aBitIndex, unsigned int aLength) {
	if(theLength <= aBitIndex) {
		throw std::invalid_argument("setBits:Requested bit is outside range");
	} else if(theLength <= aBitIndex + aLength) {
		throw std::invalid_argument("setBits:The index plus the length exceeds to bitset length");
	}
	
	unsigned int myStartBlockIndex = aBitIndex / theBlockSize;
	unsigned int myEndBlockIndex = (aBitIndex + aLength) / theBlockSize;
	// calculate the number of bits that will spill into the end block
	int myEndBit = (aBitIndex + aLength) % theBlockSize;
	BlockType myMask = theMaxBlockValue; // all bits in mask set to 1

	if(myStartBlockIndex != myEndBlockIndex) {
		// clear the spill into the last applicable block
		theInner[myEndBlockIndex] &= (theMaxBlockValue >> myEndBit);
		// clear each block between the starting and end blocks
		for(myEndBlockIndex -= 1; myEndBlockIndex != myStartBlockIndex; myEndBlockIndex--) {
			theInner[myEndBlockIndex] = 0;
		}
	} else {
		// the clear is all within one block
		// leave an empty space at the end of the mask for data left in the block
		myMask <<= theBlockSize - aLength;
	}
	
	// shift the mask to the starting position of the clear
	myMask >>= (aBitIndex % theBlockSize);
	
	// use the inverse of the mask to clear all bits set in the mask,
	// while maintaining the rest of the data
	theInner[myStartBlockIndex] &= ~myMask;
}

unsigned char Wick::Bitset::getBlock(unsigned int aBlockIndex) {
	return theInner[aBlockIndex];
}
