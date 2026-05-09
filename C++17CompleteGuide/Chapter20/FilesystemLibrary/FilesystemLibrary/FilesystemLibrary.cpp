//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <filesystem>
#include <fstream>
#include <type_traits>
#include <format>
//----------------------------------------------------------------------------------------------------------------------
#include "Helpers/MyDebug.h"
#include "Helpers/CString.h"
#include "Helpers/CException.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4804 )
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26478 )
#pragma warning( disable : 26498 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
using namespace std::filesystem;
using namespace std::chrono;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestReadOperations(void)
{
	PrintLineSeparator();

	{
		// !!! CLASS [path] reprezentuje FILESYSTEM PATH.
		path													Path(L"Test");
		bool													IsDirectory=is_directory(Path);

		if (IsDirectory==true)
		{
			wcout << L"PATH [" << Path << L"] is DIRECTORY." << endl;

			directory_iterator									Iterator(Path);

			for(const directory_entry& Entry : Iterator)
			{
				const path&										EntryPath=Entry.path();
				file_status										EntryStatus=status(EntryPath);
				file_type										EntryType=EntryStatus.type();

				if (is_regular_file(EntryPath)==true)
				{
					wcout << L"\tENTRY PATH [" << EntryPath << L"] and IS REGULAR FILE. ENTRY TYPE [" << int(EntryType) << L"]." << endl;
				}
				else
				{
					wcout << L"\tENTRY PATH [" << EntryPath << L"] and IS NOT REGULAR FILE. ENTRY TYPE [" << int(EntryType) << L"]." << endl;
				}
			}
		}
		else
		{
			wcout << L"PATH [" << Path << L"] is NOT DIRECTORY." << endl;
		}
	}

	PrintLineSeparator();

	{
		// !!! CLASS [path] reprezentuje FILESYSTEM PATH.
		path													Path(L"Test");
		bool													IsDirectory=is_directory(Path);

		if (IsDirectory==true)
		{
			// !!! METHOD [wstring path::wstring(void) const] vracia NATIVE PATH.
			wcout << L"PATH [" << Path.wstring() << L"] is DIRECTORY." << endl;

			directory_iterator									Iterator(Path);

			for(const directory_entry& Entry : Iterator)
			{
				const path&										EntryPath=Entry.path();
				file_status										EntryStatus=status(EntryPath);
				file_type										EntryType=EntryStatus.type();

				if (is_regular_file(EntryPath)==true)
				{
					// !!! METHOD [wstring path::wstring(void) const] vracia NATIVE PATH.
					wcout << L"\tENTRY PATH [" << EntryPath.wstring() << L"] and IS REGULAR FILE. ENTRY TYPE [" << int(EntryType) << L"]." << endl;
				}
				else
				{
					// !!! METHOD [wstring path::wstring(void) const] vracia NATIVE PATH.
					wcout << L"\tENTRY PATH [" << EntryPath.wstring() << L"] and IS NOT REGULAR FILE. ENTRY TYPE [" << int(EntryType) << L"]." << endl;
				}
			}
		}
		else
		{
			// !!! METHOD [wstring path::wstring(void) const] vracia NATIVE PATH.
			wcout << L"PATH [" << Path.wstring() << L"] is NOT DIRECTORY." << endl;
		}
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestWriteOperations(void)
{
	PrintLineSeparator();

	try
	{
		path													DirectoryTempTest(L"Temp/MyTest");

		// !!! Vytvoria sa DIRECTORIES.
		bool													DirectoriesCreated=create_directories(DirectoryTempTest);

		if (DirectoriesCreated==true)
		{
			wcout << L"DIRECTORIES CREATED." << endl;
		}
		else
		{
			wcout << L"DIRECTORIES ALREADY EXIST." << endl;
		}

		path													FileData=(DirectoryTempTest/L"MyData.txt");

		{
			// !!! Zapise sa FILE.
			wofstream											FileDataStream{FileData};

			// !!! Konverzia na BOOL vracia informacia ci FILE OPERATION skoncila uspesne.
			if (static_cast<bool>(FileDataStream)==true)
			{
				FileDataStream << L"Hello World !";

				wcout << L"FILE CREATED and WRITTEN." << endl;
			}
			else
			{
				wcout << L"FILE was NOT CREATED and WRITTEN." << endl;
			}
		}

		path													LinkMyLink=(DirectoryTempTest.parent_path()/L"MyLink");

		// !!! Vytvori sa SYMBOLIC LINK.
		// !!! FUNCTION vyzaduje ADMINISTRATOR ACCESS RIGHTS.
		create_directory_symlink("MyTest",LinkMyLink);

		wcout << L"SYMBOLIC LINK CREATED." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		wcout << endl << L"CURRENT PATH [" << current_path().wstring() << L"]." << endl;

		path													DirectoryTemp(L"Temp");
		directory_options										DirectoryOptions=directory_options::follow_directory_symlink;

		for(const directory_entry& Entry : recursive_directory_iterator(DirectoryTemp,DirectoryOptions))
		{
			const path&											EntryPath=Entry.path();

			wcout << L"\tENTRY PATH [" << EntryPath.lexically_normal().wstring() << L"]." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPathNormalization(void)
{
	PrintLineSeparator();

	{
		path													Path(L"foo/.///bar/../");
		path													NormalizedPath=Path.lexically_normal();

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"NORMALIZED PATH [" << NormalizedPath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path(L"//host/../foo.txt");
		path													NormalizedPath=Path.lexically_normal();

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"NORMALIZED PATH [" << NormalizedPath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path(L"./f/../.f/");
		path													NormalizedPath=Path.lexically_normal();

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"NORMALIZED PATH [" << NormalizedPath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path(L"C:bar/../");
		path													NormalizedPath=Path.lexically_normal();

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"NORMALIZED PATH [" << NormalizedPath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path(L"C:/bar/..");
		path													NormalizedPath=Path.lexically_normal();

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"NORMALIZED PATH [" << NormalizedPath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path(L"C:\\bar\\..");
		path													NormalizedPath=Path.lexically_normal();

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"NORMALIZED PATH [" << NormalizedPath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path(L"/./../data.txt");
		path													NormalizedPath=Path.lexically_normal();

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"NORMALIZED PATH [" << NormalizedPath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path(L"././");
		path													NormalizedPath=Path.lexically_normal();

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"NORMALIZED PATH [" << NormalizedPath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestFilesystemErrors(void)
{
	PrintLineSeparator();

	try
	{
		const path&												Path1=L"NotExistingPath1.txt";
		const path&												Path2=L"NotExistingPath2.txt";

		// !!! FUNCTION pri vzniku ERROR hodi EXCEPTION.
		bool													FileCopied=copy_file(Path1,Path2);

		if (FileCopied==true)
		{
			wcout << L"FILE COPIED." << endl;
		}
		else
		{
			wcout << L"FILE NOT COPIED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		const path&												Path1=L"NotExistingPath1.txt";
		const path&												Path2=L"NotExistingPath2.txt";
		error_code												Code;

		// !!! FUNCTION pri vzniku ERROR vrati ERROR VALUE a nehodi EXCEPTION.
		bool													FileCopied=copy_file(Path1,Path2,Code);

		if (FileCopied==true)
		{
			wcout << L"FILE COPIED. CODE [" << Code << L"]." << endl;
		}
		else
		{
			wcout << L"FILE NOT COPIED. CODE [" << Code << L"]." << endl;


			if (Code==errc::no_such_file_or_directory)
			{
				wcout << L"FILE NOT FOUND." << endl;
			}
		}
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestFileTypes(void)
{
	PrintLineSeparator();

	try
	{
		path													DirectoryTemp(L"Test");
		directory_options										DirectoryOptions=directory_options::follow_directory_symlink;

		for(const directory_entry& Entry : recursive_directory_iterator(DirectoryTemp,DirectoryOptions))
		{
			const path&											EntryPath=Entry.path();
			file_status											EntryStatus=Entry.status();
			file_type											EntryFileType=EntryStatus.type();
			wstring												FileTypeString;

			if (EntryFileType==file_type::none)
			{
				FileTypeString=L"NONE";
			}
			else if (EntryFileType==file_type::not_found)
			{
				FileTypeString=L"NOT FOUND";
			}
			else if (EntryFileType==file_type::regular)
			{
				FileTypeString=L"REGULAR";
			}
			else if (EntryFileType==file_type::directory)
			{
				FileTypeString=L"DIRECTORY";
			}
			else if (EntryFileType==file_type::symlink)
			{
				FileTypeString=L"SYMBOLIC LINK";
			}
			else if (EntryFileType==file_type::block)
			{
				FileTypeString=L"BLOCK FILE";
			}
			else if (EntryFileType==file_type::character)
			{
				FileTypeString=L"CHARACTER FILE";
			}
			else if (EntryFileType==file_type::fifo)
			{
				FileTypeString=L"FIFO PIPE FILE";
			}
			else if (EntryFileType==file_type::socket)
			{
				FileTypeString=L"SOCKET FILE";
			}
			else if (EntryFileType==file_type::unknown)
			{
				FileTypeString=L"UNKNOWN";
			}

			wcout << L"ENTRY PATH [" << EntryPath.lexically_normal().wstring() << L"] FILE TYPE [" << FileTypeString << L"]." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCurrentAndTempPaths(void)
{
	PrintLineSeparator();

	// !!! Vracia CURRENT PATH.
	path														CurrentPath1=current_path();

	wcout << L"CURRENT PATH [" << CurrentPath1.wstring() << L"]." << endl;

	PrintLineSeparator();

	path														NewCurrentPath=L"Test";

	current_path(NewCurrentPath);

	wcout << L"NEW CURRENT PATH SET." << endl;

	PrintLineSeparator();

	// !!! Vracia CURRENT PATH.
	path														CurrentPath2=current_path();

	wcout << L"CURRENT PATH [" << CurrentPath2.wstring() << L"]." << endl;

	PrintLineSeparator();

	// !!! Vracia TEMPORARY DIRECTORY.
	path														TemporaryDirectory=temp_directory_path();

	wcout << L"TEMPORARY DIRECTORY [" << TemporaryDirectory.wstring() << L"]." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void PrintPathProperties(const path& Path)
{
	wcout << L"PATH [" << Path.wstring() << L"]." << endl;

	wcout << endl;

	wcout << L"EMPTY [" << Path.empty() << L"]." << endl;
	wcout << L"IS ABSOLUTE [" << Path.is_absolute() << L"]." << endl;
	wcout << L"IS RELATIVE [" << Path.is_relative() << L"]." << endl;
	wcout << L"HAS FILENAME [" << Path.has_filename() << L"]." << endl;
	wcout << L"HAS STEM [" << Path.has_stem() << L"]." << endl;
	wcout << L"HAS EXTENSION [" << Path.has_extension() << L"]." << endl;
	wcout << L"HAS ROOT NAME [" << Path.has_root_name() << L"]." << endl;
	wcout << L"HAS ROOT DIRECTORY [" << Path.has_root_directory() << L"]." << endl;
	wcout << L"HAS ROOT PATH [" << Path.has_root_path() << L"]." << endl;
	wcout << L"HAS PARENT PATH [" << Path.has_parent_path() << L"]." << endl;
	wcout << L"HAS RELATIVE PATH [" << Path.has_relative_path() << L"]." << endl;

	wcout << endl;

	wcout << L"FILENAME [" << Path.filename().wstring() << L"]." << endl;
	wcout << L"STEM [" << Path.stem().wstring() << L"]." << endl;
	wcout << L"EXTENSION [" << Path.extension().wstring() << L"]." << endl;
	wcout << L"ROOT NAME [" << Path.root_name().wstring() << L"]." << endl;
	wcout << L"ROOT DIRECTORY [" << Path.root_directory().wstring() << L"]." << endl;
	wcout << L"ROOT PATH [" << Path.root_path().wstring() << L"]." << endl;
	wcout << L"PARENT PATH [" << Path.parent_path().wstring() << L"]." << endl;
	wcout << L"RELATIVE PATH [" << Path.relative_path().wstring() << L"]." << endl;

	wcout << endl;

	wcout << L"PATH ELEMENTS:" << endl;

	// !!! ITERATOR umoznuje iterovat jednotlivymi PATH ELEMENTS.
	for(path::iterator Iterator=Path.begin();Iterator!=Path.end();++Iterator)
	{
		path													Element=*Iterator;

		wcout << L"\tELEMENT [" << Element.wstring() << L"]." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPathProperties(void)
{
	PrintLineSeparator();

	{
		// !!! ABSOLUTE PATH.
		path													Path=current_path();

		PrintPathProperties(Path);
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path=L"Directory1/Directory2/File.txt";

		PrintPathProperties(Path);
	}

	PrintLineSeparator();

	{
		path													Path=L"C:";

		PrintPathProperties(Path);
	}

	PrintLineSeparator();

	{
		path													Path=L".";

		PrintPathProperties(Path);
	}

	PrintLineSeparator();

	{
		path													Path=L"..";

		PrintPathProperties(Path);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void PathIteration(const path& Path)
{
	wcout << L"ITERATION BEGIN-END:" << endl;

	for(path::iterator Iterator=Path.begin();Iterator!=Path.end();++Iterator)
	{
		path													Element=*Iterator;

		wcout << L"\tELEMENT [" << Element.wstring() << L"]." << endl;
	}

	wcout << L"ITERATION FOR:" << endl;

	for(path Element : Path)
	{
		wcout << L"\tELEMENT [" << Element.wstring() << L"]." << endl;
	}

	wcout << L"ITERATION END-BEGIN:" << endl;

	{
		path::iterator											ReverseIterator=Path.end();

		while(ReverseIterator!=Path.begin())
		{
			path												Element=*(--ReverseIterator);

			wcout << L"\tELEMENT [" << Element.wstring() << L"]." << endl;
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestPathIteration(void)
{
	PrintLineSeparator();

	{
		// !!! ABSOLUTE PATH.
		path													Path=current_path();

		PathIteration(Path);
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path=L"Directory1/Directory2/File.txt";

		PathIteration(Path);
	}

	PrintLineSeparator();

	{
		// !!! EMPTY PATH.
		path													Path;

		PathIteration(Path);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPathInputOutputOperators(void)
{
	PrintLineSeparator();

	{
		path													Path=L"Directory1/Directory2/File.txt";
		wstringstream											Stream{};

		// !!! Zapise sa PATH ako QUOTED STRING.
		Stream << Path;

		wcout << L"STREAM [" << Stream.str() << L"]." << endl;

		// !!! PATH sa cita ako QUOTED STRING.
		path													PathFromStream;

		Stream >> PathFromStream;
		
		wcout << L"PATH [" << PathFromStream.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path=L"Directory1/Directory2/File.txt";
		wstringstream											Stream{};

		// !!! Zapise sa PATH ako RAW STRING.
		Stream << Path.wstring();

		wcout << L"STREAM [" << Stream.str() << L"]." << endl;

		path													PathFromStream;

		// !!! PATH sa cita ako RAW STRING.
		Stream >> PathFromStream;
		
		wcout << L"PATH [" << PathFromStream.wstring() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPathRelativePaths(void)
{
	PrintLineSeparator();

	{
		path													Path1(L"/a/d");
		path													Path2(L"/a/b/c");
		path													RelativePath=Path1.lexically_relative(Path2);
		path													ProximatePath=Path1.lexically_proximate(Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"RELATIVE PATH [" << RelativePath.wstring() << L"]." << endl;
		wcout << L"PROXIMATE PATH [" << ProximatePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"/a/b/c");
		path													Path2(L"/a/d");
		path													RelativePath=Path1.lexically_relative(Path2);
		path													ProximatePath=Path1.lexically_proximate(Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"RELATIVE PATH [" << RelativePath.wstring() << L"]." << endl;
		wcout << L"PROXIMATE PATH [" << ProximatePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"/a/b");
		path													Path2(L"/a/b");
		path													RelativePath=Path1.lexically_relative(Path2);
		path													ProximatePath=Path1.lexically_proximate(Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"RELATIVE PATH [" << RelativePath.wstring() << L"]." << endl;
		wcout << L"PROXIMATE PATH [" << ProximatePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"/a/b");
		path													Path2(L"/a/b/");
		path													RelativePath=Path1.lexically_relative(Path2);
		path													ProximatePath=Path1.lexically_proximate(Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"RELATIVE PATH [" << RelativePath.wstring() << L"]." << endl;
		wcout << L"PROXIMATE PATH [" << ProximatePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"/a/b");
		path													Path2(L"/a/b\\");
		path													RelativePath=Path1.lexically_relative(Path2);
		path													ProximatePath=Path1.lexically_proximate(Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"RELATIVE PATH [" << RelativePath.wstring() << L"]." << endl;
		wcout << L"PROXIMATE PATH [" << ProximatePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"/a/b");
		path													Path2(L"/a/d/../c");
		path													RelativePath=Path1.lexically_relative(Path2);
		path													ProximatePath=Path1.lexically_proximate(Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"RELATIVE PATH [" << RelativePath.wstring() << L"]." << endl;
		wcout << L"PROXIMATE PATH [" << ProximatePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"a/d/../b");
		path													Path2(L"a/c");
		path													RelativePath=Path1.lexically_relative(Path2);
		path													ProximatePath=Path1.lexically_proximate(Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"RELATIVE PATH [" << RelativePath.wstring() << L"]." << endl;
		wcout << L"PROXIMATE PATH [" << ProximatePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"a//d/..//b");
		path													Path2(L"a/c");
		path													RelativePath=Path1.lexically_relative(Path2);
		path													ProximatePath=Path1.lexically_proximate(Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"RELATIVE PATH [" << RelativePath.wstring() << L"]." << endl;
		wcout << L"PROXIMATE PATH [" << ProximatePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"C:/a/b");
		path													Path2(L"c:/c/d");
		path													RelativePath=Path1.lexically_relative(Path2);
		path													ProximatePath=Path1.lexically_proximate(Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"RELATIVE PATH [" << RelativePath.wstring() << L"]." << endl;
		wcout << L"PROXIMATE PATH [" << ProximatePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"C:/a/b");
		path													Path2(L"D:/c/d");
		path													RelativePath=Path1.lexically_relative(Path2);
		path													ProximatePath=Path1.lexically_proximate(Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"RELATIVE PATH [" << RelativePath.wstring() << L"]." << endl;
		wcout << L"PROXIMATE PATH [" << ProximatePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"C:/a/b");
		path													Path2(L"D:/c/d");
		path													RelativePath=Path1.lexically_relative(Path2);
		path													ProximatePath=Path1.lexically_proximate(Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"RELATIVE PATH [" << RelativePath.wstring() << L"]." << endl;
		wcout << L"PROXIMATE PATH [" << ProximatePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPathStringConversions(void)
{
	PrintLineSeparator();

	path														Path=L"Directory1/Directory2/File.txt";

	wcout << L"PATH [" << Path.wstring() << L"]." << endl;

	string														String=Path.string();
	size_t														StringSize=sizeof(decltype(*String.cbegin()))*String.size();

	wcout << L"STRING SIZE [" << StringSize << L"]." << endl;

	wstring														WString=Path.wstring();
	size_t														WStringSize=sizeof(decltype(*WString.cbegin()))*WString.size();

	wcout << L"WSTRING SIZE [" << WStringSize << L"]." << endl;

	u8string													U8String=Path.u8string();
	size_t														U8StringSize=sizeof(decltype(*U8String.cbegin()))*U8String.size();

	wcout << L"U8STRING SIZE [" << U8StringSize << L"]." << endl;

	u16string													U16String=Path.u16string();
	size_t														U16StringSize=sizeof(decltype(*U16String.cbegin()))*U16String.size();

	wcout << L"U16STRING SIZE [" << U16StringSize << L"]." << endl;

	u32string													U32String=Path.u32string();
	size_t														U32StringSize=sizeof(decltype(*U32String.cbegin()))*U32String.size();

	wcout << L"U32STRING SIZE [" << U32StringSize << L"]." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void PrintNativePath(const TType& Value)
{
	if constexpr (is_same<path::string_type,wstring>::value==true)
	{
		wcout << L"PATH NATIVE (WSTRING) [" << Value << L"]." << endl;
	}
	else if constexpr (is_same<path::string_type,string>::value==true)
	{
		wstring												PathNative=ConvertStringToWideString(Value);

		wcout << L"PATH NATIVE (STRING) [" << PathNative << L"]." << endl;
	}
	else
	{
		wcout << L"UNSUPPORTED STRING TYPE." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void PrintCStrPath(const TType* Value)
{
	if constexpr (is_same<path::value_type,wchar_t>::value==true)
	{
		wcout << L"PATH NATIVE (wchar_t) [" << Value << L"]." << endl;
	}
	else if constexpr (is_same<path::value_type,char>::value==true)
	{
		wstring												PathNative=ConvertStringToWideString(Value);

		wcout << L"PATH NATIVE (char) [" << PathNative << L"]." << endl;
	}
	else
	{
		wcout << L"UNSUPPORTED STRING TYPE." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestPathNativeGenericFormats(void)
{
	PrintLineSeparator();

	{
		path													Path(L"/dir\\subdir/subsubdir\\/./\\");
		wstring													PathGenericWString=Path.generic_wstring();

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"PATH GENERIC WSTRING [" << PathGenericWString << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path(L"/dir\\subdir/subsubdir\\/./\\");
		path::string_type										RawPathNative=Path.native();

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;

		PrintNativePath(RawPathNative);
	}

	PrintLineSeparator();

	{
		path													Path(L"/dir\\subdir/subsubdir\\/./\\");
		const path::value_type*									RawPathCStr=Path.c_str();

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;

		PrintCStrPath(RawPathCStr);
	}

	PrintLineSeparator();

	{
		path													Path(L"/dir\\subdir/subsubdir\\/./\\");

		wcout << L"PATH BEFORE [" << Path.wstring() << L"]." << endl;

		// !!! METHOD modifikuje PATH.
		Path.make_preferred();

		wcout << L"PATH AFTER [" << Path.wstring() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPathOperatorSlash(void)
{
	PrintLineSeparator();

	{
		path													Path1(L"Directory1");
		path													Path2(L"Directory2");
		path													PathResult=(Path1 / Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << PathResult.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Ak SOURCE PATH obsahuje DIRECTORY SEPARATOR, tak novy nie je pridany.
		path													Path1(L"Directory1/");
		path													Path2(L"Directory2");
		path													PathResult=(Path1 / Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << PathResult.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory1");
		// !!! Toto je ABSOLUTE PATH, ktora nahradi povodnu PATH.
		path													Path2(L"/Directory2");
		path													PathResult=(Path1 / Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << PathResult.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory1");
		// !!! Toto je vo WINDOWS ABSOLUTE PATH, ktora nahradi povodnu PATH. V LINUX je to RELATIVE PATH.
		path													Path2(L"\\Directory2");
		path													PathResult=(Path1 / Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << PathResult.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory1");
		// !!! ABSOLUTE PATH vo WINDOWS nahradi povodnu PATH.
		path													Path2(L"C:/Directory2");
		path													PathResult=(Path1 / Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << PathResult.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory1");
		// !!! ABSOLUTE PATH vo WINDOWS nahradi povodnu PATH.
		path													Path2(L"C:");
		path													PathResult=(Path1 / Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << PathResult.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! ABSOLUTE PATH vo WINDOWS.
		path													Path1(L"C:");
		path													Path2(L"");
		path													PathResult=(Path1 / Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << PathResult.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! ROOT ELEMENT s RELATIVE PATH vo WINDOWS.
		path													Path1(L"C:Directory1");
		// !!! ABSOLUTE PATH vo WINDOWS, ktora nahradi povodnu PATH.
		path													Path2(L"/Directory2");
		// !!!!! ROOT ELEMENT je PONECHANY, ale RELATIVE PATH je nahradena ABSOLUTE PATH.
		path													PathResult=(Path1 / Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << PathResult.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! ROOT ELEMENT s RELATIVE PATH vo WINDOWS.
		path													Path1(L"C:Directory1");
		// !!! ROOT ELEMENT s RELATIVE PATH vo WINDOWS.
		path													Path2(L"C:Directory2");
		// !!!!! ROOT ELEMENT je PONECHANY, a nova RELATIVE PATH je pridana na koniec povodnej RELATIVE PATH.
		path													PathResult=(Path1 / Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << PathResult.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! ROOT ELEMENT s RELATIVE PATH vo WINDOWS.
		path													Path1(L"C:Directory1");
		// !!! ROOT ELEMENT s RELATIVE PATH vo WINDOWS.
		path													Path2(L"D:Directory2");
		// !!!!! Kedze ROOT ELEMENT sa lisi, nova PATH nahradi povodnu PATH.
		path													PathResult=(Path1 / Path2);

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << PathResult.wstring() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPathOperatorSlashEqual(void)
{
	PrintLineSeparator();

	{
		path													Path1(L"Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		path													Path2(L"Directory2");

		(Path1 /= Path2);

		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Ak SOURCE PATH obsahuje DIRECTORY SEPARATOR, tak novy nie je pridany.
		path													Path1(L"Directory1/");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		path													Path2(L"Directory2");

		(Path1 /= Path2);

		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		// !!! Toto je ABSOLUTE PATH, ktora nahradi povodnu PATH.
		path													Path2(L"/Directory2");

		(Path1 /= Path2);

		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		// !!! Toto je vo WINDOWS ABSOLUTE PATH, ktora nahradi povodnu PATH. V LINUX je to RELATIVE PATH.
		path													Path2(L"\\Directory2");

		(Path1 /= Path2);

		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		// !!! ABSOLUTE PATH vo WINDOWS nahradi povodnu PATH.
		path													Path2(L"C:/Directory2");

		(Path1 /= Path2);

		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		// !!! ABSOLUTE PATH vo WINDOWS nahradi povodnu PATH.
		path													Path2(L"C:");

		(Path1 /= Path2);

		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! ABSOLUTE PATH vo WINDOWS.
		path													Path1(L"C:");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		path													Path2(L"");

		(Path1 /= Path2);

		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! ROOT ELEMENT s RELATIVE PATH vo WINDOWS.
		path													Path1(L"C:Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		// !!! ABSOLUTE PATH vo WINDOWS, ktora nahradi povodnu PATH.
		path													Path2(L"/Directory2");

		// !!!!! ROOT ELEMENT je PONECHANY, ale RELATIVE PATH je nahradena ABSOLUTE PATH.
		(Path1 /= Path2);

		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! ROOT ELEMENT s RELATIVE PATH vo WINDOWS.
		path													Path1(L"C:Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		// !!! ROOT ELEMENT s RELATIVE PATH vo WINDOWS.
		path													Path2(L"C:Directory2");

		// !!!!! ROOT ELEMENT je PONECHANY, a nova RELATIVE PATH je pridana na koniec povodnej RELATIVE PATH.
		(Path1 /= Path2);

		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! ROOT ELEMENT s RELATIVE PATH vo WINDOWS.
		path													Path1(L"C:Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		// !!! ROOT ELEMENT s RELATIVE PATH vo WINDOWS.
		path													Path2(L"D:Directory2");

		// !!!!! Kedze ROOT ELEMENT sa lisi, nova PATH nahradi povodnu PATH.
		(Path1 /= Path2);

		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPathAppend(void)
{
	PrintLineSeparator();

	{
		path													Path1(L"Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		wstring													Path2(L"Directory2");

		Path1.append(Path2);

		wcout << L"PATH 2 [" << Path2 << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Ak SOURCE PATH obsahuje DIRECTORY SEPARATOR, tak novy nie je pridany.
		path													Path1(L"Directory1/");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		wstring													Path2(L"Directory2");

		Path1.append(Path2);

		wcout << L"PATH 2 [" << Path2 << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		// !!! Toto je ABSOLUTE PATH, ktora nahradi povodnu PATH.
		wstring													Path2(L"/Directory2");

		Path1.append(Path2);

		wcout << L"PATH 2 [" << Path2 << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		// !!! Toto je vo WINDOWS ABSOLUTE PATH, ktora nahradi povodnu PATH. V LINUX je to RELATIVE PATH.
		wstring													Path2(L"\\Directory2");

		Path1.append(Path2);

		wcout << L"PATH 2 [" << Path2 << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		// !!! ABSOLUTE PATH vo WINDOWS nahradi povodnu PATH.
		wstring													Path2(L"C:/Directory2");

		Path1.append(Path2);

		wcout << L"PATH 2 [" << Path2 << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		// !!! ABSOLUTE PATH vo WINDOWS nahradi povodnu PATH.
		wstring													Path2(L"C:");

		Path1.append(Path2);

		wcout << L"PATH 2 [" << Path2 << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! ABSOLUTE PATH vo WINDOWS.
		path													Path1(L"C:");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		wstring													Path2(L"");

		Path1.append(Path2);

		wcout << L"PATH 2 [" << Path2 << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! ROOT ELEMENT s RELATIVE PATH vo WINDOWS.
		path													Path1(L"C:Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		// !!! ABSOLUTE PATH vo WINDOWS, ktora nahradi povodnu PATH.
		wstring													Path2(L"/Directory2");

		// !!!!! ROOT ELEMENT je PONECHANY, ale RELATIVE PATH je nahradena ABSOLUTE PATH.
		Path1.append(Path2);

		wcout << L"PATH 2 [" << Path2 << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! ROOT ELEMENT s RELATIVE PATH vo WINDOWS.
		path													Path1(L"C:Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		// !!! ROOT ELEMENT s RELATIVE PATH vo WINDOWS.
		wstring													Path2(L"C:Directory2");

		// !!!!! ROOT ELEMENT je PONECHANY, a nova RELATIVE PATH je pridana na koniec povodnej RELATIVE PATH.
		Path1.append(Path2);

		wcout << L"PATH 2 [" << Path2 << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! ROOT ELEMENT s RELATIVE PATH vo WINDOWS.
		path													Path1(L"C:Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		// !!! ROOT ELEMENT s RELATIVE PATH vo WINDOWS.
		wstring													Path2(L"D:Directory2");

		// !!!!! Kedze ROOT ELEMENT sa lisi, nova PATH nahradi povodnu PATH.
		Path1.append(Path2);

		wcout << L"PATH 2 [" << Path2 << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPathOperatorPlusEqualAndConcat(void)
{
	PrintLineSeparator();

	{
		path													Path1(L"Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		wstring													Path2(L"Directory2");

		// !!! Medzi obe PATHS sa NEPRIDAVA DIRECTORY SEPARATOR.
		Path1+=Path2;

		wcout << L"PATH 2 [" << Path2 << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		wstring													Path2(L"/Directory2");

		// !!! Medzi obe PATHS sa NEPRIDAVA DIRECTORY SEPARATOR.
		Path1+=Path2;

		wcout << L"PATH 2 [" << Path2 << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		wstring													Path2(L"Directory2");

		// !!! Medzi obe PATHS sa NEPRIDAVA DIRECTORY SEPARATOR.
		Path1.concat(Path2);

		wcout << L"PATH 2 [" << Path2 << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		wstring													Path2(L"/Directory2");

		// !!! Medzi obe PATHS sa NEPRIDAVA DIRECTORY SEPARATOR.
		Path1.concat(Path2);

		wcout << L"PATH 2 [" << Path2 << L"]." << endl;
		wcout << L"PATH RESULT [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPathOperatorEqualAndAssignAndSwapAndClear(void)
{
	PrintLineSeparator();

	{
		path													Path1(L"Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		wstring													Path2(L"Directory2");

		Path1=Path2;

		wcout << L"PATH 2 [" << Path2 << L"]." << endl;
		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		wstring													Path2(L"Directory2");

		Path1.assign(Path2);

		wcout << L"PATH 2 [" << Path2 << L"]." << endl;
		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory1");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		path													Path2(L"Directory2");

		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;

		Path1.swap(Path2);

		wcout << L"PATH 1 AFTER SWAP [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 AFTER SWAP [" << Path2.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path(L"Directory/File.txt");

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;

		Path.clear();

		wcout << L"PATH AFTER CLEAR [" << Path.wstring() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPathRemoveFilenameReplaceFilename(void)
{
	PrintLineSeparator();

	{
		path													Path(L"/Directory1/Directory2/Directory3/File.txt");

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;

		// !!! Odstrani posledny FILENAME.
		Path.remove_filename();

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path(L"/Directory1/Directory2/Directory3");

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;

		// !!! Odstrani posledny FILENAME.
		Path.remove_filename();

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path(L"/Directory1/Directory2/Directory3/File.txt");

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;

		// !!! Nahradi FILENAME.
		Path.replace_filename("NewFile.!!!");

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path(L"/Directory1/Directory2/Directory3");

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;

		// !!! Nahradi FILENAME.
		Path.replace_filename("NewFile.!!!");

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPathReplaceExtension(void)
{
	PrintLineSeparator();

	{
		path													Path(L"/Directory1/Directory2/Directory3/File.txt");

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;

		// !!! Odstrani existujucu EXTENSION.
		Path.replace_extension();

		wcout << L"PATH AFTER REPLACE EXTENSION [" << Path.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"/Directory1/Directory2/Directory3/File.txt");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		path													Path2(L"!!!");

		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;

		// !!! Nahradi existujucu EXTENSION.
		Path1.replace_extension(Path2);

		wcout << L"PATH AFTER REPLACE EXTENSION [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"/Directory1/Directory2/Directory3/File.txt");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		path													Path2(L".!!!");

		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;

		// !!! Nahradi existujucu EXTENSION.
		Path1.replace_extension(Path2);

		wcout << L"PATH AFTER REPLACE EXTENSION [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"/Directory1/Directory2/Directory3/File");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		path													Path2(L".!!!");

		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;

		// !!! Prida EXTENSION.
		Path1.replace_extension(Path2);

		wcout << L"PATH AFTER REPLACE EXTENSION [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"/Directory1/Directory2/Directory3/File.");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		path													Path2(L".!!!");

		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;

		// !!! Prida EXTENSION.
		Path1.replace_extension(Path2);

		wcout << L"PATH AFTER REPLACE EXTENSION [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path1(L"/Directory1/Directory2/Directory3/");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;

		path													Path2(L"!!!");

		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;

		// !!! Prida EXTENSION.
		Path1.replace_extension(Path2);

		wcout << L"PATH AFTER REPLACE EXTENSION [" << Path1.wstring() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void DoCompare(const path& Path1, const path& Path2)
{
	wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
	wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;
	
	wcout << endl;

	wcout << L"OPERATOR== [" << (Path1==Path2) << L"]." << endl;
	wcout << L"OPERATOR!= [" << (Path1!=Path2) << L"]." << endl;
	wcout << L"OPERATOR< [" << (Path1<Path2) << L"]." << endl;
	wcout << L"OPERATOR<= [" << (Path1<=Path2) << L"]." << endl;
	wcout << L"OPERATOR> [" << (Path1>Path2) << L"]." << endl;
	wcout << L"OPERATOR>= [" << (Path1>=Path2) << L"]." << endl;
	wcout << L"COMPARE [" << (Path1.compare(Path2)) << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestPathComparisons(void)
{
	PrintLineSeparator();

	{
		path													Path1(L"Directory/File.txt");
		path													Path2(L"/Directory//File.txt");

		// !!! PATHS sa LISIA.
		DoCompare(Path1,Path2);
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory/File.txt");
		path													Path2(L"Directory//File.txt");

		// !!! PATHS su ZHODNE.
		DoCompare(Path1,Path2);
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory/File.txt");
		path													Path2(L"Directory/\\/File.txt");

		// !!! PATHS su ZHODNE, ale iba na WINDOWS.
		DoCompare(Path1,Path2);
	}

	PrintLineSeparator();

	{
		path													Path1(L"Directory/File.txt");
		path													Path2(L"Directory/./File.txt");

		// !!! PATHS sa LISIA, aj ked logicky su zhodne.
		DoCompare(Path1,Path2);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPathEquivalent(void)
{
	PrintLineSeparator();

	{
		// !!!!! FILES MUSIA EXISTOVAT.
		path													Path1(L"Test/File1.txt");
		path													Path2(L"Test/File1.txt");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;

		wcout << L"EQUIVALENT [" << equivalent(Path1,Path2) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! FILES MUSIA EXISTOVAT.
		path													Path1(L"Test/File1.txt");
		path													Path2(L"Test/File2.txt");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;

		wcout << L"EQUIVALENT [" << equivalent(Path1,Path2) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! FILES MUSIA EXISTOVAT.
		path													Path1(L"Test/File1.txt");
		path													Path2(L"Test/./File1.txt");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;

		wcout << L"EQUIVALENT [" << equivalent(Path1,Path2) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! FILES MUSIA EXISTOVAT.
		path													Path1(L"Test/File1.txt");
		path													Path2(L"Test/../Test/File1.txt");

		wcout << L"PATH 1 [" << Path1.wstring() << L"]." << endl;
		wcout << L"PATH 2 [" << Path2.wstring() << L"]." << endl;

		wcout << L"EQUIVALENT [" << equivalent(Path1,Path2) << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPathHashValue(void)
{
	PrintLineSeparator();

	{
		path													Path(L"Directory1/Directory2/File.txt");
		size_t													Hash=hash_value(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"HASH [" << Hash << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path(L"Directory1//Directory2/File.txt");

		// !!! VALUE je ROVNAKA ako HASH VALUE pre PATH [Directory1/Directory2/File.txt].
		size_t													Hash=hash_value(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"HASH [" << Hash << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path(L"Directory1/./Directory2/File.txt");

		// !!! VALUE je ROZDIELNA ako HASH VALUE pre PATH [Directory1/Directory2/File.txt].
		size_t													Hash=hash_value(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"HASH [" << Hash << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CheckFileAttributes(const path& Path)
{
	if (exists(Path)==true)
	{
		wcout << L"PATH [" << Path.wstring() << L"] EXISTS." << endl;

		wcout << L"IS REGULAR FILE [" << is_regular_file(Path) << L"]." << endl;
		wcout << L"IS DIRECTORY [" << is_directory(Path) << L"]." << endl;
		wcout << L"IS OTHER [" << is_other(Path) << L"]." << endl;
		wcout << L"IS SYMBOLIC LINK [" << is_symlink(Path) << L"]." << endl;
		wcout << L"IS BLOCK FILE [" << is_block_file(Path) << L"]." << endl;
		wcout << L"IS CHARACTER FILE [" << is_character_file(Path) << L"]." << endl;
		wcout << L"IS FIFO [" << is_fifo(Path) << L"]." << endl;
		wcout << L"IS SOCKET [" << is_socket(Path) << L"]." << endl;
	}
	else
	{
		wcout << L"PATH [" << Path.wstring() << L"] doesn't EXIST." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestFileAttributes(void)
{
	PrintLineSeparator();

	{
		path													Path(L"FileNotExists.txt");

		CheckFileAttributes(Path);
	}

	PrintLineSeparator();

	{
		path													Path(L"Test");

		CheckFileAttributes(Path);
	}

	PrintLineSeparator();

	{
		path													Path(L"Test/SubDirectory");

		CheckFileAttributes(Path);
	}

	PrintLineSeparator();

	{
		path													Path(L"Test/File1.txt");

		CheckFileAttributes(Path);
	}

	PrintLineSeparator();

	{
		path													Path(L"Test/File2.txt");

		CheckFileAttributes(Path);
	}

	PrintLineSeparator();

	{
		path													Path(L"Test/SubDirectory/SomeFile.txt");

		CheckFileAttributes(Path);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template <typename TTimePoint>
time_t TimePointToTime(TTimePoint TimePoint)
{
	system_clock::time_point									CurrentSystemTime=system_clock::now();
	typename TTimePoint::clock::time_point						CurrentTimePointTime=TTimePoint::clock::now();
    time_point<system_clock,system_clock::duration>				ConvertedTime=time_point_cast<system_clock::duration>(TimePoint-CurrentTimePointTime+CurrentSystemTime);
	time_t														Time=system_clock::to_time_t(ConvertedTime);

    return(Time);
}
//----------------------------------------------------------------------------------------------------------------------
void TestFileOtherAttributes(void)
{
	PrintLineSeparator();

	{
		path													Path(L"Test/SubDirectory/SomeFile.txt");

		wcout << L"PATH [" << Path.wstring() << L"] EXISTS [" << exists(Path) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path(L"Test/SubDirectory/SomeFile.!!!");

		wcout << L"PATH [" << Path.wstring() << L"] EXISTS [" << exists(Path) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path(L"Test/SubDirectory/SomeFile.txt");

		wcout << L"PATH [" << Path.wstring() << L"] FILE SIZE [" << file_size(Path) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path(L"Test/SubDirectory/SomeFile.txt");

		wcout << L"PATH [" << Path.wstring() << L"] HARD LINKS COUNT [" << hard_link_count(Path) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Path(L"Test/SubDirectory/SomeFile.txt");
		file_time_type											FileTime=last_write_time(Path);
		time_t													Time=TimePointToTime(FileTime);

		wcout << L"PATH [" << Path.wstring() << L"] FILE TIME [" << Time << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CheckFileAttributesFromStatus(const path& Path, const file_status& FileStatus)
{
	if (exists(FileStatus)==true)
	{
		wcout << L"PATH [" << Path.wstring() << L"] EXISTS." << endl;

		// !!!!! FUNCTIONS NEPRISTUPUJU k FILE SYSTEM volanim SYSTEM CALLS.
		wcout << L"FILE TYPE [" << int(FileStatus.type()) << L"]." << endl;
		wcout << L"FILE PERMISSIONS [" << int(FileStatus.permissions()) << L"]." << endl;

		// !!!!! FUNCTIONS NEPRISTUPUJU k FILE SYSTEM volanim SYSTEM CALLS.
		wcout << L"IS REGULAR FILE [" << is_regular_file(FileStatus) << L"]." << endl;
		wcout << L"IS DIRECTORY [" << is_directory(FileStatus) << L"]." << endl;
		wcout << L"IS OTHER [" << is_other(FileStatus) << L"]." << endl;
		wcout << L"IS SYMBOLIC LINK [" << is_symlink(FileStatus) << L"]." << endl;
		wcout << L"IS BLOCK FILE [" << is_block_file(FileStatus) << L"]." << endl;
		wcout << L"IS CHARACTER FILE [" << is_character_file(FileStatus) << L"]." << endl;
		wcout << L"IS FIFO [" << is_fifo(FileStatus) << L"]." << endl;
		wcout << L"IS SOCKET [" << is_socket(FileStatus) << L"]." << endl;
		wcout << L"KNOWN [" << status_known(FileStatus) << L"]." << endl;
	}
	else
	{
		wcout << L"PATH [" << Path.wstring() << L"] doesn't EXIST." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestFileStatus(void)
{
	PrintLineSeparator();

	{
		path													Path(L"Test");
		file_status												FileStatus=status(Path);

		CheckFileAttributesFromStatus(Path,FileStatus);
	}

	PrintLineSeparator();

	{
		path													Path(L"Test/SubDirectory");
		file_status												FileStatus=status(Path);

		CheckFileAttributesFromStatus(Path,FileStatus);
	}

	PrintLineSeparator();

	{
		path													Path(L"Test/File1.txt");
		file_status												FileStatus=status(Path);

		CheckFileAttributesFromStatus(Path,FileStatus);
	}

	PrintLineSeparator();

	{
		path													Path(L"Test/File2.txt");
		file_status												FileStatus=status(Path);

		CheckFileAttributesFromStatus(Path,FileStatus);
	}

	PrintLineSeparator();

	{
		path													Path(L"Test/SubDirectory/SomeFile.txt");
		file_status												FileStatus=status(Path);

		CheckFileAttributesFromStatus(Path,FileStatus);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CheckFilePermissions(const path& Path, const file_status& FileStatus, const perms& Permissions)
{
	if (exists(FileStatus)==true)
	{
		wcout << L"PATH [" << Path.wstring() << L"] EXISTS." << endl;

		wcout << L"HAS PERMISSION [none] VALUE [" << (Permissions==perms::none) << L"]." << endl;
		wcout << L"HAS PERMISSION [unknown] VALUE [" << (Permissions==perms::unknown) << L"]." << endl;
		wcout << L"HAS PERMISSION [all] VALUE [" << (Permissions==perms::all) << L"]." << endl;
		wcout << L"HAS PERMISSION [owner_read] VALUE [" << bool(Permissions & perms::owner_read) << L"]." << endl;
		wcout << L"HAS PERMISSION [owner_write] VALUE [" << bool(Permissions & perms::owner_write) << L"]." << endl;
		wcout << L"HAS PERMISSION [owner_exec] VALUE [" << bool(Permissions & perms::owner_exec) << L"]." << endl;
		wcout << L"HAS PERMISSION [owner_all] VALUE [" << bool(Permissions & perms::owner_all) << L"]." << endl;
		wcout << L"HAS PERMISSION [group_read] VALUE [" << bool(Permissions & perms::group_read) << L"]." << endl;
		wcout << L"HAS PERMISSION [group_write] VALUE [" << bool(Permissions & perms::group_write) << L"]." << endl;
		wcout << L"HAS PERMISSION [group_exec] VALUE [" << bool(Permissions & perms::group_exec) << L"]." << endl;
		wcout << L"HAS PERMISSION [group_all] VALUE [" << bool(Permissions & perms::group_all) << L"]." << endl;
		wcout << L"HAS PERMISSION [others_read] VALUE [" << bool(Permissions & perms::others_read) << L"]." << endl;
		wcout << L"HAS PERMISSION [others_write] VALUE [" << bool(Permissions & perms::others_write) << L"]." << endl;
		wcout << L"HAS PERMISSION [others_exec] VALUE [" << bool(Permissions & perms::others_exec) << L"]." << endl;
		wcout << L"HAS PERMISSION [others_all] VALUE [" << bool(Permissions & perms::others_all) << L"]." << endl;
		wcout << L"HAS PERMISSION [set_uid] VALUE [" << bool(Permissions & perms::set_uid) << L"]." << endl;
		wcout << L"HAS PERMISSION [set_gid] VALUE [" << bool(Permissions & perms::set_gid) << L"]." << endl;
		wcout << L"HAS PERMISSION [sticky_bit] VALUE [" << bool(Permissions & perms::sticky_bit) << L"]." << endl;
	}
	else
	{
		wcout << L"PATH [" << Path.wstring() << L"] doesn't EXIST." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestFilePermissions(void)
{
	PrintLineSeparator();

	{
		path													Path(L"Test");
		file_status												FileStatus=status(Path);
		perms													Permissions=FileStatus.permissions();

		CheckFilePermissions(Path,FileStatus,Permissions);
	}

	PrintLineSeparator();

	{
		path													Path(L"Test/SubDirectory");
		file_status												FileStatus=status(Path);
		perms													Permissions=FileStatus.permissions();

		CheckFilePermissions(Path,FileStatus,Permissions);
	}

	PrintLineSeparator();

	{
		path													Path(L"Test/File1.txt");
		file_status												FileStatus=status(Path);
		perms													Permissions=FileStatus.permissions();

		CheckFilePermissions(Path,FileStatus,Permissions);
	}

	PrintLineSeparator();

	{
		path													Path(L"Test/File2.txt");
		file_status												FileStatus=status(Path);
		perms													Permissions=FileStatus.permissions();

		CheckFilePermissions(Path,FileStatus,Permissions);
	}

	PrintLineSeparator();

	{
		path													Path(L"Test/SubDirectory/SomeFile.txt");
		file_status												FileStatus=status(Path);
		perms													Permissions=FileStatus.permissions();

		CheckFilePermissions(Path,FileStatus,Permissions);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCreateDirectory1(void)
{
	PrintLineSeparator();

	path														Directory(L"TEMP");

	try
	{
		// !!! DIRECTORY ma PERMISSIONS [perms::all].
		if (create_directory(Directory)==true)
		{
			wcout << L"DIRECTORY [" << Directory.wstring() << L"] was CREATED." << endl;
		}
		else
		{
			wcout << L"DIRECTORY [" << Directory.wstring() << L"] was NOT CREATED." << endl;
		}

		file_status												DirectoryStatus=status(Directory);

		wcout << L"DIRECTORY TYPE [" << int(DirectoryStatus.type()) << L"]." << endl;
		wcout << L"DIRECTORY PERMISSIONS [" << int(DirectoryStatus.permissions()) << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		uintmax_t												NumberOfRemovedEntries=remove_all(Directory);

		if (NumberOfRemovedEntries>0)
		{
			wcout << L"DIRECTORY [" << Directory.wstring() << L"] was REMOVED. NUMBER of REMOVED ENTRIES [" << NumberOfRemovedEntries << L"]." << endl;
		}
		else
		{
			wcout << L"DIRECTORY [" << Directory.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCreateDirectory2(void)
{
	PrintLineSeparator();

	path														Directory(L"TEMP");

	try
	{
		path													ExistingDirectory(L"Test");

		// !!! Novy DIRECTORY bude mat ATTRIBUTES prebrane z uz existujuceho DIRECTORY.
		if (create_directory(Directory,ExistingDirectory)==true)
		{
			wcout << L"DIRECTORY [" << Directory.wstring() << L"] was CREATED." << endl;
		}
		else
		{
			wcout << L"DIRECTORY [" << Directory.wstring() << L"] was NOT CREATED." << endl;
		}

		file_status												DirectoryStatus=status(Directory);

		wcout << L"DIRECTORY TYPE [" << int(DirectoryStatus.type()) << L"]." << endl;
		wcout << L"DIRECTORY PERMISSIONS [" << int(DirectoryStatus.permissions()) << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		uintmax_t												NumberOfRemovedEntries=remove_all(Directory);

		if (NumberOfRemovedEntries>0)
		{
			wcout << L"DIRECTORY [" << Directory.wstring() << L"] was REMOVED. NUMBER of REMOVED ENTRIES [" << NumberOfRemovedEntries << L"]." << endl;
		}
		else
		{
			wcout << L"DIRECTORY [" << Directory.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCreateDirectories(void)
{
	PrintLineSeparator();

	path														Directory1(L"Directory1");
	path														Directory2(L"Directory2");
	path														Directory3(L"Directory3");
	path														Directories=(Directory1 / Directory2 / Directory3);

	try
	{
		// !!! Vytvoria sa vsetky DIRECTORIES.
		if (create_directories(Directories)==true)
		{
			wcout << L"DIRECTORIES [" << Directories.wstring() << L"] was CREATED." << endl;
		}
		else
		{
			wcout << L"DIRECTORIES [" << Directories.wstring() << L"] was NOT CREATED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

#ifdef _MSC_VER
	try
	{
		uintmax_t												NumberOfRemovedEntries=remove_all(Directory1);

		if (NumberOfRemovedEntries>0)
		{
			wcout << L"DIRECTORIES [" << Directories.wstring() << L"] was REMOVED. NUMBER of REMOVED ENTRIES [" << NumberOfRemovedEntries << L"]." << endl;
		}
		else
		{
			wcout << L"DIRECTORIES [" << Directories.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}
#else
	try
	{
		// !!!!! FUNCTION [remove_all()] v LINUX NEFUNGUJE ak DIRECTORY obsahuje SUBDIRECTORIES. Nedokaze rekurzivne zmazat DIRECTORIES.
		path													Directory=(Directory1 / Directory2 / Directory3);

		if (remove(Directory)==true)
		{
			wcout << L"DIRECTORY [" << Directory.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"DIRECTORY [" << Directory.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		// !!!!! FUNCTION [remove_all()] v LINUX NEFUNGUJE ak DIRECTORY obsahuje SUBDIRECTORIES. Nedokaze rekurzivne zmazat DIRECTORIES.
		path													Directory=(Directory1 / Directory2);

		if (remove(Directory)==true)
		{
			wcout << L"DIRECTORY [" << Directory.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"DIRECTORY [" << Directory.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		// !!!!! FUNCTION [remove_all()] v LINUX NEFUNGUJE ak DIRECTORY obsahuje SUBDIRECTORIES. Nedokaze rekurzivne zmazat DIRECTORIES.
		path													Directory=Directory1;

		if (remove(Directory)==true)
		{
			wcout << L"DIRECTORY [" << Directory.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"DIRECTORY [" << Directory.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}
#endif

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCreateHardLink(void)
{
	PrintLineSeparator();

	path														Path(L"Test/File1.txt");
	path														PathHardlink1(L"HardLink1");
	path														PathHardlink2(L"HardLink2");

	try
	{
		uintmax_t												Count1=hard_link_count(Path);

		wcout << L"FILE [" << Path.wstring() << L"] HARD LINK COUNT [" << Count1 << L"]." << endl;

		create_hard_link(Path,PathHardlink1);

		wcout << L"HARD LINK [" << PathHardlink1.wstring() << L"] to FILE [" << Path.wstring() << L"] was CREATED." << endl;

		create_hard_link(Path,PathHardlink2);

		wcout << L"HARD LINK [" << PathHardlink2.wstring() << L"] to FILE [" << Path.wstring() << L"] was CREATED." << endl;

		file_status												Status1=status(PathHardlink1);

		wcout << L"HARD LINK [" << PathHardlink1.wstring() << L"] TYPE [" << int(Status1.type()) << L"]." << endl;
		wcout << L"HARD LINK [" << PathHardlink1.wstring() << L"] PERMISSIONS [" << int(Status1.permissions()) << L"]." << endl;

		file_status												Status2=status(PathHardlink2);

		wcout << L"HARD LINK [" << PathHardlink2.wstring() << L"] TYPE [" << int(Status2.type()) << L"]." << endl;
		wcout << L"HARD LINK [" << PathHardlink2.wstring() << L"] PERMISSIONS [" << int(Status2.permissions()) << L"]." << endl;

		uintmax_t												Count2=hard_link_count(Path);

		wcout << L"FILE [" << Path.wstring() << L"] HARD LINK COUNT [" << Count2 << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		uintmax_t												NumberOfRemovedEntries=remove_all(PathHardlink1);

		if (NumberOfRemovedEntries>0)
		{
			wcout << L"HARD LINK [" << PathHardlink1.wstring() << L"] was REMOVED. NUMBER of REMOVED ENTRIES [" << NumberOfRemovedEntries << L"]." << endl;
		}
		else
		{
			wcout << L"HARD LINK [" << PathHardlink1.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		uintmax_t												NumberOfRemovedEntries=remove_all(PathHardlink2);

		if (NumberOfRemovedEntries>0)
		{
			wcout << L"HARD LINK [" << PathHardlink2.wstring() << L"] was REMOVED. NUMBER of REMOVED ENTRIES [" << NumberOfRemovedEntries << L"]." << endl;
		}
		else
		{
			wcout << L"HARD LINK [" << PathHardlink2.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		uintmax_t												Count=hard_link_count(Path);

		wcout << L"FILE [" << Path.wstring() << L"] HARD LINK COUNT [" << Count << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCreateSymbolicLink(void)
{
	PrintLineSeparator();

	path														Path(L"Test/File1.txt");
	path														PathSymboliclink(L"MyFileLink");

	try
	{
		create_symlink(Path,PathSymboliclink);

		wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] to FILE [" << Path.wstring() << L"] was CREATED." << endl;

		file_status												Status=status(PathSymboliclink);

		wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] TYPE [" << int(Status.type()) << L"]." << endl;
		wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] PERMISSIONS [" << int(Status.permissions()) << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		// !!!!! Odstranuje sa SYMBOLIC LINK a nie TARGET na ktory SYMBOLIC LINK odkazuje.
		if (remove(PathSymboliclink)==true)
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCreateDirectorySymbolicLink(void)
{
	PrintLineSeparator();

	path														Path(L"Test");
	path														PathSymboliclink(L"MyFileLink");

	try
	{
		create_directory_symlink(Path,PathSymboliclink);

		wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] to FILE [" << Path.wstring() << L"] was CREATED." << endl;

		file_status												Status=status(PathSymboliclink);

		wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] TYPE [" << int(Status.type()) << L"]." << endl;
		wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] PERMISSIONS [" << int(Status.permissions()) << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		// !!!!! Odstranuje sa SYMBOLIC LINK a nie TARGET na ktory SYMBOLIC LINK odkazuje.
		if (remove(PathSymboliclink)==true)
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCopySymbolicLink(void)
{
	PrintLineSeparator();

	path														Path(L"Test/File1.txt");
	path														PathSymboliclink1(L"MyFileLink1");
	path														PathSymboliclink2(L"MyFileLink2");

	try
	{
		create_symlink(Path,PathSymboliclink1);

		wcout << L"SYMBOLIC LINK [" << PathSymboliclink1.wstring() << L"] to FILE [" << Path.wstring() << L"] was CREATED." << endl;

		file_status												Status1=status(PathSymboliclink1);

		wcout << L"SYMBOLIC LINK [" << PathSymboliclink1.wstring() << L"] TYPE [" << int(Status1.type()) << L"]." << endl;
		wcout << L"SYMBOLIC LINK [" << PathSymboliclink1.wstring() << L"] PERMISSIONS [" << int(Status1.permissions()) << L"]." << endl;

		// !!! Kopriuje SYMBOLIC LINK do novej PATH.
		copy_symlink(PathSymboliclink1,PathSymboliclink2);

		wcout << L"SYMBOLIC LINK [" << PathSymboliclink2.wstring() << L"] to FILE [" << Path.wstring() << L"] was COPIED." << endl;

		file_status												Status2=status(PathSymboliclink2);

		wcout << L"SYMBOLIC LINK [" << PathSymboliclink2.wstring() << L"] TYPE [" << int(Status2.type()) << L"]." << endl;
		wcout << L"SYMBOLIC LINK [" << PathSymboliclink2.wstring() << L"] PERMISSIONS [" << int(Status2.permissions()) << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		// !!!!! Odstranuje sa SYMBOLIC LINK a nie TARGET na ktory SYMBOLIC LINK odkazuje.
		if (remove(PathSymboliclink1)==true)
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink1.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink1.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		// !!!!! Odstranuje sa SYMBOLIC LINK a nie TARGET na ktory SYMBOLIC LINK odkazuje.
		if (remove(PathSymboliclink2)==true)
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink2.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink2.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCopy1(void)
{
	PrintLineSeparator();

	path														Path(L"Test/File1.txt");
	path														PathCopy(L"CopiedFile1.txt");

	try
	{
		copy(Path,PathCopy);

		wcout << L"FILE [" << Path.wstring() << L"] COPIED to FILE [" << PathCopy.wstring() << L"]." << endl;

		file_status												Status=status(PathCopy);

		wcout << L"FILE [" << PathCopy.wstring() << L"] TYPE [" << int(Status.type()) << L"]." << endl;
		wcout << L"FILE [" << PathCopy.wstring() << L"] PERMISSIONS [" << int(Status.permissions()) << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		if (remove(PathCopy)==true)
		{
			wcout << L"FILE [" << PathCopy.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"FILE [" << PathCopy.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCopy2(void)
{
	PrintLineSeparator();

	path														Path(L"Test/SubDirectory");
	path														PathCopy(L"CopiedDirectory");

	try
	{
		// !!! DIRECTORY sa kopiruje REKURZIVNE.
		copy(Path,PathCopy,copy_options::recursive);

		wcout << L"DIRECTORY [" << Path.wstring() << L"] COPIED to DIRECTORY [" << PathCopy.wstring() << L"]." << endl;

		file_status												Status=status(PathCopy);

		wcout << L"DIRECTORY [" << PathCopy.wstring() << L"] TYPE [" << int(Status.type()) << L"]." << endl;
		wcout << L"DIRECTORY [" << PathCopy.wstring() << L"] PERMISSIONS [" << int(Status.permissions()) << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		uintmax_t												NumberOfRemovedEntries=remove_all(PathCopy);

		if (NumberOfRemovedEntries>0)
		{
			wcout << L"DIRECTORY [" << PathCopy.wstring() << L"] was REMOVED. NUMBER of REMOVED ENTRIES [" << NumberOfRemovedEntries << L"]." << endl;
		}
		else
		{
			wcout << L"DIRECTORY [" << PathCopy.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCopyFile1(void)
{
	PrintLineSeparator();

	path														Path(L"Test/File1.txt");
	path														PathCopy(L"CopiedFile1.txt");

	try
	{
		copy_file(Path,PathCopy);

		wcout << L"FILE [" << Path.wstring() << L"] COPIED to FILE [" << PathCopy.wstring() << L"]." << endl;

		file_status												Status=status(PathCopy);

		wcout << L"FILE [" << PathCopy.wstring() << L"] TYPE [" << int(Status.type()) << L"]." << endl;
		wcout << L"FILE [" << PathCopy.wstring() << L"] PERMISSIONS [" << int(Status.permissions()) << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		if (remove(PathCopy)==true)
		{
			wcout << L"FILE [" << PathCopy.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"FILE [" << PathCopy.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCopyFile2(void)
{
	PrintLineSeparator();

	path														Path(L"Test/File1.txt");
	path														PathCopy(L"CopiedFile1.txt");

	try
	{
		copy_file(Path,PathCopy,copy_options::none);

		wcout << L"FILE [" << Path.wstring() << L"] COPIED to FILE [" << PathCopy.wstring() << L"]." << endl;

		file_status												Status=status(PathCopy);

		wcout << L"FILE [" << PathCopy.wstring() << L"] TYPE [" << int(Status.type()) << L"]." << endl;
		wcout << L"FILE [" << PathCopy.wstring() << L"] PERMISSIONS [" << int(Status.permissions()) << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		// !!! FILE sa PREPISE novym CONTENT.
		copy_file(Path,PathCopy,copy_options::overwrite_existing);

		wcout << L"FILE [" << Path.wstring() << L"] COPIED to FILE [" << PathCopy.wstring() << L"]." << endl;

		file_status												Status=status(PathCopy);

		wcout << L"FILE [" << PathCopy.wstring() << L"] TYPE [" << int(Status.type()) << L"]." << endl;
		wcout << L"FILE [" << PathCopy.wstring() << L"] PERMISSIONS [" << int(Status.permissions()) << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		if (remove(PathCopy)==true)
		{
			wcout << L"FILE [" << PathCopy.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"FILE [" << PathCopy.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestRemove(void)
{
	PrintLineSeparator();

	path														Path(L"Test/File1.txt");
	path														PathCopy(L"CopiedFile1.txt");

	try
	{
		copy_file(Path,PathCopy);

		wcout << L"FILE [" << Path.wstring() << L"] COPIED to FILE [" << PathCopy.wstring() << L"]." << endl;

		file_status												Status=status(PathCopy);

		wcout << L"FILE [" << PathCopy.wstring() << L"] TYPE [" << int(Status.type()) << L"]." << endl;
		wcout << L"FILE [" << PathCopy.wstring() << L"] PERMISSIONS [" << int(Status.permissions()) << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		// !!! FILE sa zmaze.
		if (remove(PathCopy)==true)
		{
			wcout << L"FILE [" << PathCopy.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"FILE [" << PathCopy.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestRemoveAll(void)
{
	PrintLineSeparator();

	path														Path(L"Test/SubDirectory");
	path														PathCopy(L"CopiedDirectory");

	try
	{
		// !!! DIRECTORY sa kopiruje REKURZIVNE.
		copy(Path,PathCopy,copy_options::recursive);

		wcout << L"DIRECTORY [" << Path.wstring() << L"] COPIED to DIRECTORY [" << PathCopy.wstring() << L"]." << endl;

		file_status												Status=status(PathCopy);

		wcout << L"DIRECTORY [" << PathCopy.wstring() << L"] TYPE [" << int(Status.type()) << L"]." << endl;
		wcout << L"DIRECTORY [" << PathCopy.wstring() << L"] PERMISSIONS [" << int(Status.permissions()) << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		// !!! FUNCTION REKURZIVNE odstrani DIRECTORY a jeho SUBDIRECTORIES.
		// !!!!! FUNCTION [remove_all()] v LINUX NEFUNGUJE ak DIRECTORY obsahuje SUBDIRECTORIES. Nedokaze rekurzivne zmazat DIRECTORIES. Ale ak DIRECTORY SUBDIRECTORIES NEOBSAHUJE FUNCTION na LINUX funguje OK.
		uintmax_t												NumberOfRemovedEntries=remove_all(PathCopy);

		if (NumberOfRemovedEntries>0)
		{
			wcout << L"DIRECTORY [" << PathCopy.wstring() << L"] was REMOVED. NUMBER of REMOVED ENTRIES [" << NumberOfRemovedEntries << L"]." << endl;
		}
		else
		{
			wcout << L"DIRECTORY [" << PathCopy.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestRename1(void)
{
	PrintLineSeparator();

	path														Path(L"Test/File1.txt");
	path														PathCopy(L"CopiedFile1.txt");
	path														PathRename(L"CopiedFile2.txt");

	try
	{
		copy_file(Path,PathCopy);

		wcout << L"FILE [" << Path.wstring() << L"] COPIED to FILE [" << PathCopy.wstring() << L"]." << endl;

		file_status												Status=status(PathCopy);

		wcout << L"FILE [" << PathCopy.wstring() << L"] TYPE [" << int(Status.type()) << L"]." << endl;
		wcout << L"FILE [" << PathCopy.wstring() << L"] PERMISSIONS [" << int(Status.permissions()) << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		rename(PathCopy,PathRename);

		wcout << L"FILE [" << PathCopy.wstring() << L"] MOVED to FILE [" << PathRename.wstring() << L"]." << endl;

		file_status												Status=status(PathRename);

		wcout << L"FILE [" << PathRename.wstring() << L"] TYPE [" << int(Status.type()) << L"]." << endl;
		wcout << L"FILE [" << PathRename.wstring() << L"] PERMISSIONS [" << int(Status.permissions()) << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		if (remove(PathRename)==true)
		{
			wcout << L"FILE [" << PathRename.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"FILE [" << PathRename.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestRename2(void)
{
	PrintLineSeparator();

	path														Path(L"Test/SubDirectory");
	path														PathCopy(L"CopiedDirectory");
	path														PathRename(L"RenamedDirectory");

	try
	{
		// !!! DIRECTORY sa kopiruje REKURZIVNE.
		copy(Path,PathCopy,copy_options::recursive);

		wcout << L"DIRECTORY [" << Path.wstring() << L"] COPIED to DIRECTORY [" << PathCopy.wstring() << L"]." << endl;

		file_status												Status=status(PathCopy);

		wcout << L"DIRECTORY [" << PathCopy.wstring() << L"] TYPE [" << int(Status.type()) << L"]." << endl;
		wcout << L"DIRECTORY [" << PathCopy.wstring() << L"] PERMISSIONS [" << int(Status.permissions()) << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		// !!! Vykona sa RENAME DIRECTORY.
		rename(PathCopy,PathRename);

		wcout << L"DIRECTORY [" << Path.wstring() << L"] RENAMED to DIRECTORY [" << PathCopy.wstring() << L"]." << endl;

		file_status												Status=status(PathRename);

		wcout << L"DIRECTORY [" << PathRename.wstring() << L"] TYPE [" << int(Status.type()) << L"]." << endl;
		wcout << L"DIRECTORY [" << PathRename.wstring() << L"] PERMISSIONS [" << int(Status.permissions()) << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		uintmax_t												NumberOfRemovedEntries=remove_all(PathRename);

		if (NumberOfRemovedEntries>0)
		{
			wcout << L"DIRECTORY [" << PathRename.wstring() << L"] was REMOVED. NUMBER of REMOVED ENTRIES [" << NumberOfRemovedEntries << L"]." << endl;
		}
		else
		{
			wcout << L"DIRECTORY [" << PathRename.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template <typename TTimePoint>
time_t TimePointToTimeSet(TTimePoint TimePoint)
{
	system_clock::time_point									CurrentSystemTime=system_clock::now();
	typename TTimePoint::clock::time_point						CurrentTimePointTime=TTimePoint::clock::now();
    time_point<system_clock,system_clock::duration>				ConvertedTime=time_point_cast<system_clock::duration>(TimePoint-CurrentTimePointTime+CurrentSystemTime);
	time_t														Time=system_clock::to_time_t(ConvertedTime);

    return(Time);
}
//----------------------------------------------------------------------------------------------------------------------
void TestLastWriteTime(void)
{
	PrintLineSeparator();

	path														Path(L"Test/SubDirectory/SomeFile.txt");

	{
		file_time_type											FileTime=last_write_time(Path);
		time_t													Time=TimePointToTimeSet(FileTime);

		wcout << L"PATH [" << Path.wstring() << L"] FILE TIME [" << Time << L"]." << endl;
	}

	PrintLineSeparator();

	{
		time_point												CurrentTime=file_time_type::clock::now();

		last_write_time(Path,CurrentTime);

		wcout << L"PATH [" << Path.wstring() << L"] FILE TIME SET." << endl;
	}


	PrintLineSeparator();

	{
		file_time_type											FileTime=last_write_time(Path);
		time_t													Time=TimePointToTimeSet(FileTime);

		wcout << L"PATH [" << Path.wstring() << L"] FILE TIME [" << Time << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestPermissions(void)
{
	PrintLineSeparator();

	path														Path(L"Test/File1.txt");
	path														PathCopy(L"CopiedFile1.txt");

	try
	{
		copy(Path,PathCopy);

		wcout << L"FILE [" << Path.wstring() << L"] COPIED to FILE [" << PathCopy.wstring() << L"]." << endl;

		file_status												Status1=status(PathCopy);

		wcout << L"FILE [" << PathCopy.wstring() << L"] TYPE [" << int(Status1.type()) << L"]." << endl;
		wcout << L"FILE [" << PathCopy.wstring() << L"] PERMISSIONS [" << int(Status1.permissions()) << L"]." << endl;

#ifdef _MSC_VER
		// !!! Pre WINDOWS je nutne pridavat a odoberat PERMISSIONS pre vsetkych USERS.
		perms													PermissionsToRemove=(perms::owner_write | perms::group_write | perms::others_write);
#else
		perms													PermissionsToRemove=(perms::group_write);
#endif

		permissions(PathCopy,PermissionsToRemove,perm_options::remove);

		wcout << L"FILE [" << PathCopy.wstring() << L"] PERMISSIONS [" << int(PermissionsToRemove) << L"] were REMOVED." << endl;

		file_status												Status2=status(PathCopy);

		wcout << L"FILE [" << PathCopy.wstring() << L"] PERMISSIONS [" << int(Status2.permissions()) << L"]." << endl;

#ifdef _MSC_VER
		// !!! Pre WINDOWS je nutne pridavat a odoberat PERMISSIONS pre vsetkych USERS.
		perms													PermissionsToAdd=(perms::owner_write | perms::group_write | perms::others_write);
#else
		perms													PermissionsToAdd=(perms::group_write);
#endif

		permissions(PathCopy,PermissionsToAdd,perm_options::add);

		wcout << L"FILE [" << PathCopy.wstring() << L"] PERMISSIONS [" << int(PermissionsToAdd) << L"] were ADDED." << endl;

		file_status												Status3=status(PathCopy);

		wcout << L"FILE [" << PathCopy.wstring() << L"] PERMISSIONS [" << int(Status3.permissions()) << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		if (remove(PathCopy)==true)
		{
			wcout << L"FILE [" << PathCopy.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"FILE [" << PathCopy.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestResizeFile(void)
{
	PrintLineSeparator();

	path														Path(L"Test/File1.txt");
	path														PathCopy(L"CopiedFile1.txt");

	try
	{
		copy(Path,PathCopy);

		wcout << L"FILE [" << Path.wstring() << L"] COPIED to FILE [" << PathCopy.wstring() << L"]." << endl;

		file_status												Status=status(PathCopy);

		wcout << L"FILE [" << PathCopy.wstring() << L"] TYPE [" << int(Status.type()) << L"]." << endl;
		wcout << L"FILE [" << PathCopy.wstring() << L"] PERMISSIONS [" << int(Status.permissions()) << L"]." << endl;

		uintmax_t												FileSize1=file_size(PathCopy);

		wcout << L"FILE [" << PathCopy.wstring() << L"] FILE SIZE [" << FileSize1 << L"]." << endl;

		uintmax_t												NewFileSize=(FileSize1/2);

		// !!! Nastavi sa FILE SIZE.
		resize_file(PathCopy,NewFileSize);

		wcout << L"FILE [" << PathCopy.wstring() << L"] SET new FILE SIZE [" << NewFileSize << L"]." << endl;

		uintmax_t												FileSize2=file_size(PathCopy);

		wcout << L"FILE [" << PathCopy.wstring() << L"] FILE SIZE [" << FileSize2 << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		if (remove(PathCopy)==true)
		{
			wcout << L"FILE [" << PathCopy.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"FILE [" << PathCopy.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestReadSymLink(void)
{
	PrintLineSeparator();

	path														Path(L"Test/File1.txt");
	path														PathSymboliclink(L"MyFileLink");

	try
	{
		create_symlink(Path,PathSymboliclink);

		wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] to FILE [" << Path.wstring() << L"] was CREATED." << endl;

		file_status												Status=status(PathSymboliclink);

		wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] TYPE [" << int(Status.type()) << L"]." << endl;
		wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] PERMISSIONS [" << int(Status.permissions()) << L"]." << endl;

		// !!! FUNCTION vracia PATH na ktoru odkazuje SYMBOLIC LINK.
		// !!! SYMBOLIC LINK MUSI existovat.
		path													PathToSymboliclink=read_symlink(PathSymboliclink);

		wcout << L"PATH to SYMBOLIC LINK [" << PathToSymboliclink.wstring() << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	try
	{
		// !!!!! Odstranuje sa SYMBOLIC LINK a nie TARGET na ktory SYMBOLIC LINK odkazuje.
		if (remove(PathSymboliclink)==true)
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestAbsolute(void)
{
	PrintLineSeparator();

	path														PathSymboliclink(L"MyFileLink");

	try
	{
		path													Path(L"Test/File1.txt");

		create_symlink(Path,PathSymboliclink);

		wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] to FILE [" << Path.wstring() << L"] was CREATED." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"Test/File1.txt");

		// !!! ABSOLUTE PATH voci CURRENT PATH.
		path													AbsolutePath=absolute(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"ABSOLUTE PATH [" << AbsolutePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"Test/../Test/./File1.txt");

		// !!! ABSOLUTE PATH voci CURRENT PATH.
		path													AbsolutePath=absolute(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"ABSOLUTE PATH [" << AbsolutePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"./File1.txt");

		// !!! ABSOLUTE PATH voci CURRENT PATH.
		path													AbsolutePath=absolute(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"ABSOLUTE PATH [" << AbsolutePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! ABSOLUTE PATH.
		path													Path(L"/Directory1/Directory2/NonExistingFile.txt");
		path													AbsolutePath=absolute(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"ABSOLUTE PATH [" << AbsolutePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! PATH na SYMBOLIC LINK.
		path													Path=PathSymboliclink;
		path													AbsolutePath=absolute(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"ABSOLUTE PATH [" << AbsolutePath.wstring() << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!!!! Odstranuje sa SYMBOLIC LINK a nie TARGET na ktory SYMBOLIC LINK odkazuje.
		if (remove(PathSymboliclink)==true)
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCanonical(void)
{
	PrintLineSeparator();

	path														PathSymboliclink(L"MyFileLink");

	try
	{
		path													Path(L"Test/File1.txt");

		create_symlink(Path,PathSymboliclink);

		wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] to FILE [" << Path.wstring() << L"] was CREATED." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"Test/File1.txt");

		// !!! ABSOLUTE PATH voci CURRENT PATH.
		// !!! PATH MUSI existovat.
		path													CanonicalPath=canonical(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"CANONICAL PATH [" << CanonicalPath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"Test/../Test/./File1.txt");

		// !!! ABSOLUTE PATH voci CURRENT PATH.
		path													CanonicalPath=canonical(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"CANONICAL PATH [" << CanonicalPath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"./Test/File1.txt");

		// !!! ABSOLUTE PATH voci CURRENT PATH.
		path													CanonicalPath=canonical(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"CANONICAL PATH [" << CanonicalPath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													CurrentPath=current_path();
		path													RelativePath(L"Test");

		// !!! ABSOLUTE PATH.
		path													Path=(CurrentPath / RelativePath);
		path													CanonicalPath=canonical(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"CANONICAL PATH [" << CanonicalPath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! PATH na SYMBOLIC LINK.
		path													Path=PathSymboliclink;

		// !!!!! FUNCTION robi RESOLVE SYMBOLIC LINKS.
		path													CanonicalPath=canonical(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"CANONICAL PATH [" << CanonicalPath.wstring() << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! FILE MUSI EXISTOVAT.
		path													Path("NonExistingFile.txt");
		path													WeaklyCanonicalPath=canonical(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"CANONICAL PATH [" << WeaklyCanonicalPath.wstring() << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!!!! Odstranuje sa SYMBOLIC LINK a nie TARGET na ktory SYMBOLIC LINK odkazuje.
		if (remove(PathSymboliclink)==true)
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestWeaklyCanonical(void)
{
	PrintLineSeparator();

	path														PathSymboliclink(L"MyFileLink");

	try
	{
		path													Path(L"Test/File1.txt");

		create_symlink(Path,PathSymboliclink);

		wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] to FILE [" << Path.wstring() << L"] was CREATED." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"Test/File1.txt");

		// !!! ABSOLUTE PATH voci CURRENT PATH.
		// !!! PATH MUSI existovat.
		path													WeaklyCanonicalPath=weakly_canonical(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"WEAKLY CANONICAL PATH [" << WeaklyCanonicalPath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"Test/../Test/./File1.txt");

		// !!! ABSOLUTE PATH voci CURRENT PATH.
		path													WeaklyCanonicalPath=weakly_canonical(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"WEAKLY CANONICAL PATH [" << WeaklyCanonicalPath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"./Test/File1.txt");

		// !!! ABSOLUTE PATH voci CURRENT PATH.
		path													WeaklyCanonicalPath=weakly_canonical(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"WEAKLY CANONICAL PATH [" << WeaklyCanonicalPath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													CurrentPath=current_path();
		path													RelativePath(L"Test");

		// !!! ABSOLUTE PATH.
		path													Path=(CurrentPath / RelativePath);
		path													WeaklyCanonicalPath=weakly_canonical(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"WEAKLY CANONICAL PATH [" << WeaklyCanonicalPath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! PATH na SYMBOLIC LINK.
		path													Path=PathSymboliclink;

		// !!!!! FUNCTION robi RESOLVE SYMBOLIC LINKS.
		path													WeaklyCanonicalPath=weakly_canonical(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"WEAKLY CANONICAL PATH [" << WeaklyCanonicalPath.wstring() << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! FILE NEMUSI EXISTOVAT.
		path													Path("NonExistingFile.txt");
		path													WeaklyCanonicalPath=weakly_canonical(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"WEAKLY CANONICAL PATH [" << WeaklyCanonicalPath.wstring() << L"]." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!!!! Odstranuje sa SYMBOLIC LINK a nie TARGET na ktory SYMBOLIC LINK odkazuje.
		if (remove(PathSymboliclink)==true)
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestRelative(void)
{
	PrintLineSeparator();

	path														PathSymboliclink(L"MyFileLink");

	try
	{
		path													Path(L"Test/File1.txt");

		create_symlink(Path,PathSymboliclink);

		wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] to FILE [" << Path.wstring() << L"] was CREATED." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"Test/File1.txt");

		// !!! Urci sa RELATIVE PATH voci CURRENT PATH.
		path													RelativePath=relative(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"RELATIVE PATH [" << RelativePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"Test/File1.txt");
		path													BasePath(L"Test");

		// !!! Urci sa RELATIVE PATH voci BASE PATH.
		path													RelativePath=relative(Path,BasePath);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"BASE PATH [" << BasePath.wstring() << L"]." << endl;
		wcout << L"RELATIVE PATH [" << RelativePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"Test/File1.txt");
		path													BasePath(L"..");

		// !!! Urci sa RELATIVE PATH voci BASE PATH.
		path													RelativePath=relative(Path,BasePath);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"BASE PATH [" << BasePath.wstring() << L"]." << endl;
		wcout << L"RELATIVE PATH [" << RelativePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"Test/File1.txt");

		// !!! ABSOLUTE PATH.
		path													BasePath(L"/Directory1/Directory2");

		// !!! Urci sa RELATIVE PATH voci BASE PATH.
		// !!!!! Kedze RELATIVE PATH NEEXISTUJE, FUNCTION vrati EMPTY PATH.
		path													RelativePath=relative(Path,BasePath);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"BASE PATH [" << BasePath.wstring() << L"]." << endl;
		wcout << L"RELATIVE PATH [" << RelativePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"Test/File2.txt");

		// !!! PATH na SYMBOLIC LINK.
		path													BasePath=PathSymboliclink;

		// !!! Urci sa RELATIVE PATH voci BASE PATH.
		// !!! Robi sa RESOLVE SYMBOLIC LINK.
		path													RelativePath=relative(Path,BasePath);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"BASE PATH [" << BasePath.wstring() << L"]." << endl;
		wcout << L"RELATIVE PATH [" << RelativePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!!!! Odstranuje sa SYMBOLIC LINK a nie TARGET na ktory SYMBOLIC LINK odkazuje.
		if (remove(PathSymboliclink)==true)
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestProximate(void)
{
	PrintLineSeparator();

	path														PathSymboliclink(L"MyFileLink");

	try
	{
		path													Path(L"Test/File1.txt");

		create_symlink(Path,PathSymboliclink);

		wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] to FILE [" << Path.wstring() << L"] was CREATED." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"Test/File1.txt");

		// !!! Urci sa RELATIVE PATH voci CURRENT PATH.
		path													ProximatePath=proximate(Path);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"PROXIMATE PATH [" << ProximatePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"Test/File1.txt");
		path													BasePath(L"Test");

		// !!! Urci sa RELATIVE PATH voci BASE PATH.
		path													ProximatePath=proximate(Path,BasePath);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"BASE PATH [" << BasePath.wstring() << L"]." << endl;
		wcout << L"PROXIMATE PATH [" << ProximatePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"Test/File1.txt");
		path													BasePath(L"..");

		// !!! Urci sa RELATIVE PATH voci BASE PATH.
		path													ProximatePath=proximate(Path,BasePath);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"BASE PATH [" << BasePath.wstring() << L"]." << endl;
		wcout << L"PROXIMATE PATH [" << ProximatePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"Test/File1.txt");

		// !!! ABSOLUTE PATH.
		path													BasePath(L"/Directory1/Directory2");

		// !!! Urci sa RELATIVE PATH voci BASE PATH.
		// !!!!! Kedze RELATIVE PATH NEEXISTUJE, FUNCTION vrati PATH v PARAMETER [Path].
		path													ProximatePath=proximate(Path,BasePath);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"BASE PATH [" << BasePath.wstring() << L"]." << endl;
		wcout << L"PROXIMATE PATH [" << ProximatePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! RELATIVE PATH.
		path													Path(L"Test/File2.txt");

		// !!! PATH na SYMBOLIC LINK.
		path													BasePath=PathSymboliclink;

		// !!! Urci sa RELATIVE PATH voci BASE PATH.
		// !!! Robi sa RESOLVE SYMBOLIC LINK.
		path													ProximatePath=proximate(Path,BasePath);

		wcout << L"PATH [" << Path.wstring() << L"]." << endl;
		wcout << L"BASE PATH [" << BasePath.wstring() << L"]." << endl;
		wcout << L"PROXIMATE PATH [" << ProximatePath.wstring() << L"]." << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!!!! Odstranuje sa SYMBOLIC LINK a nie TARGET na ktory SYMBOLIC LINK odkazuje.
		if (remove(PathSymboliclink)==true)
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCurrentPath(void)
{
	PrintLineSeparator();

	path														CurrentPath1=current_path();

	wcout << L"CURRENT PATH 1 [" << CurrentPath1.wstring() << L"]." << endl;

	path														NewCurrentPath1(L"Test");

	current_path(NewCurrentPath1);

	wcout << L"CURRENT PATH set to PATH [" << NewCurrentPath1.wstring() << L"]." << endl;
	
	path														CurrentPath2=current_path();

	wcout << L"CURRENT PATH 2 [" << CurrentPath2.wstring() << L"]." << endl;

	path														NewCurrentPath2(L"..");

	current_path(NewCurrentPath2);

	wcout << L"CURRENT PATH set to PATH [" << NewCurrentPath2.wstring() << L"]." << endl;
	
	path														CurrentPath3=current_path();

	wcout << L"CURRENT PATH 3 [" << CurrentPath3.wstring() << L"]." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestSpace(void)
{
	PrintLineSeparator();

	path														Path(L".");
	space_info													Space=space(Path);

	wcout << L"PATH [" << Path.wstring() << L"]." << endl;
	wcout << L"SPACE CAPACITY [" << Space.capacity << L"]." << endl;
	wcout << L"SPACE AVAILABLE [" << Space.available << L"]." << endl;
	wcout << L"SPACE FREE [" << Space.free << L"]." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestDirectoryIterator(void)
{
	PrintLineSeparator();

	path														PathSymboliclink(L"MyFileLink");

	try
	{
		path													Path(L"Test/File1.txt");

		create_symlink(Path,PathSymboliclink);

		wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] to FILE [" << Path.wstring() << L"] was CREATED." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Directory(L".");
		directory_iterator										Iterator(Directory);

		for(const directory_entry& Entry : Iterator)
		{
			wcout << L"ENTRY [" << Entry.path().wstring() << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		path													Directory(L".");

		// !!! ITERATOR vstupuje do SYMBOLIC LINKS.
		directory_iterator										Iterator(Directory,directory_options::follow_directory_symlink);

		for(const directory_entry& Entry : Iterator)
		{
			wcout << L"ENTRY [" << Entry.path().wstring() << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		path													Directory(L".");
		directory_iterator										BeginIterator(Directory);
		directory_iterator										EndIterator;

		while(BeginIterator!=EndIterator)
		{
			const directory_entry&								Entry=*BeginIterator;

			wcout << L"ENTRY [" << Entry.path().wstring() << L"]." << endl;

			BeginIterator++;
		}
	}

	PrintLineSeparator();

	{
		path													Directory(L".");
		directory_iterator										DirectoryIterator(Directory,directory_options::follow_directory_symlink);

		for(directory_iterator Iterator=begin(DirectoryIterator);Iterator!=end(DirectoryIterator);Iterator++)
		{
			const directory_entry&								Entry=*Iterator;

			wcout << L"ENTRY [" << Entry.path().wstring() << L"]." << endl;
		}
	}

	PrintLineSeparator();

	try
	{
		// !!!!! Odstranuje sa SYMBOLIC LINK a nie TARGET na ktory SYMBOLIC LINK odkazuje.
		if (remove(PathSymboliclink)==true)
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
wstring GetTabs(int Depth)
{
	wstring														Tabs;

	for(int Index=0;Index<Depth;Index++)
	{
		Tabs+=L"\t";
	}

	return(Tabs);
}
//----------------------------------------------------------------------------------------------------------------------
void TestRecursiveDirectoryIterator(void)
{
	PrintLineSeparator();

	path														PathSymboliclink(L"MyFileLink");

	try
	{
		path													Path(L"Test/File1.txt");

		create_symlink(Path,PathSymboliclink);

		wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] to FILE [" << Path.wstring() << L"] was CREATED." << endl;
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		path													Directory(L".");
		recursive_directory_iterator							Iterator(Directory);

		for(const directory_entry& Entry : Iterator)
		{
			int													Depth=Iterator.depth();
			wstring												Tabs=GetTabs(Depth);

			wcout << Tabs << L"ENTRY [" << Entry.path().wstring() << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		path													Directory(L".");

		// !!! ITERATOR vstupuje do SYMBOLIC LINKS.
		recursive_directory_iterator							Iterator(Directory,directory_options::follow_directory_symlink);

		for(const directory_entry& Entry : Iterator)
		{
			int													Depth=Iterator.depth();
			wstring												Tabs=GetTabs(Depth);

			wcout << Tabs << L"ENTRY [" << Entry.path().wstring() << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		path													Directory(L".");
		recursive_directory_iterator							BeginIterator(Directory);
		recursive_directory_iterator										EndIterator;

		while(BeginIterator!=EndIterator)
		{
			const directory_entry&								Entry=*BeginIterator;

			int													Depth=BeginIterator.depth();
			wstring												Tabs=GetTabs(Depth);

			wcout << Tabs << L"ENTRY [" << Entry.path().wstring() << L"]." << endl;

			BeginIterator++;
		}
	}

	PrintLineSeparator();

	{
		path													Directory(L".");
		recursive_directory_iterator							DirectoryIterator(Directory,directory_options::follow_directory_symlink);

		for(recursive_directory_iterator Iterator=begin(DirectoryIterator);Iterator!=end(DirectoryIterator);Iterator++)
		{
			const directory_entry&								Entry=*Iterator;

			int													Depth=Iterator.depth();
			wstring												Tabs=GetTabs(Depth);

			wcout << Tabs << L"ENTRY [" << Entry.path().wstring() << L"]." << endl;
		}
	}

	PrintLineSeparator();

	try
	{
		// !!!!! Odstranuje sa SYMBOLIC LINK a nie TARGET na ktory SYMBOLIC LINK odkazuje.
		if (remove(PathSymboliclink)==true)
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was REMOVED." << endl;
		}
		else
		{
			wcout << L"SYMBOLIC LINK [" << PathSymboliclink.wstring() << L"] was NOT REMOVED." << endl;
		}
	}
	catch(const filesystem_error& E)
	{
		wstring													What=ConvertStringToWideString(E.what());
		error_code												Code=E.code();
		const path&												Path1=E.path1();
		const path&												Path2=E.path2();

		wcout << L"EXCEPTION - WHAT [" << What << L"] CODE [" << Code << L"] PATH 1 [" << Path1 << L"] PATH 2 [" << Path2 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
wstring GetTabsEntry(int Depth)
{
	wstring														Tabs;

	for(int Index=0;Index<Depth;Index++)
	{
		Tabs+=L"\t";
	}

	return(Tabs);
}
//----------------------------------------------------------------------------------------------------------------------
void PrintDirectoryEntry(directory_entry Entry, int Depth)
{
	// !!!!! Vykonsa sa REFRESH FILE PROPERTIES.
	Entry.refresh();

	wstring														Tabs=GetTabsEntry(Depth);

	wcout << Tabs << L"ENTRY [" << Entry.path().wstring() << L"]." << endl;

	if (Entry.is_regular_file()==true)
	{
		wcout << Tabs << L"\tFILE SIZE [" << Entry.file_size() << L"]." << endl;
	}

	wcout << Tabs << L"\tHARD LINK COUNT [" << Entry.hard_link_count() << L"]." << endl;

	wcout << Tabs << L"\tEXISTS [" << Entry.exists() << L"]." << endl;

	wcout << Tabs << L"\tIS REGULAR FILE [" << Entry.is_regular_file() << L"]." << endl;
	wcout << Tabs << L"\tIS DIRECTORY [" << Entry.is_directory() << L"]." << endl;
	wcout << Tabs << L"\tIS OTHER [" << Entry.is_other() << L"]." << endl;
	wcout << Tabs << L"\tIS SYMBOLIC LINK [" << Entry.is_symlink() << L"]." << endl;
	wcout << Tabs << L"\tIS BLOCK FILE [" << Entry.is_block_file() << L"]." << endl;
	wcout << Tabs << L"\tIS CHARACTER FILE [" << Entry.is_character_file() << L"]." << endl;
	wcout << Tabs << L"\tIS FIFO [" << Entry.is_fifo() << L"]." << endl;
	wcout << Tabs << L"\tIS SOCKET [" << Entry.is_socket() << L"]." << endl;

}
//----------------------------------------------------------------------------------------------------------------------
void TestDirectoryEntry(void)
{
	PrintLineSeparator();

	{
		path													Directory(L".");
		recursive_directory_iterator							Iterator(Directory);

		for(const directory_entry& Entry : Iterator)
		{
			int													Depth=Iterator.depth();

			PrintDirectoryEntry(Entry,Depth);
		}
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main()
{
	SafeMain();

    //TestReadOperations();
    //TestWriteOperations();
    //TestPathNormalization();
	//TestFilesystemErrors();
	//TestFileTypes();
	//TestCurrentAndTempPaths();
	//TestPathProperties();
	//TestPathIteration();
	//TestPathInputOutputOperators();
	//TestPathRelativePaths();
	//TestPathStringConversions();
	//TestPathNativeGenericFormats();
	//TestPathOperatorSlash();
	//TestPathOperatorSlashEqual();
	//TestPathAppend();
	//TestPathOperatorPlusEqualAndConcat();
	//TestPathOperatorEqualAndAssignAndSwapAndClear();
	//TestPathRemoveFilenameReplaceFilename();
	//TestPathReplaceExtension();
	//TestPathComparisons();
	//TestPathEquivalent();
	//TestPathHashValue();
	//TestFileAttributes();
	//TestFileOtherAttributes();
	//TestFileStatus();
	//TestFilePermissions();
	//TestCreateDirectory1();
	//TestCreateDirectory2();
	//TestCreateDirectories();
	//TestCreateHardLink();
	//TestCreateSymbolicLink();
	//TestCreateDirectorySymbolicLink();
	//TestCopySymbolicLink();
	//TestCopy1();
	//TestCopy2();
	//TestCopyFile1();
	//TestCopyFile2();
	//TestRemove();
	//TestRemoveAll();
	//TestRename1();
	//TestRename2();
	//TestLastWriteTime();
	//TestPermissions();
	//TestResizeFile();
	//TestReadSymLink();
	//TestAbsolute();
	//TestCanonical();
	//TestWeaklyCanonical();
	//TestRelative();
	//TestProximate();
	//TestCurrentPath();
	//TestSpace();
	//TestDirectoryIterator();
	//TestRecursiveDirectoryIterator();
	TestDirectoryEntry();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------