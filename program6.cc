// Daniel Zhang
// CS3377.002
// dxz170030@utdallas.edu

#include <string>
#include <iostream>
#include "cdk.h"
#include "program6.h"
#include <fstream>
#include <sstream>
#include <iomanip>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;


int main()
{

	WINDOW *window;
	CDKSCREEN *cdkscreen;
	CDKMATRIX *myMatrix;           // CDK Screen Matrix

	const char *rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
	const char *columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
	int	boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
	int	boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED, vMIXED};

	/*
	* Initialize the Cdk screen.
	*
	* Make sure the putty terminal is large enough
	*/
	window = initscr();
	cdkscreen = initCDKScreen(window);

	/* Start CDK Colors */
	initCDKColor();

	/*
	* Create the matrix.  Need to manually cast (const char**) to (char **)
	*/
	myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

	if (myMatrix ==NULL)
	{
		printf("Error creating Matrix\n");
		_exit(1);
	}

	/* Display the Matrix */
	drawCDKMatrix(myMatrix, true);
	BinaryFileHeader *myHeader = new BinaryFileHeader();
	BinaryFileRecord *myRecord = new BinaryFileRecord();

	ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
	binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
	/*
	* Dipslay the messages
	*/
	std::string magNum = "Magic: ";
	std::stringstream str;
	// Converts the magic number to hex
	str << std::hex << myHeader->magicNumber;
	// Adding the hex number to the message
	magNum += str.str();
	std::string version = "Version: "; 					// Version number
	version += std::to_string(myHeader->versionNumber);	// Adding version number to the message
	std::string numRec = "NumRecords: ";
	numRec += std::to_string(myHeader->numRecords);		// Adding numRecords to the message
	setCDKMatrixCell(myMatrix, 1, 1, magNum.c_str());	// Inserting messages into the matrix
	setCDKMatrixCell(myMatrix, 1, 2, version.c_str());
	setCDKMatrixCell(myMatrix, 1, 3, numRec.c_str());

	int recordNum = myHeader->numRecords;


	for (int i = 0; i < recordNum; i++)					// Add as many messages as the recordNum variable
	{
		binInfile.read((char *) myRecord, sizeof(BinaryFileRecord)); // Add each message from the binary file
		std::string strlen = "strlen: ";
		strlen += std::to_string(myRecord->strLength);
		setCDKMatrixCell(myMatrix, i+2, 1, strlen.c_str());
		setCDKMatrixCell(myMatrix, i+2, 2, myRecord->stringBuffer);
	}


	drawCDKMatrix(myMatrix, true);    /* required  */

	/* So we can see results, pause until a key is pressed. */
	unsigned char x;
	cin >> x;

	// Cleanup screen
	endCDK();
}
