#pragma once

#include <memory>
#include <climits>

namespace Wick {
	
	typedef unsigned char BlockType;
	
	class Bitset {
		public:
			Bitset(unsigned int aLength);
			
			void setBit(unsigned int aBitIndex, bool aVal);
			bool getBit(unsigned int aBitIndex);
			
			void setBits(unsigned int aBitIndex, BlockType aBits, unsigned int aLength);
			void clearBits(unsigned int aBitIndex, unsigned int aLength);
			
			unsigned char getBlock(unsigned int aBlockIndex);
			unsigned char* get();
			
		private:		
			std::unique_ptr<BlockType[]> theInner;
			unsigned int theLength;
			
			static const unsigned int theBitsPerByte = 8;
			static const unsigned int theBlockSize = sizeof(BlockType) * theBitsPerByte;
			static const unsigned int theMaxBlockValue = UCHAR_MAX;
	};
};