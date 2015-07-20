#pragma once

#include <memory>
#include <climits>

namespace Wick {
		
	class Bitset {
		public:
			typedef unsigned char BlockType;
		
			Bitset(unsigned int aLength);
			
			void setBit(unsigned int aBitIndex, bool aVal);
			bool getBit(unsigned int aBitIndex);
			
			void setBits(unsigned int aBitIndex, BlockType aBits, unsigned int aLength);
			void clearBits(unsigned int aBitIndex, unsigned int aLength);
			
			BlockType getBlock(unsigned int aBlockIndex);
			void get(BlockType** aData, unsigned int& aLength);
			
		private:		
			std::unique_ptr<BlockType[]> theInner;
			unsigned int theLength;
			unsigned int theBlockCount;
			
			static const unsigned int theBitsPerByte = 8;
			static const unsigned int theBlockSize = sizeof(BlockType) * theBitsPerByte;
			static const unsigned int theMaxBlockValue = UCHAR_MAX;
	};
};
