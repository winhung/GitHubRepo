/**
Author	: Chan Win Hung
Email	: winhung.chan@nie.edu.sg
*/

#include "CustomFileIO.h"
#include <string>

int main()
{
	int ToExit = 1;

	while( ToExit == 1 )
	{
		SFT::CustomFileIO Test_IO(TXTFILENAME, DEPTTXTFILENAME);	
		SFT::CustomFileIO::DataType DT;	

		//@ToDo : Shift this test cases to another file ?
		if(WHDEBUG)
		{
			std::cout << "***************DEBUG****************" << std::endl;
			Test_IO.DisplayContent();			
		}

		std::cout << "Welcome to the Student Feedback Part timer input application!" << std::endl;
		std::cout << std::endl;

		//Enter fullname, department, username and email
		Test_IO.SetData(DT = SFT::CustomFileIO::DataType::DEPT);
		Test_IO.SetData(DT = SFT::CustomFileIO::DataType::FULLNAME);
		Test_IO.SetData(DT = SFT::CustomFileIO::DataType::USERNAME);
		Test_IO.SetData(DT = SFT::CustomFileIO::DataType::EMAIL);

		//Display what was keyed in by user before moving on
		Test_IO.DisplayAndVerifyEnteredData();

		//Write the new entry to file
		if( Test_IO.WriteFile() )
			std::cout << "Entry created...." << std::endl;

		//Ending credits...
		ToExit = Test_IO.DisplayGoodbyeMsg();
	}//while

	system("Pause");
	return 0;

}//main
