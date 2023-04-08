//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "Int.h"
//-------------------------------------------------------------------------------------------------------
// !!!!! Tato trieda ma PRETAZENY OPERATOR() a sluzi ako WRAPPER okolo volania FUNKCIE. Nieco ako DELEGATE v C#.
class CIntAdditionFunction
{
	private:
		// !!! KONTEXTOVE PARAMETRE sa podobaju LOKALNYM PREMENNYM PARENT funkcie na ktorej sa ANONYMNA FUNKCIA v C# moze odkazovat.
		bool													MAddOrRemove;
		int														MValue;

	public:
		// !!!!! Tento OPERATOR bude volat for_each().
		int operator()(CInt& Value);

	public:
		CIntAdditionFunction(bool AddOrRemove, int Value);
		virtual ~CIntAdditionFunction(void);
};
//-------------------------------------------------------------------------------------------------------