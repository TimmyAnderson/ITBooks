//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>
#include <filesystem>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
using namespace std;
using namespace std::experimental::filesystem::v1;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PrintPathFragments(const path& Path)
{
	wcout << L"FULL PATH [" << Path.wstring() << L"] !" << endl;

	if (Path.has_root_name()==true)
	{
		wcout << L"ROOT NAME [" << Path.root_name().wstring() << L"] !" << endl;
	}

	if (Path.has_root_directory()==true)
	{
		wcout << L"ROOT DIRECTORY [" << Path.root_directory().wstring() << L"] !" << endl;
	}

	if (Path.has_root_path()==true)
	{
		wcout << L"ROOT PATH [" << Path.root_path().wstring() << L"] !" << endl;
	}

	if (Path.has_parent_path()==true)
	{
		wcout << L"PARENT PATH [" << Path.parent_path().wstring() << L"] !" << endl;
	}

	if (Path.has_relative_path()==true)
	{
		wcout << L"RELATIVE PATH [" << Path.relative_path().wstring() << L"] !" << endl;
	}

	if (Path.has_filename()==true)
	{
		wcout << L"FILENAME [" << Path.filename().wstring() << L"] !" << endl;
	}

	if (Path.has_extension()==true)
	{
		wcout << L"EXTENSION [" << Path.extension().wstring() << L"] !" << endl;
	}

	if (Path.has_stem()==true)
	{
		wcout << L"STEM [" << Path.stem().wstring() << L"] !" << endl;
	}

	if (Path.is_absolute()==true)
	{
		wcout << L"PATH is ABSOTULE !" << endl;
	}

	if (Path.is_relative()==true)
	{
		wcout << L"PATH is RELATIVE !" << endl;
	}
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPath(void)
{
	PrintLineSeparator();

	PrintPathFragments("C:\\Dir1\\Dir2\\Text.txt");

	PrintLineSeparator();

	PrintPathFragments("/dev/list/Text.txt");

	PrintLineSeparator();

	PrintPathFragments("Dir2\\Text.txt");

	PrintLineSeparator();

	PrintPathFragments("list/Text.txt");

	PrintLineSeparator();

	PrintPathFragments("list1/list2/");

	PrintLineSeparator();

	PrintPathFragments("List1\\List2\\");

	PrintLineSeparator();

	PrintPathFragments("Text.txt");

	PrintLineSeparator();

	PrintPathFragments("Dir/..");

	PrintLineSeparator();

	PrintPathFragments("/Dir");

	PrintLineSeparator();

	PrintPathFragments("\\Dir");

	PrintLineSeparator();

	PrintPathFragments("C:");

	PrintLineSeparator();

	PrintPathFragments("C:\\");

	PrintLineSeparator();

	PrintPathFragments("C:\\\\\\\\\\\\");

	PrintLineSeparator();

	PrintPathFragments("C:\\Dir");

	PrintLineSeparator();

	PrintPathFragments("C:\\\\\\\\\\Dir1\\\\\\\\\\Dir2\\\\\\\\");

	PrintLineSeparator();

	PrintPathFragments("C:\\\\\\\\\\Dir1\\\\\\\\\\Dir2\\\\\\\\Text.txt");

	PrintLineSeparator();

	PrintPathFragments("C:\\Dir\\");

	PrintLineSeparator();

	PrintPathFragments("..");

	PrintLineSeparator();

	PrintPathFragments(".");

	PrintLineSeparator();

	PrintPathFragments(".ext");

	PrintLineSeparator();

	PrintPathFragments("..ext");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	TestPath();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------