/**
Author	: Chan Win Hung
Email	: winhung.chan@nie.edu.sg
*/

#include "CustomFileIO.h"

namespace SFT
{
	//Constructor
	CustomFileIO::CustomFileIO( char *pSFT_FileName, char *pNIEDEPT_FileName )
	{
		std::cout << "Loading......" << std::endl;
			std::cout << std::endl;

			//Read NIE_DEPT.txt file
			if( OpenFile( pNIEDEPT_FileName ) )
			{
				std::cout << "Load NIE_DEPT File Successful." << std::endl;
				LoadFrmFileToVector();

				//stop reading the NIE Department file
				CloseFile();
			}
			else
			{
				std::cout << "WARNING : Load NIE_DEPT File Failed." << std::endl;
				std::cout << "Program will load embedded department names." << std::endl;
				ManualLoadDeptNames();
			}		

			//Read SFT_STAFF.txt file
			while( !OpenFile( pSFT_FileName ) )			
			{
				std::cout << "ERROR : Load SFT File Failed." << std::endl;
				std::cout << "ERROR : Unable to Load SFT file, will create one." << std::endl;
				CreateSftStaffFile();
			}//while

			//Reaching here would mean SFT_STAFF file was loaded successfully
			std::cout << "Load SFT File Successful." << std::endl;

			//init all to their respective column name
			DeptLong = "Department";
			DeptAcronym = "XXX";
			FullName = "Fullname";
			Username = "Username";
			Email = "Email";

			//Fix the width according to their department names first
			DeptAcronymCoutWidth = DeptLong.size(); 
			FullnameCoutWidth = FullName.size(); 
			UsernameCoutWidth = Username.size(); 
			EmailCoutWidth = Email.size();
			
			std::cout << std::endl;	
	}//ctor

	CustomFileIO::~CustomFileIO()
	{
	
	}//dtor

	bool CustomFileIO::OpenFile( char *pFilename )
	{
		fs.open( pFilename );

		return IsFileOpenSuccessfully();
	}//ReadFile

	void CustomFileIO::CloseFile()
	{
		fs.close();
	}//CloseFile
	
	void CustomFileIO::LoadFrmFileToVector()
	{
		char c = fs.get();
		std::string Str_Dept;

		while( !fs.eof() )
		{			
			if( c == '\n' )
			{
				Vec_DeptNames.push_back( Str_Dept );
				
				//Empty the String Str_Dept and clear it's flags, if any
				Str_Dept = "";
				Str_Dept.clear();
			}
			else
				Str_Dept.push_back( c );

			c = fs.get();
		
		}//while

		//Store the last value before end of file
		Vec_DeptNames.push_back( Str_Dept );
						
	}//LoadFrmFileToVector

	bool CustomFileIO::WriteFile()
	{	
		long SizeOfData = DeptLong.size() + FullName.size() 
			+ Email.size() + Username.size() + sizeof('\n') + 3*sizeof('\t');

		std::string FullDetails = 
			'\n' 
			+ DeptLong + '\t' + FullName + '\t' + Email + '\t' + Username;

		//check if file is opened first
		while( !IsFileOpenSuccessfully() )
		{
			std::cout << "File SFT_STAFF.txt not found." << std::endl;
			std::cout << "Please kindly ensure that it is in the same folder as this program and the file is named as SFT_STAFF.txt" << std::endl;
			std::cout << "Press enter for me to try again." << std::endl;
			std::cout << "To quit, please press Ctrl + C" << std::endl;
			std::cout << std::endl;
			
			//As long as user press the enter key with any content
			if( std::cin.get() )
			{
				//Try opening the file again
				OpenFile(TXTFILENAME);

				//Clear the Cin buffer and all it's flags if any
				Clear_Cin();
			}//if						
		}//while

		//Move to one char before EOF
		MoveToEndOfFile();

		//Write the contents into the file
		fs.write(FullDetails.c_str(), SizeOfData);

		return true;
	}//WriteFile
	
	bool CustomFileIO::IsFileOpenSuccessfully()
	{
		if( fs.fail() )
			return false; //File opened successfully

		//Cannot open file properly
		return true;
	}//IsFileOpenSuccessfully

	void CustomFileIO::DisplayContent()
	{
		char c;
		while( fs.good() )
		{
			c = fs.get();
			std::cout << c;		
		}//while	
	}//DisplayContent

	void CustomFileIO::DisplayAndVerifyEnteredData()
	{
		char Reply = 'n', Entry = '0';

		while(Reply == 'n')
		{
			std::cout << std::endl;
			std::cout << "Here's what you have entered" << std::endl;
			
			//Print out the heading first
			std::cout << std::setw(DeptAcronymCoutWidth) << std::left << "Department" << " ";
			std::cout << std::setw(FullnameCoutWidth) << std::left << "Fullname" << " ";
			std::cout << std::setw(UsernameCoutWidth) << std::left << "Username" << " ";
			std::cout << std::setw(EmailCoutWidth) << std::left << "Email" << std::endl;
			
			//Print out the values
			std::cout << std::setw(DeptAcronymCoutWidth) << std::left << DeptAcronym
				<< " ";
			std::cout << std::setw(FullnameCoutWidth) << std::left << FullName 
				<< " ";
			std::cout << std::setw(UsernameCoutWidth) << std::left << Username 
				<< " ";
			std::cout << std::setw(EmailCoutWidth) << std::left << Email 
				<< std::endl;
			
			std::cout << std::endl;

			std::cout << "Is this correct ? Key in y for YES and n for NO." << std::endl;
			std::cin >> Reply;

			if( Reply == 'n' )
			{
				std::cout << "Which section needs to be changed ?" << std::endl;
				std::cout << "Key in..." << std::endl;
				std::cout << "1 for Department" << std::endl;
				std::cout << "2 for Fullname" << std::endl;
				std::cout << "3 for Username" << std::endl;
				std::cout << "4 for Email" << std::endl;
				std::cout << "Key in anything else to go back." << std::endl;

				Clear_Cin();
				std::cin >> Entry;

				//Clear again
				Clear_Cin();

				switch (Entry)
				{
				case '1':
					SetData( DEPT );
					break;

				case '2':
					SetData( FULLNAME );
					break;

				case '3':
					SetData( USERNAME );
					break;

				case '4':
					SetData( EMAIL );
					break;

				default:
					break;
				}//switch

				if( Entry != '1' || Entry != '2' 
					|| Entry != '3' || Entry != '4')
					continue; //restart
		
			}//if
		}//while

	}//DisplayEnteredData

	//Set Basic parameters
	void CustomFileIO::SetData( CustomFileIO::DataType d )
	{
		bool EntryComplete = false;
		std::string CurrQn = "", CurrData = "";
		
		//Used only with Department Names
		unsigned index = 0;

		//Decide which question to ask
		switch( d )
		{
			case DEPT:
				CurrQn = "department";
				break;

			case FULLNAME:
				CurrQn = "full name";
				break;

			case USERNAME:
				CurrQn = "username";
				break;

			case EMAIL:
				CurrQn = "email";
				break;

			default:
				break;		
		}//switch-case

		while( !EntryComplete )
		{
			CurrData = "";//instantiate it with empty string
			CurrData.clear(); //clear it's flags

			std::cout << "Please enter part-timer's " << CurrQn << std::endl;
						
			if( d != DataType::DEPT )
				std::getline(std::cin, CurrData);

			if( d == DataType::DEPT )
			{
				std::vector<std::string>::iterator VecItr_DeptName 
					= Vec_DeptNames.begin();

				std::cout << "Key in the number for the respective "
					 "department you would like to enter..." << std::endl;
				std::cout << std::endl;

				//Print out all the known dept names from NIE_DEPT.txt
				for( unsigned int i = 1; 
					VecItr_DeptName != Vec_DeptNames.end(); 
					++i, ++VecItr_DeptName )
				{
					std::cout << i << ". " << *VecItr_DeptName << std::endl;				
				}//for				

				bool IsValid = false;
				while( !IsValid )
				{	
					std::string Input = "";
					std::getline(std::cin, Input);

					std::stringstream StrStream(Input);

					StrStream >> index;

					if( index == 0 || index > Vec_DeptNames.size() )
					{
						std::cout 
							<< "ERROR : Please enter a value between 1 to " 
							<< Vec_DeptNames.size() 
							<< std::endl;

						continue;
					}
					else
						IsValid = true;
				
				}//while			
			}//if
			else if( d == DataType::USERNAME )
			{
				if( !VerifyUsernameSyntax(CurrData.c_str()) )
				{
					std::cout << "ERROR : Username format is wrong. No spaces please." << std::endl;
					std::cout << std::endl;
					continue; //restart !
				}//if
			}//if
			else if( d == DataType::EMAIL )
			{
				if( !VerifyEmailSyntax(CurrData.c_str()) )
				{
					std::cout << "ERROR : Email format is wrong. Please check again." << std::endl;
					continue; //restart !
				}
			}//else-if

			//Data format is accepted
			EntryComplete = true;
		}//while

		//Set the data to the correct variables
		switch( d )
		{
			case DEPT:
				//Department names in long format..
				CurrData = Vec_DeptNames[index-1]; //index-1 because we diplay the values from 1 and not 0
				DeptLong = CurrData;				
				
				//Department names in Acronym format...
				DeptAcronym = ReturnDeptInAcronyms( CurrData );
				//Do this to update the CurrData's size
				CurrData = DeptAcronym;
				break;

			case FULLNAME:
				FullName = CurrData;
				break;

			case USERNAME:
				Username = CurrData;
				break;

			case EMAIL:
				Email = CurrData;
				break;

			default:
				break;		
		}//switch-case

		//Set the cout's width for printing neatly
		FindBestWidth( d, CurrData.size() );			

	}//SetFullname

	//Ensure that the username given is one word only. Eg.whchan
	bool CustomFileIO::VerifyUsernameSyntax( const char *pUsername )
	{
		while(*pUsername)
		{
			if(*pUsername == ' ')
				return false;

			//Move on
			++pUsername;
		}//while

		return true;		
	}//VerifyUsernameSyntax

	//Ensure that user enters a valid email. Meaning, must be seperated by only one '@'
	bool CustomFileIO::VerifyEmailSyntax ( const char *pEmail )
	{
		bool IsOneAtSign = false, HasAtLeastOneDot = false;

		while(*pEmail)
		{
			if(*pEmail == '@')
			{
				if(!IsOneAtSign)
					IsOneAtSign = true;
				else
					return false; //more than one @ found
			}//if

			if(*pEmail == '.' && !HasAtLeastOneDot)
				HasAtLeastOneDot = true;

			//Move on
			++pEmail;
		}//while

		if(!IsOneAtSign || !HasAtLeastOneDot)
			return false; //Every email should have an '@' and at least one '.'

		return true;
	}//VerifyEmailSyntax

	void CustomFileIO::Clear_Cin()
	{
		//Ignore to the end of line
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		//clear it's flags
		std::cin.clear();
	}//Clear_Cin

	void CustomFileIO::MoveToEndOfFile()
	{
		//Position to the end of the text file to start writing from there
		fs.seekg(0, fs.end);
	}//MoveToEndOfFile

	unsigned int CustomFileIO::DisplayGoodbyeMsg()
	{
		std::cout << "Part time staff " + FullName + " has been added." << std::endl;
		std::cout << "Here's what you can do next...." << std::endl;
		std::cout << "Press and enter 1 to add another entry or" << std::endl;
		std::cout << "Press and enter 2 to exit" << std::endl;		
		
		unsigned int Input = 0;
		bool SecondTime = false, IsInputWrong = true;

		while( IsInputWrong )
		{
			if(SecondTime)
			{
				std::cout << std::endl;
				std::cout << "ERROR : Please key in only 1 or 2 before pressing enter." << std::endl;
				std::cout << std::endl;
			}

			std::cin >> Input;
			Clear_Cin();

			SecondTime = true;

			if( Input == 1 || Input == 2 )
				IsInputWrong = false;
		}//while

		CloseFile();//close the file stream to save current entry

		return Input;
	}//DisplayGoodbyeMsg

	void CustomFileIO::ManualLoadDeptNames() 
	{
		Vec_DeptNames.push_back("Visual & Performing Arts (VPA)");
		Vec_DeptNames.push_back("Natural Sciences & Science Education (NSSE)");
		Vec_DeptNames.push_back("Mathematics & Mathematics Education (MME)");
		Vec_DeptNames.push_back("English Language & Literacy (ELL)");
		Vec_DeptNames.push_back("Psycological Studies (PS)");
		Vec_DeptNames.push_back("Policy & Leadership Studies (PLS)");
		Vec_DeptNames.push_back("Early Childhood & Special Needs Education (ECSE)");
		Vec_DeptNames.push_back("Learning Sciences & Technologies (LST)");
		Vec_DeptNames.push_back("Curriculum, Teaching and Learning (CTL)");
		Vec_DeptNames.push_back("Asian Languages & Cultures (ALC)");
		Vec_DeptNames.push_back("Humanities & Social Studies Education (HSSE)");
		Vec_DeptNames.push_back("Physical Education & Sports Science (PESS)");
		Vec_DeptNames.push_back("Office of Education Research (OER)");
		Vec_DeptNames.push_back("Centre for Research in Pedagogy & Practice (CRPP)");
		Vec_DeptNames.push_back("Learning Sciences Laboratory (LSL)");
		
		//@ToDo : Shift these test cases else where ?
		if(WHDEBUG)
		{
			for( std::vector<std::string>::iterator IT = Vec_DeptNames.begin();
				IT != Vec_DeptNames.end();
				++IT)
			{
				std::cout << "***************DEBUG****************" << std::endl;
				std::cout << *IT << std::endl;
				std::cout << "************************************" << std::endl;
			}//for
		}//if
	}//ManualLoadDeptNames

	void CustomFileIO::CreateSftStaffFile()
	{
		std::cout << "Creating SFT_STAFF.txt file" << std::endl;
		std::ofstream SteamOut_File;
		
		//File cannot be found, hence ofstream will create one
		SteamOut_File.open("SFT_STAFF.txt");

		//Input the necessary headers for file to work
		SteamOut_File << "DEPTDESCL\tNAME\tEMAIL\tUSERID";

		//Close it to save the work
		SteamOut_File.close();
	
	}//CreateSftStaffFile

	void CustomFileIO::FindBestWidth
	( DataType ColName, unsigned int SizeOfCurrData )
	{
		bool IsWidthWider = false;

		switch( ColName )
		{
			case DEPT:
				if( SizeOfCurrData > DeptAcronymCoutWidth )
					IsWidthWider = true;					
				break;

			case FULLNAME:
				if( SizeOfCurrData > FullnameCoutWidth )
					IsWidthWider = true;					
				break;

			case USERNAME:
				if( SizeOfCurrData > UsernameCoutWidth )
					IsWidthWider = true;					
				break;

			case EMAIL:
				if( SizeOfCurrData > EmailCoutWidth )
					IsWidthWider = true;					
				break;

			default:
				break;
		
		}//switch

		if( IsWidthWider )
			SetColCoutWidth( ColName, SizeOfCurrData );				
	
	}//FindBestWidth

	void CustomFileIO::SetColCoutWidth( DataType ColName, unsigned int Width )
	{
		switch( ColName )
		{
			case DEPT:
				DeptAcronymCoutWidth = Width;
				break;

			case FULLNAME:
				FullnameCoutWidth = Width;
				break;

			case USERNAME:
				UsernameCoutWidth = Width;
				break;

			case EMAIL:
				EmailCoutWidth = Width;
				break;

			default:
				break;
		
		}//switch
		
	}//SetCoutWidth

	std::string CustomFileIO::ReturnDeptInAcronyms( std::string DeptName )
	{
		std::string::iterator FirstChar, LastChar;
		std::string TempDept;

		//Point LastChar to 1 char before the EOF
		LastChar = DeptName.end() - 1;
		FirstChar = LastChar;		

		while( *FirstChar != '(' )
			--FirstChar;

		//Reached '(', move one step to the alphabet
		++FirstChar;

		return TempDept.assign(FirstChar, LastChar);	
	}//PrintDeptAcronyms

}//SFT