/**
Author	: Chan Win Hung
Email	: winhung.chan@nie.edu.sg
*/


#include <fstream>
#include <string>
#include <iostream> //std::cout, std::cin
#include <vector> //std::vector
#include <sstream> //std::stringstream
#include <iomanip> //std::setw

#define TXTFILENAME "SFT_STAFF.txt"
#define DEPTTXTFILENAME "NIE_DEPT.txt"
#define WHDEBUG false

namespace SFT
{
	class CustomFileIO
	{
	public:
		enum DataType
		{
			DEPT = 0,
			FULLNAME = 1,
			USERNAME = 2,
			EMAIL = 3	
		};

		//ctor
		CustomFileIO( char *pSFT_FileName, char *pNIEDEPT_FileName );

		//dtor
		~CustomFileIO();

		//Function to read file only
		bool OpenFile( char *pFilename );

		//Function to write file only
		bool WriteFile();

		//Closes the file
		void CloseFile();

		//Function to load the contents of the file into an array for NIE Dept
		void LoadFrmFileToVector();

		//test func to check if the contents of the file can be viewed
		void DisplayContent();

		//func to display what user has entered
		void DisplayAndVerifyEnteredData();

		//func to check if file was open proplery
		bool IsFileOpenSuccessfully();

		//Set fullname
		void SetData( DataType d );

		//Ensure that the username given is one word only. Eg.whchan
		bool VerifyUsernameSyntax( const char *pUsername );
				
		//Ensure that user enters a valid email. Meaning, must be seperated by only one '@'
		bool VerifyEmailSyntax ( const char *pEmail );

		//Will only be called if NIE_DEPT.txt file not found
		void ManualLoadDeptNames();

		//Ending credits
		unsigned int DisplayGoodbyeMsg();		

		//To clear the contents in te cin buffer and clear it's flags
		void Clear_Cin();

		//Move to end of file
		void MoveToEndOfFile();

		//Create SFT_STAFF.txt file when loading of it fails
		void CreateSftStaffFile();

		//Determine best cout width by finding the largest in string size
		void FindBestWidth( DataType ColName, unsigned int SizeOfCurrData );

		//Set the cout's width. The string with the most alphabets wins
		void SetColCoutWidth( DataType ColName,  unsigned int Width );

		//Find and display only the acronyms of the depts
		std::string ReturnDeptInAcronyms( std::string DeptName );

	private:		
		std::string DeptLong, DeptAcronym, FullName, Username, Email;
		std::fstream fs;
		std::vector<std::string> Vec_DeptNames;
		unsigned int DeptAcronymCoutWidth, FullnameCoutWidth, UsernameCoutWidth, EmailCoutWidth;
	};

}//SFT
