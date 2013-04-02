#include <fstream>
#include <string>
#include <iostream> //cout, cin

#define _TXTFILENAME "SFT_STAFF.txt"

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
		CustomFileIO( char *pFileName )
		{
			if( ReadFile( pFileName ) )
				std::cout << "Read File Successful." << std::endl;
			else
				std::cout << "Read File Failed." << std::endl;

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
	};



}//SFT
