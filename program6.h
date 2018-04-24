// Daniel Zhang
// CS3377.002
// dxz170030@utdallas.edu
#ifndef PROGRAM_6
#define PROGRAM_6

#include <stdint.h>

// Binary File Header class
class BinaryFileHeader
{
public:
	uint32_t magicNumber;
	uint32_t versionNumber;
	uint64_t numRecords;
};

const int maxRecordStringLength = 25;
// Binary File Record class
class BinaryFileRecord
{
public:
	uint8_t strLength;
	char stringBuffer[maxRecordStringLength];
};

#endif // PROGRAM_6
