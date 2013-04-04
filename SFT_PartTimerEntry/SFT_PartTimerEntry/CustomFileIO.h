#include <fstream>
#include <string>
#include <iostream> //cout, cin
#include <vector> //std::vector

#define _TXTFILENAME "SFT_STAFF.txt"
#define _DEPTTXTFILENAME "NIE_DEPT.txt"

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
		CustomFileIO( char *pSFT_FileName, char *pNIEDEPT_FileName )
		{
			std::cout << "Loading......" << std::endl;
			std::cout << std::endl;

			//Read NIE_DEPT.txt file
			if( ReadFile( pNIEDEPT_FileName ) )
			{
				std::cout << "Read NIE_DEPT File Successful." << std::endl;
				LoadFrmFileToVector();
			}
			else
			{
				std::cout << "WARNING : Read NIE_DEPT File Failed." << std::endl;
				std::cout << "Program will load embedded department names." << std::endl;
				ManualLoadDeptNames();
			}

			//stop reading the NIE Department file
			fs.close();

			//Read SFT_STAFF.txt file
			if( ReadFile( pSFT_FileName ) )
				std::cout << "Read SFT File Successful." << std::endl;
			else
				std::cout << "ERROR : Read SFT File Failed." << std::endl;

			//init all to empty string, just to be sure
			Dept , FullName, Username, Email = "";
			
			std::cout << std::endl;
		}//ctor

		~CustomFileIO()
		{
		}//dtor

		//Function to read file only
		bool ReadFile( char *pFilename );

		//Function to write file only
		bool WriteFile();

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

		//Will onlu be called if NIE_DEPT.txt file not found
		void ManualLoadDeptNames();

		//Ending credits
		unsigned int DisplayGoodbyeMsg();		
	private:
		//function

		void Clear_Cin();

		//Move to end of file
		void MoveToEndOfFile();

		//variables
		std::string Dept, FullName, Username, Email;
		std::fstream fs;
		std::vector<std::string> Vec_DeptNames;

		
	};



}//SFT
