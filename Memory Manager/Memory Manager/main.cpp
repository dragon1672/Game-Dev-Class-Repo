#include <stdlib.h>

#define byte char

class meHeap {
	static const int sizeOfDataSize = sizeof(size_t); // stored before every dataBit
	void * theData;

	struct MemBlock {
		size_t size;
		void * nextIndex;
	} *header;
public:
	meHeap() {
		//
	}
	void consolidate() {
		consolidate1();
	}
	void consolidate1() {
		//grabbing the first block in memory
		MemBlock * currentBlock = nextMemBlockInMemory(nullptr);//grabs the first in memory
		while(currentBlock) {
			combineWithNextContiguousBlockIfValid(currentBlock);
			currentBlock = nextMemBlockInMemory(currentBlock); // find the nextBlock
		}
	}
	MemBlock * nextMemBlockInMemory(void * minBounds) {
		MemBlock * firstMemBlock = nullptr;
		MemBlock * runner = (MemBlock *)header;
		while(runner) {
			if(runner>minBounds && (runner<firstMemBlock || firstMemBlock==nullptr)) firstMemBlock = runner;
		}
		return firstMemBlock;
	}
	void * combineWithNextContiguousBlockIfValid(void * start) {
		MemBlock * runner = (MemBlock *)start;
		void * target = (char *)start+runner->size;
		while(runner) {
			if(runner==target) {
				((MemBlock *)start)->size += runner->size;
				((MemBlock *)start)->nextIndex = runner->nextIndex;
				combineWithNextContiguousBlockIfValid(start);//do it again!
			}
		}
	}
	void init() {
		const int sizeOfRam = 256;
		theData = malloc(sizeOfRam);
		header = (MemBlock *)theData;
		header->size = sizeOfRam;
		header->nextIndex = nullptr;
	}
	void shutdown() {
		free(theData);
	}
	void * newIt(size_t size) {
		size += sizeOfDataSize;//adds on memory for storing the size;
		size = (size < sizeof(MemBlock))? sizeof(MemBlock) : size; // upgrades the size to always allow for memory block
		MemBlock * currentBlock  = (MemBlock *)header;
		MemBlock * previousBlock = nullptr;
		MemBlock * nextMemBlock  = nullptr; //holds the next memblock
		while(currentBlock) {
			if(currentBlock->size >= size) {
				// size remaining in current block
				int leftOverSize = currentBlock->size-size;
				
				// left overs cannot fit new mem block
				if(leftOverSize < sizeof(MemBlock)) {
					nextMemBlock = (MemBlock *)currentBlock->nextIndex;
					size = currentBlock->size; // upgrade the size
				} else { // fit in current MemBlock
					nextMemBlock = (MemBlock *)((byte *)currentBlock+size);//offset by size;
					nextMemBlock->size = leftOverSize;
					nextMemBlock->nextIndex = currentBlock->nextIndex;
				}
				break;
			}
			previousBlock = currentBlock;
			currentBlock  = (MemBlock *)currentBlock->nextIndex;
		} // end while
		if(currentBlock==nullptr || nextMemBlock==nullptr) { // out of memory
			return nullptr;
		}

		if(previousBlock != nullptr) { // not at the head
			previousBlock->nextIndex = nextMemBlock;
		} else { // is at the headptr
			header = nextMemBlock;
		}

		currentBlock->size = size;
		return (byte *)currentBlock+sizeOfDataSize;
	}
	void deleteIt(void * toDel) {
		void * lastHeader = header;
		header = (MemBlock *)((size_t *)toDel - 1);//moving back by size of int
		MemBlock * currentHeader = (MemBlock *)header;
		currentHeader->nextIndex = lastHeader;
		//size is still the same and doens't need to be updated
	}
	void debugFill(void * start, size_t bytes) {
		const char first  = 'N';
		const char second = 'O';
		char temp = first;
		for(void * i=start;i<(char *)start+bytes;i=(char *)i+1) {
			*(char *)start = temp;
			temp = (temp==second)? first : second;
		}
	}
} myHeap;

void * operator new(size_t size) {
	return myHeap.newIt(size);
}
void operator delete(void * toDel) {
	myHeap.deleteIt(toDel);
}




struct Vector { int x,y,z; };
//basic new and delete
void test1() {
	int * p1 = new int;		*p1 = 0x11111111;
	int * p2 = new int;		*p2 = 0x22222222;
	int * p3 = new int;		*p3 = 0x33333333;
	delete p2;
	delete p1;
	delete p3;
	p1  = new int;
	*p1 = 0x11111111;
	p2  = new int;
	*p2 = 0x22222222;
	p3  = new int;
	*p3 = 0x33333333;
	delete p2;
	delete p1;
	delete p3;
}

//new of different sizes
void test2() {
	int * p1    = new int;		*p1 = 0x11111111;
	__int64 * p2 = new __int64;	*p2 = 0x2222222222222222;
	int * p3    = new int;		*p3 = 0x33333333;
	delete p2;
	delete p1;
	delete p3;
}

//testing different cases
void test3() {
	int * p1    = new int;		*p1 = 0x11111111;
	__int64 * p2 = new __int64;	*p2 = 0x2222222222222222;
	int * p3    = new int;		*p3 = 0x33333333;
	delete p2;
	delete p1;
	delete p3;
}

//creating and filling gaps
void test4() {
	int * p0     = new int;
	*p0 = 0xFFFFFFFF;
	delete p0;
	int * p1     = new int;		//end
	*p1 = 0x11111111;
	__int64 * p2 = new __int64;	//end
	*p2 = 0x2222222222222222;
	int * p3     = new int;		//end
	*p3 = 0x33333333;
	delete p2;					//creates gap, updates header
	int * p4     = new int;		//should fit in gap
	*p4 = 0x44444444;
	int * p5     = new int;		//will not fit in gap because size won't fit
	*p5 = 0x55555555;
	int * p6     = new int;		//end
	*p6 = 0x66666666;
	int * p7     = new int;		//end
	*p7 = 0x77777777;
	int * p8     = new int;		//end
	*p8 = 0x88888888;
	delete p6;					//create gap
	int * p9     = new int;		//fill in gap
	*p9 = 0x99999999;
	delete p7;					//create gap
	delete p9;					//create larger gap
	int * p10     = new int;		//fill half of gap
	*p10 = 0xAAAAAAAA;
	int * p11     = new int;		//fill gap completely
	*p11 = 0xBBBBBBBB;
	int * p12     = new int;		//end
	*p12 = 0xCCCCCCCC;
	delete p12;					//add block before end;
	//checking memory
	if( *(p1-1 ) != 8          ) throw("Anthony Should Learn How to Code");
	if( *(p1   ) != 0x11111111 ) throw("Anthony Should Learn How to Code");
	if( *(p1+1 ) != 12         ) throw("Anthony Should Learn How to Code");
	if( *(p1+2 ) != 0x44444444 ) throw("Anthony Should Learn How to Code");
	if( *(p1+3 ) != 0x22222222 ) throw("Anthony Should Learn How to Code"); // because i'm not cleaning out old data and size gets upgraded
	if( *(p1+4 ) != 8          ) throw("Anthony Should Learn How to Code");
	if( *(p1+5 ) != 0x33333333 ) throw("Anthony Should Learn How to Code");
	if( *(p1+6 ) != 8          ) throw("Anthony Should Learn How to Code");
	if( *(p1+7 ) != 0x55555555 ) throw("Anthony Should Learn How to Code");
	if( *(p1+8 ) != 8          ) throw("Anthony Should Learn How to Code");
	if( *(p1+9 ) != 0xaaaaaaaa ) throw("Anthony Should Learn How to Code");
	if( *(p1+10) != 8          ) throw("Anthony Should Learn How to Code");
	if( *(p1+11) != 0xbbbbbbbb ) throw("Anthony Should Learn How to Code");
	if( *(p1+12) != 8          ) throw("Anthony Should Learn How to Code");
	if( *(p1+13) != 0x88888888 ) throw("Anthony Should Learn How to Code");
	if( *(p1+14) != 8          ) throw("Anthony Should Learn How to Code");
	if( *(p1+15) != *(p1+15)   ) throw("Anthony Should Learn How to Code");
	if( *(p1+16) != 0xbc       ) throw("Anthony Should Learn How to Code");
	if( *(p1+17) != 0x00000000 ) throw("Anthony Should Learn How to Code");
}

int main() {
	/*
	myHeap.init();
	test1();
	myHeap.shutdown();
	//*/
	/*
	myHeap.init();
	test2();
	myHeap.shutdown();
	//*/
	/*
	myHeap.init();
	test3();
	myHeap.shutdown();
	//*/
	//*
	myHeap.init();
	test4();
	myHeap.shutdown();
	//*/
	return 0;
}