//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "MyText.h"
//-------------------------------------------------------------------------------------------------------
union USomeUnion
{
	int															MIntValue;
	double														MDoubleValue;

	// !!! V UNIONS nie je mozne pouzit CLASS VARIABLES, lebo C++ by nevedelo ci je platna hodnota prave hodnota CLASS TYPU a teda ci ma pre nu volat CONSTRUCTOR a DESTRUCTOR.
	//CMyText													MText;

	void Print(void);
};
//-------------------------------------------------------------------------------------------------------