#include "CustomFileIO.h"
#include <string>

#define _WHDEBUG false

int main()
{
	int ToExit = 1;

	while( ToExit == 1 )
	{
		SFT::CustomFileIO Test_IO(_TXTFILENAME, _DEPTTXTFILENAME);	
		SFT::CustomFileIO::DataType DT;	

		if(_WHDEBUG)
			Test_IO.DisplayContent();

		std::cout << "Welcome to the Student Feedback Part timer input application!" << std::endl;
		std::cout << "=============================================================" << std::endl;

		//Enter fullname, department, username and email
		Test_IO.SetData(DT = SFT::CustomFileIO::DataType::DEPT);
		Test_IO.SetData(DT = SFT::CustomFileIO::DataType::FULLNAME);
		Test_IO.SetData(DT = SFT::CustomFileIO::DataType::USERNAME);
		Test_IO.SetData(DT = SFT::CustomFileIO::DataType::EMAIL);

		//Display what was keyed in by user before moving on
		Test_IO.DisplayAndVerifyEnteredData();

		//Write the new entry to file
		Test_IO.WriteFile();

		//Ending credits...
		ToExit = Test_IO.DisplayGoodbyeMsg();
	}//while

	system("Pause");
	return 0;

}//main
