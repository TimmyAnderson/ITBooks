//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
class CClass
{
//-------------------------------------------------------------------------------------------------------
	private:
		wstring													MField1;
		wstring													MField2;
		wstring													MField3;
		wstring													MField4;

	public:
		void TestLambdaExpressionsWithOuterScope1(void)
		{
			wstring												Value1=L"DEFAULT";
			wstring												Value2=L"DEFAULT";

			auto												Lambda=[Value1,&Value2,this]
			{
				std::wcout << L"VALUE 1 [" << Value1 << L"] !" << std::endl;
				std::wcout << L"VALUE 2 [" << Value2 << L"] !" << std::endl;
				std::wcout << L"FIELD 1 [" << MField1 << L"] !" << std::endl;

				// COMPILER hodi ERROR, pretoze NIE je mozne zapisovat do VARIABLE prenesenej BY-VALUE.
				//Value1=L"CHANGED in LAMBDA EXPRESSION";

				// Tento CODE prebehne OK, pretoze do VARIABLE prenesenej BY-REFERENCE je mozne zapisovat.
				Value2=L"CHANGED in LAMBDA EXPRESSION";

				// Tento CODE prebehne OK, pretoze do FIELDS THIS VARIABLE prenesenej BY-VALUE je mozne zapisovat.
				MField1=L"CHANGED in LAMBDA EXPRESSION";

				std::wcout << L"VALUE 2 [" << Value2 << L"] !" << std::endl;
				std::wcout << L"FIELD 1 [" << MField1 << L"] !" << std::endl;
			};

			Value1=L"CHANGED in METHOD";
			Value2=L"CHANGED in METHOD";
			MField1=L"CHANGED in METHOD";

			// !!!!! Kedze VARIABLE [Value1] sa prenasa BY-VALUE, jej hodnota sa prenasa v case DEFINICIE LAMBDA EXPRESSION.
			// !!!!! Kedze VARIABLE [Value2] sa prenasa BY-REFERENCE, jej hodnota sa prenasa v case VOLANIA LAMBDA EXPRESSION.
			Lambda();

			PrintLineSeparator();

			// !!! Hodnota [Value1] bude NEZMENENA, pretoze sa preniesla BY-VALUE a tym padom NEMOHLA byt modifikovana v LAMBDA FUNCTION.
			std::wcout << L"VALUE 1 [" << Value1 << L"] !" << std::endl;
			// !!! Hodnota [Value2] bude ZMENENA, pretoze sa preniesla BY-REFERENCE a bola zmenena v LAMBDA FUNCTION.
			std::wcout << L"VALUE 2 [" << Value2 << L"] !" << std::endl;
			std::wcout << L"FIELD 1 [" << MField1 << L"] !" << std::endl;
		}

		void TestLambdaExpressionsWithOuterScope2(void)
		{
			wstring												Value1=L"DEFAULT";
			wstring												Value2=L"DEFAULT";

			// !!! VSETKY LOCAL VARIABLES su prenesene BY-VALUE.
			auto												Lambda=[=]
			{
				std::wcout << L"VALUE 1 [" << Value1 << L"] !" << std::endl;
				std::wcout << L"VALUE 2 [" << Value2 << L"] !" << std::endl;
				std::wcout << L"FIELD 2 [" << MField2 << L"] !" << std::endl;

				// COMPILER hodi ERROR, pretoze NIE je mozne zapisovat do VARIABLE prenesenej BY-VALUE.
				//Value1=L"CHANGED in LAMBDA EXPRESSION";

				// COMPILER hodi ERROR, pretoze NIE je mozne zapisovat do VARIABLE prenesenej BY-VALUE.
				//Value2=L"CHANGED in LAMBDA EXPRESSION";

				// Tento CODE prebehne OK, pretoze do FIELDS THIS VARIABLE prenesenej BY-VALUE je mozne zapisovat.
				MField1=L"CHANGED in LAMBDA EXPRESSION";

				std::wcout << L"VALUE 2 [" << Value2 << L"] !" << std::endl;
				std::wcout << L"FIELD 2 [" << MField2 << L"] !" << std::endl;
			};

			Value1=L"CHANGED in METHOD";
			Value2=L"CHANGED in METHOD";
			MField2=L"CHANGED in METHOD";

			// !!!!! Kedze VARIABLE [Value1] sa prenasa BY-VALUE, jej hodnota sa prenasa v case DEFINICIE LAMBDA EXPRESSION.
			// !!!!! Kedze VARIABLE [Value2] sa prenasa BY-VALUE, jej hodnota sa prenasa v case DEFINICIE LAMBDA EXPRESSION.
			Lambda();

			PrintLineSeparator();

			// !!! Hodnota [Value1] bude NEZMENENA, pretoze sa preniesla BY-VALUE a tym padom NEMOHLA byt modifikovana v LAMBDA FUNCTION.
			std::wcout << L"VALUE 1 [" << Value1 << L"] !" << std::endl;
			// !!! Hodnota [Value2] bude NEZMENENA, pretoze sa preniesla BY-VALUE a tym padom NEMOHLA byt modifikovana v LAMBDA FUNCTION.
			std::wcout << L"VALUE 2 [" << Value2 << L"] !" << std::endl;
			std::wcout << L"FIELD 2 [" << MField2 << L"] !" << std::endl;
		}

		void TestLambdaExpressionsWithOuterScope3(void)
		{
			wstring												Value1=L"DEFAULT";
			wstring												Value2=L"DEFAULT";

			// !!! VSETKY LOCAL VARIABLES su prenesene BY-REFERENCE.
			auto												Lambda=[&]
			{
				std::wcout << L"VALUE 1 [" << Value1 << L"] !" << std::endl;
				std::wcout << L"VALUE 2 [" << Value2 << L"] !" << std::endl;
				std::wcout << L"FIELD 3 [" << MField3 << L"] !" << std::endl;

				// Tento CODE prebehne OK, pretoze do VARIABLE prenesenej BY-REFERENCE je mozne zapisovat.
				Value1=L"CHANGED in LAMBDA EXPRESSION";

				// Tento CODE prebehne OK, pretoze do VARIABLE prenesenej BY-REFERENCE je mozne zapisovat.
				Value2=L"CHANGED in LAMBDA EXPRESSION";

				// Tento CODE prebehne OK, pretoze do FIELDS THIS VARIABLE prenesenej BY-VALUE je mozne zapisovat.
				MField3=L"CHANGED in LAMBDA EXPRESSION";

				std::wcout << L"VALUE 2 [" << Value2 << L"] !" << std::endl;
				std::wcout << L"FIELD 3 [" << MField3 << L"] !" << std::endl;
			};

			Value1=L"CHANGED in METHOD";
			Value2=L"CHANGED in METHOD";
			MField3=L"CHANGED in METHOD";

			// !!!!! Kedze VARIABLE [Value1] sa prenasa BY-REFERENCE, jej hodnota sa prenasa v case VOLANIA LAMBDA EXPRESSION.
			// !!!!! Kedze VARIABLE [Value2] sa prenasa BY-REFERENCE, jej hodnota sa prenasa v case VOLANIA LAMBDA EXPRESSION.
			Lambda();

			PrintLineSeparator();

			// !!! Hodnota [Value1] bude ZMENENA, pretoze sa preniesla BY-REFERENCE a bola zmenena v LAMBDA FUNCTION.
			std::wcout << L"VALUE 1 [" << Value1 << L"] !" << std::endl;
			// !!! Hodnota [Value2] bude ZMENENA, pretoze sa preniesla BY-REFERENCE a bola zmenena v LAMBDA FUNCTION.
			std::wcout << L"VALUE 2 [" << Value2 << L"] !" << std::endl;
			std::wcout << L"FIELD 3 [" << MField3 << L"] !" << std::endl;
		}

		void TestLambdaExpressionsWithOuterScope4(void)
		{
			// !!! VSETKY LOCAL VARIABLES su prenesene BY-REFERENCE.
			auto												Lambda=[]
			{
				// !!! FIELDS NIE su PRISTUPNE, pretoze sa NEPOUZIL KEYWORD [this].
				//std::wcout << L"FIELD 4 [" << << L"] !" << std::endl;,MField4.c_str());

				std::wcout << L"LAMBDA FUNCTION CALLED !" << std::endl;
			};

			MField4=L"CHANGED in METHOD";

			// !!!!! Kedze VARIABLE [Value1] sa prenasa BY-REFERENCE, jej hodnota sa prenasa v case VOLANIA LAMBDA EXPRESSION.
			// !!!!! Kedze VARIABLE [Value2] sa prenasa BY-REFERENCE, jej hodnota sa prenasa v case VOLANIA LAMBDA EXPRESSION.
			Lambda();

			std::wcout << L"FIELD 4 [" << MField4 << L"] !" << std::endl;
		}

	public:
		CClass(void)
		{
			MField1=L"DEFAULT";
			MField2=L"DEFAULT";
			MField3=L"DEFAULT";
			MField4=L"DEFAULT";
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------