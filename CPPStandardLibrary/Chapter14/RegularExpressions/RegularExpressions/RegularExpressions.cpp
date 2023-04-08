//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <memory>
#include <iostream>
#include <sstream>
#include <regex>
#include <algorithm>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
using namespace std;
using namespace std::regex_constants;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TBidirectionalIterator>
void PrintSubMatch(const wstring& Prefix, match_results<TBidirectionalIterator> MatchResults, const sub_match<TBidirectionalIterator>& SubMatch)
{
	wcout << Prefix;
	wcout << L" MATCHED [";
	wcout << SubMatch.matched;
	wcout << L"] POSITION [";
	wcout << distance(MatchResults[0].first,SubMatch.first);
	wcout << L"] LENGTH [";
	wcout << SubMatch.length();
	wcout << L"] STRING [";
	wcout << SubMatch.str();
	wcout << L"] !";
	wcout << endl;
}
//-----------------------------------------------------------------------------
template<typename TBidirectionalIterator>
void PrintMatchResults(const wstring& String, const wstring& Pattern, const match_results<TBidirectionalIterator>& MatchResults)
{
	using														Size=typename match_results<TBidirectionalIterator>::size_type;

	wcout << L"STRING     [" << String << L"] !" << endl;
	wcout << L"PATTERN    [" << Pattern << L"] !" << endl;

	PrintSubMatch(L"FULL MATCH",MatchResults,MatchResults[0]);

	for(Size Index=1;Index<MatchResults.size();Index++)
	{
		wstringstream											Prefix;

		Prefix << L"SUBMATCH ";
		Prefix << Index;
		
		PrintSubMatch(Prefix.str(),MatchResults,MatchResults[Index]);
	}

	PrintSubMatch(L"UNMATCHED ",MatchResults,MatchResults[MatchResults.size()]);

	PrintSubMatch(L"PREFIX    ",MatchResults,MatchResults.prefix());
	PrintSubMatch(L"SUFIX     ",MatchResults,MatchResults.suffix());
}
//-----------------------------------------------------------------------------
void RegularExpressionMatch(const wstring& String, const wstring& Pattern, match_flag_type Flags=match_default, syntax_option_type Options=ECMAScript)
{
	wregex														RegEx(Pattern,Options);
	wsmatch														Match;
	
	if (regex_match(String,Match,RegEx,Flags)==true)
	{
		PrintMatchResults(String,Pattern,Match);
	}
	else
	{
		wcout << L"REGULAR EXPRESSION MATCHING FAILED !" << endl;
	}
}
//-----------------------------------------------------------------------------
void RegularExpressionSearch(const wstring& String, const wstring& Pattern, match_flag_type Flags=match_default, syntax_option_type Options=ECMAScript)
{
	wregex														RegEx(Pattern,Options);
	wsmatch														Match;
	
	if (regex_search(String,Match,RegEx,Flags)==true)
	{
		PrintMatchResults(String,Pattern,Match);
	}
	else
	{
		wcout << L"REGULAR EXPRESSION SEARCHING FAILED !" << endl;
	}
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSimpleSearch(void)
{
	PrintLineSeparator();

	RegularExpressionSearch(L"AAAABBBAAAABBB",L"((AAAA)(BBB))*");

	PrintLineSeparator();

	// !!! SUBMATCHES NIE SU zaradene do MATCH RESULTS.
	RegularExpressionSearch(L"AAAABBBAAAABBB",L"((AAAA)(BBB))*",match_default,nosubs);

	PrintLineSeparator();

	RegularExpressionSearch(L"AAAABBBAAAABBBAAAA",L"((AAAA)(BBB))*");

	PrintLineSeparator();

	RegularExpressionSearch(L"CCC",L"((AAAA)(BBB))*");

	PrintLineSeparator();

	// !!! Nenajde ZIADEN MATCH.
	RegularExpressionSearch(L"CCCAAAABBBAAAABBBAAAA",L"((AAAA)(BBB))*");

	PrintLineSeparator();

	RegularExpressionSearch(L"CCCAAAABBBAAAABBBAAAA",L"((AAAA)(BBB))");

	PrintLineSeparator();

	// !!! SUBMATCH repreznetuje vyskyt KAZDEJ SUBEXPRESSION v ZATVORKACH () v najdenom MATCH.
	// !!!!! Kedze tento REGULAR EXPRESSION obsahuje 5 SUBEXPRESSIONS v ZATVORKACH (), tak REGULAR EXPRESSION MATCH obsahuje 5 SUBEXPRESSIONS.
	RegularExpressionSearch(L"CCCAAAABBBAAAABBBAAAA",L"((((AAAA)(BBB))))");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestComplexMatch(void)
{
	PrintLineSeparator();

	RegularExpressionMatch(L"<SomeTag>Value</SomeTag>",L"<.*>.*</.*>");

	PrintLineSeparator();

	// MATCH bude uspesny, pretoze sa NEKONTROLUJE, ci OPENING TAG a CLOSING TAG su ROVNAKE.
	RegularExpressionMatch(L"<SomeTag>Value</XXX>",L"<.*>.*</.*>");

	PrintLineSeparator();

	// !!! Vykonava sa kontrola ci OPENING TAG a CLOSING TAG su ROVNAKE.
	// !!! SYNTAX '\1' znamena, ze STRING MUSI byt ROVNAKY ako PRVY SUBMATCH uzatvoreny v ZATVORKACH (), teda [(.*)].
	RegularExpressionMatch(L"<SomeTag>Value</SomeTag>",L"<(.*)>.*</\\1.*>");

	PrintLineSeparator();

	// !!!!! MATCH ZLYHA, pretoze sa KONTROLUJE, ci OPENING TAG a CLOSING TAG su ROVNAKE.
	RegularExpressionMatch(L"<SomeTag>Value</XXX>",L"<(.*)>.*</\\1.*>");

	PrintLineSeparator();

	// !!!!! Pouziva sa GREP GRAMMAR.
	RegularExpressionMatch(L"<SomeTag>Value</SomeTag>",L"<\\(.*\\)>.*</\\1.*>",match_default,grep);

	PrintLineSeparator();

	RegularExpressionMatch(L"111.112.113.114",L"([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRegularExpressionMatch(void)
{
	PrintLineSeparator();

	// MATCH je USPESNY, pretoze CELY STRING je reprezentovany REGULAR EXPRESSION PATTERN.
	RegularExpressionMatch(L"AAAABBBAAAABBB",L"((AAAA)(BBB))*");

	PrintLineSeparator();

	// !!!!! MATCH ZLYHA, pretoze na konci retazca je STRING 'AAAA', ktory NIE JE REPREZENTOVANY REGULAR EXPRESSION PATTERN.
	RegularExpressionMatch(L"AAAABBBAAAABBBAAAA",L"((AAAA)(BBB))*");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRegularExpressionSearch(void)
{
	PrintLineSeparator();

	// SEARCH je USPESNY, pretoze CELY STRING je reprezentovatelny REGULAR EXPRESSION PATTERN.
	RegularExpressionSearch(L"AAAABBBAAAABBB",L"((AAAA)(BBB))*");

	PrintLineSeparator();

	// !!!!! SEARCH je USPESNY, pretoze aj ked STRING 'AAAA' konci retazca NIE SU reprezentovatelne REGULAR EXPRESSION PATTERN, SUBSTRING 'AAAABBBAAAABBB' reprezentovatelny je.
	RegularExpressionSearch(L"AAAABBBAAAABBBAAAA",L"((AAAA)(BBB))*");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRegularExpressionMatchResultsIterationByIndex(void)
{
	PrintLineSeparator();

	using														Size=wsmatch::size_type;

	wregex														RegEx(L"((AAAA)(BBB))");
	wsmatch														MatchResults;
	wstring														Text(L"BEGIN (AAAABBB) END !");

	if (regex_search(Text,MatchResults,RegEx)==true)
	{
		wcout << L"PREFIX  MATCHED [";
		wcout << MatchResults.prefix().matched;
		wcout << L"] POSITION [";
		wcout << distance(MatchResults[0].first,MatchResults.prefix().first);
		wcout << L"] LENGTH [";
		wcout << MatchResults.prefix().length();
		wcout << L"] STRING [";
		wcout << MatchResults.prefix().str();
		wcout << L"] !";
		wcout << endl;

		for(Size Index=0;Index<=MatchResults.size();Index++)
		{
			wcout << L"MATCH " << Index;
			wcout << L" MATCHED [";
			wcout << MatchResults[Index].matched;
			wcout << L"] POSITION [";
			wcout << distance(MatchResults[0].first,MatchResults[Index].first);
			wcout << L"] LENGTH [";
			wcout << MatchResults[Index].length();
			wcout << L"] STRING [";
			wcout << MatchResults[Index].str();
			wcout << L"] !";
			wcout << endl;
		}

		wcout << L"SUFIX   MATCHED [";
		wcout << MatchResults.suffix().matched;
		wcout << L"] POSITION [";
		wcout << distance(MatchResults[0].first,MatchResults.suffix().first);
		wcout << L"] LENGTH [";
		wcout << MatchResults.suffix().length();
		wcout << L"] STRING [";
		wcout << MatchResults.suffix().str();
		wcout << L"] !";
		wcout << endl;
	}
	else
	{
		wcout << L"REGULAR EXPRESSION SEARCHING FAILED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRegularExpressionMatchResultsIterationByIterators(void)
{
	PrintLineSeparator();

	using														Size=wsmatch::size_type;

	wregex														RegEx(L"((AAAA)(BBB))");
	wsmatch														MatchResults;
	wstring														Text(L"BEGIN (AAAABBB) END !");

	if (regex_search(Text,MatchResults,RegEx)==true)
	{
		wcout << L"PREFIX  MATCHED [";
		wcout << MatchResults.prefix().matched;
		wcout << L"] POSITION [";
		wcout << distance(MatchResults[0].first,MatchResults.prefix().first);
		wcout << L"] LENGTH [";
		wcout << MatchResults.prefix().length();
		wcout << L"] STRING [";
		wcout << MatchResults.prefix().str();
		wcout << L"] !";
		wcout << endl;

		Size													Index=0;

		for(sub_match<wstring::const_iterator> SubMatch : MatchResults)
		{
			wcout << L"MATCH " << Index++;
			wcout << L" MATCHED [";
			wcout << SubMatch.matched;
			wcout << L"] POSITION [";
			wcout << distance(MatchResults[0].first,SubMatch.first);
			wcout << L"] LENGTH [";
			wcout << SubMatch.length();
			wcout << L"] STRING [";
			wcout << SubMatch.str();
			wcout << L"] !";
			wcout << endl;
		}

		wcout << L"SUFIX   MATCHED [";
		wcout << MatchResults.suffix().matched;
		wcout << L"] POSITION [";
		wcout << distance(MatchResults[0].first,MatchResults.suffix().first);
		wcout << L"] LENGTH [";
		wcout << MatchResults.suffix().length();
		wcout << L"] STRING [";
		wcout << MatchResults.suffix().str();
		wcout << L"] !";
		wcout << endl;
	}
	else
	{
		wcout << L"REGULAR EXPRESSION SEARCHING FAILED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRegularExpressionMatchResultsFormat(void)
{
	PrintLineSeparator();

	wregex														RegEx(L"((AAAA)(BBB))");
	wsmatch														MatchResults;
	wstring														Text(L"BEGIN (AAAABBB) END !");

	if (regex_search(Text,MatchResults,RegEx)==true)
	{
		// !!! METHOD match_results<TIterator,TAllocator>::format() pouziva SPECIALNU SYNTAX na vytvorenie STRINGU reprezentujuceho jednotlive SUBMATCHES REGULAR EXPRESSION MATCH RESULTS.
		wcout << L"REGULAR EXPRESSION SEARCH RESULT [" << MatchResults.format(L"PREFIX [$`] SUFFIX [$'] FULL MATCH [$&] 1. MATCH [$1] 2. MATCH [$2] 3. MATCH [$3] NON-MATCH [$4]") << L"] !" << endl;
	}
	else
	{
		wcout << L"REGULAR EXPRESSION SEARCHING FAILED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PrintMatch(int& MatchIndex, const wsmatch& Match)
{
	wcout << L"MATCH [" << ++MatchIndex << "]:" << endl;

	int														SubMatchIndex=0;

	for(sub_match<wstring::const_iterator> SubMatch : Match)
	{
		wcout << L"SUBMATCH " << SubMatchIndex++;
		wcout << L" MATCHED [";
		wcout << SubMatch.matched;
		wcout << L"] POSITION [";
		wcout << distance(Match[0].first,SubMatch.first);
		wcout << L"] LENGTH [";
		wcout << SubMatch.length();
		wcout << L"] STRING [";
		wcout << SubMatch.str();
		wcout << L"] !";
		wcout << endl;
	}
}
//-----------------------------------------------------------------------------
void TestRegularExpressionIterators(void)
{
	PrintLineSeparator();

	wregex														RegEx(L"<(.*)>([^>]*)</(\\1)>");
	wstring														Text(L"FIRST <XXX>Value 1</XXX> SECOND <YYY>Value 2</YYY> THIRD <ZZZ>Value 3</ZZZ> !");

	// !!! Vytvori sa BEGIN ITERATOR pre REGULAR EXPRESSION MATCHES.
	wsregex_iterator											BeginIterator1(Text.cbegin(),Text.cend(),RegEx);
	// !!! DEFAULT CONSTRUCTOR vytvara END ITERATOR.
	wsregex_iterator											EndIterator1;

	int															MatchIndex1=0;

	// !!!!! Prechadzaju sa VSETKY MATCHES v CELOM STRINGU.
	for(;BeginIterator1!=EndIterator1;BeginIterator1++)
	{
		wcout << L"MATCH [" << ++MatchIndex1 << "]:" << endl;

		int														SubMatchIndex=0;

		for(sub_match<wstring::const_iterator> SubMatch : *BeginIterator1)
		{
			wcout << L"SUBMATCH " << SubMatchIndex++;
			wcout << L" MATCHED [";
			wcout << SubMatch.matched;
			wcout << L"] POSITION [";
			wcout << distance((*BeginIterator1)[0].first,SubMatch.first);
			wcout << L"] LENGTH [";
			wcout << SubMatch.length();
			wcout << L"] STRING [";
			wcout << SubMatch.str();
			wcout << L"] !";
			wcout << endl;
		}
	}

	PrintLineSeparator();

	// !!! Vytvori sa BEGIN ITERATOR pre REGULAR EXPRESSION MATCHES.
	wsregex_iterator											BeginIterator2(Text.cbegin(),Text.cend(),RegEx);
	// !!! DEFAULT CONSTRUCTOR vytvara END ITERATOR.
	wsregex_iterator											EndIterator2;

	int															MatchIndex2=0;

	// !!!!! Prechadzaju sa VSETKY MATCHES v CELOM STRINGU pomocou ALGORITHM.
	for_each(BeginIterator2,EndIterator2,[&MatchIndex2](const wsmatch& Match)->void{PrintMatch(MatchIndex2,Match);});

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PrintIteratorSubMatch(int& SubMatchIndex, const sub_match<wstring::const_iterator>& SubMatch)
{
	wcout << L"SUBMATCH " << SubMatchIndex++;
	wcout << L" MATCHED [";
	wcout << SubMatch.matched;
	wcout << L"] LENGTH [";
	wcout << SubMatch.length();
	wcout << L"] STRING [";
	wcout << SubMatch.str();
	wcout << L"] !";
	wcout << endl;
}
//-----------------------------------------------------------------------------
void TestRegularExpressionTokenIterators(void)
{
	PrintLineSeparator();

	wregex														RegEx(L"<(.*)>([^>]*)</(\\1)>");
	wstring														Text(L"111<XXX>Value 1</XXX>2222<YYY>Value 2</YYY>33333<ZZZ>Value 3</ZZZ>444444");

	// !!! Vytvori sa BEGIN ITERATOR pre REGULAR EXPRESSION SUBMATCHES.
	// !!!!! ITERATOR bude prechadzat NON-MATCHES, FULL MATCHES a 1., 2. a 3. SUBMATCHES.
	wsregex_token_iterator										BeginIterator1(Text.cbegin(),Text.cend(),RegEx,{-1,0,1,2,3});
	// !!! DEFAULT CONSTRUCTOR vytvara END ITERATOR.
	wsregex_token_iterator										EndIterator1;

	int															MatchIndex1=0;

	for_each(BeginIterator1,EndIterator1,[&MatchIndex1](const sub_match<wstring::const_iterator>& SubMatch)->void{PrintIteratorSubMatch(MatchIndex1,SubMatch);});

	PrintLineSeparator();

	// !!! Vytvori sa BEGIN ITERATOR pre REGULAR EXPRESSION SUBMATCHES.
	// !!!!! ITERATOR bude prechadzat 3., 2. a 1. SUBMATCHES, FULL MATCHES a NON-MATCHES.
	wsregex_token_iterator										BeginIterator2(Text.cbegin(),Text.cend(),RegEx,{3,2,1,0,-1});
	// !!! DEFAULT CONSTRUCTOR vytvara END ITERATOR.
	wsregex_token_iterator										EndIterator2;

	int															MatchIndex2=0;

	for_each(BeginIterator2,EndIterator2,[&MatchIndex2](const sub_match<wstring::const_iterator>& SubMatch)->void{PrintIteratorSubMatch(MatchIndex2,SubMatch);});

	PrintLineSeparator();

	// !!! Vytvori sa BEGIN ITERATOR pre REGULAR EXPRESSION SUBMATCHES.
	// !!!!! ITERATOR bude prechadzat IBA cez NON-MATCHES.
	wsregex_token_iterator										BeginIterator3(Text.cbegin(),Text.cend(),RegEx,{-1});
	// !!! DEFAULT CONSTRUCTOR vytvara END ITERATOR.
	wsregex_token_iterator										EndIterator3;

	int															MatchIndex3=0;

	for_each(BeginIterator3,EndIterator3,[&MatchIndex3](const sub_match<wstring::const_iterator>& SubMatch)->void{PrintIteratorSubMatch(MatchIndex3,SubMatch);});

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRegularExpressionTokenizer(void)
{
	PrintLineSeparator();

	// !!!!! REGULAR EXPRESSION definuje TOKEN SEPARATOR.
	wregex														RegEx(L"[ \t\n]*[,][ \t\n]*");
	wstring														Text(L"100, 200 , 300,400,   500  ,   600");

	wcout << L"ORIGINAL STRING [" << Text << L"] !" << endl;

	// !!! Vytvori sa BEGIN ITERATOR pre REGULAR EXPRESSION SUBMATCHES.
	// !!!!! ITERATOR bude prechadzat IBA cez NON-MATCHES.
	wsregex_token_iterator										BeginIterator(Text.cbegin(),Text.cend(),RegEx,{-1});
	// !!! DEFAULT CONSTRUCTOR vytvara END ITERATOR.
	wsregex_token_iterator										EndIterator;

	wcout << L"TOKENIZED STRING:" << endl;

	int															MatchIndex=0;

	for_each(BeginIterator,EndIterator,[&MatchIndex](const sub_match<wstring::const_iterator>& SubMatch)->void{PrintIteratorSubMatch(MatchIndex,SubMatch);});

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRegularExpressionReplace(void)
{
	PrintLineSeparator();

	wregex														RegEx(L"<(.*)>([^>]*)</(\\1)>");
	wstring														Text(L"111<XXX>Value 1</XXX>2222<YYY>Value 2</YYY>33333<ZZZ>Value 3</ZZZ>444444");
	// !!! SYNTAX [$X] znamena nahradenie STRING za X. SUBMATCH, ktory bol v povodnom STRING najdeny.
	wstring														Replacement=L"<$1 value=\"$2\"/>";

	wcout << L"ORIGINAL STRING [" << Text << L"] !" << endl;
	
	wstring														Result1=regex_replace(Text,RegEx,Replacement);

	wcout << L"RESULT          [" << Result1 << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"ORIGINAL STRING [" << Text << L"] !" << endl;

	// NON-MATCHED CHARCTERS nebudu kopirovane do RESULT STRING.
	wstring														Result2=regex_replace(Text,RegEx,Replacement,format_no_copy);

	wcout << L"RESULT          [" << Result2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRegularExpressionFlags(void)
{
	PrintLineSeparator();

	wregex														RegEx1(L"<(.*)>([^>]*)</(\\1)>");
	// Pouziva sa CASE-INSENSITIVE MATCHING.
	wregex														RegEx2(L"<(.*)>([^>]*)</(\\1)>",icase);
	wstring														Text1(L"111<XXX>Value 1</XXX>2222<YYY>Value 2</YYY>33333<ZZZ>Value 3</ZZZ>444444");
	wstring														Text2(L"111<XXX>Value 1</xxx>2222<YYY>Value 2</yyy>33333<ZZZ>Value 3</zzz>444444");
	// !!! SYNTAX [$X] znamena nahradenie STRING za X. SUBMATCH, ktory bol v povodnom STRING najdeny.
	wstring														Replacement=L"<$1 value=\"$2\"/>";

	wcout << L"ORIGINAL STRING [" << Text1 << L"] !" << endl;

	wstring														Result1=regex_replace(Text1,RegEx1,Replacement);

	wcout << L"RESULT          [" << Result1 << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"ORIGINAL STRING [" << Text2 << L"] !" << endl;

	// !!!!! REGULAR EXPRESSION MATCHING ZLYHA, pretoze sa pouziva CASE-SENSITIVE MATCHING.
	wstring														Result2=regex_replace(Text2,RegEx1,Replacement);

	wcout << L"RESULT          [" << Result2 << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"ORIGINAL STRING [" << Text2 << L"] !" << endl;

	// !!!!! REGULAR EXPRESSION MATCHING PREBEHNE USPESNE, pretoze sa pouziva CASE-INSENSITIVE MATCHING.
	wstring														Result3=regex_replace(Text2,RegEx2,Replacement);

	wcout << L"RESULT          [" << Result3 << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"ORIGINAL STRING [" << Text1 << L"] !" << endl;

	// NON-MATCHED CHARCTERS nebudu kopirovane do RESULT STRING.
	wstring														Result4=regex_replace(Text1,RegEx1,Replacement,format_no_copy);

	wcout << L"RESULT          [" << Result4 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRegularExpressionDifferentStrings(void)
{
	PrintLineSeparator();

	regex														RegEx1("<(.*)>([^>]*)</(\\1)>");
	char														Replacement1[]={"<$1 value=\"$2\"/>"};
	char														InputText1[]{"111<XXX>Value 1</XXX>2222<YYY>Value 2</YYY>33333<ZZZ>Value 3</ZZZ>444444"};
	char														OutputText1[1000];

	wcout << L"ORIGINAL STRING [" << ConvertStringToWideString(InputText1) << L"] !" << endl;

	// STRING je zadany ako C-STRING.
	// !!! RETURN VALUE obsahuje END ITERATOR REPLACED C-STRING.
	char*														Result1=regex_replace(OutputText1,InputText1,InputText1+(sizeof(InputText1)/sizeof(char)),RegEx1,Replacement1);

	// !!! Do END ITERATOR je NUTNE zapisat znak '\0', ak sa ma C-STRING spravne zobrazit.
	*Result1='\0';

	wcout << L"REPLACED STRING [" << ConvertStringToWideString(OutputText1) << L"] !" << endl;

	PrintLineSeparator();

	wregex														RegEx2(L"<(.*)>([^>]*)</(\\1)>");
	wchar_t														Replacement2[]={L"<$1 value=\"$2\"/>"};
	wchar_t														InputText2[]{L"111<XXX>Value 1</XXX>2222<YYY>Value 2</YYY>33333<ZZZ>Value 3</ZZZ>444444"};
	wchar_t														OutputText2[1000];

	wcout << L"ORIGINAL STRING [" << InputText2 << L"] !" << endl;

	// STRING je zadany ako WC-STRING.
	// !!! RETURN VALUE obsahuje END ITERATOR REPLACED WC-STRING.
	wchar_t*													Result2=regex_replace(OutputText2,InputText2,InputText2+(sizeof(InputText2)/sizeof(char)),RegEx2,Replacement2);

	// !!! Do END ITERATOR je NUTNE zapisat znak '\0', ak sa ma WC-STRING spravne zobrazit.
	*Result2=L'\0';

	wcout << L"REPLACED STRING [" << OutputText2 << L"] !" << endl;

	PrintLineSeparator();

	regex														RegEx3("<(.*)>([^>]*)</(\\1)>");
	string														Replacement3("<$1 value=\"$2\"/>");
	string														InputText3("111<XXX>Value 1</XXX>2222<YYY>Value 2</YYY>33333<ZZZ>Value 3</ZZZ>444444");

	wcout << L"ORIGINAL STRING [" << ConvertStringToWideString(InputText3) << L"] !" << endl;

	// STRING je zadany ako [string].
	string														OutputText3=regex_replace(InputText3,RegEx3,Replacement3);

	wcout << L"REPLACED STRING [" << ConvertStringToWideString(OutputText3) << L"] !" << endl;

	PrintLineSeparator();

	wregex														RegEx4(L"<(.*)>([^>]*)</(\\1)>");
	wstring														Replacement4(L"<$1 value=\"$2\"/>");
	wstring														InputText4(L"111<XXX>Value 1</XXX>2222<YYY>Value 2</YYY>33333<ZZZ>Value 3</ZZZ>444444");

	wcout << L"ORIGINAL STRING [" << InputText4 << L"] !" << endl;

	// STRING je zadany ako [wstring].
	wstring														OutputText4=regex_replace(InputText4,RegEx4,Replacement4);

	wcout << L"REPLACED STRING [" << OutputText4 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
wstring GetRegularExceptionString(const regex_error& Error)
{
	if (Error.code()==error_collate)
	{
		return(L"The expression contains an invalid collating element name !");
	}
	else if (Error.code()==error_ctype)
	{
		return(L"The expression contains an invalid character class name !");
	}
	else if (Error.code()==error_escape)
	{
		return(L"The expression contains an invalid escaped character or a trailing escape !");
	}
	else if (Error.code()==error_backref)
	{
		return(L"The expression contains an invalid back reference !");
	}
	else if (Error.code()==error_brack)
	{
		return(L"The expression contains mismatched square brackets ('[' and ']') !");
	}
	else if (Error.code()==error_paren)
	{
		return(L"The expression contains mismatched parentheses ('(' and ')') !");
	}
	else if (Error.code()==error_brace)
	{
		return(L"The expression contains mismatched curly braces ('{' and '}') !");
	}
	else if (Error.code()==error_badbrace)
	{
		return(L"The expression contains an invalid range in a {} expression !");
	}
	else if (Error.code()==error_range)
	{
		return(L"The expression contains an invalid character range (e.g. [b-a]) !");
	}
	else if (Error.code()==error_space)
	{
		return(L"There was not enough memory to convert the expression into a finite state machine !");
	}
	else if (Error.code()==error_badrepeat)
	{
		return(L"One of *?+{ was not preceded by a valid regular expression !");
	}
	else if (Error.code()==error_complexity)
	{
		return(L"The complexity of an attempted match exceeded a predefined level !");
	}
	else if (Error.code()==error_stack)
	{
		return(L"There was not enough memory to perform a match !");
	}
	else
	{
		return(L"UNKNOWN EXCEPTION !");
	}
}
//-----------------------------------------------------------------------------
void TestRegularExpressionErrors(void)
{
	PrintLineSeparator();

	try
	{
		// Korektny REGULAR EXPRESSION.
		wregex													RegEx(L"<(.*)>([^>]*)</(\\1)>");

		wcout << L"REGULAR EXPRESSION PARSED ! MARK COUNT [" << RegEx.mark_count() << L"] !" << endl;
	}
	catch(const regex_error& Error)
	{
		wcout << L"EXCEPTION [" << GetRegularExceptionString(Error) << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! Chybny pocet zatvoriek ().
		wregex													RegEx(L"<(.*)>([^>]*)</(\\1>");

		wcout << L"REGULAR EXPRESSION PARSED ! MARK COUNT [" << RegEx.mark_count() << L"] !" << endl;
	}
	catch(const regex_error& Error)
	{
		wcout << L"EXCEPTION [" << GetRegularExceptionString(Error) << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! Chybny pocet zatvoriek [].
		wregex													RegEx(L"<(.*)>([^>]]*)</(\\1)>");

		wcout << L"REGULAR EXPRESSION PARSED ! MARK COUNT [" << RegEx.mark_count() << L"] !" << endl;
	}
	catch(const regex_error& Error)
	{
		wcout << L"EXCEPTION [" << GetRegularExceptionString(Error) << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! Chybny BACK REFERENCE.
		wregex													RegEx(L"<(.*)>([^>]*)</(\\15)>");

		wcout << L"REGULAR EXPRESSION PARSED ! MARK COUNT [" << RegEx.mark_count() << L"] !" << endl;
	}
	catch(const regex_error& Error)
	{
		wcout << L"EXCEPTION [" << GetRegularExceptionString(Error) << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! Chybna ESCAPE SEQUENCE.
		wregex													RegEx(L"<(.*)>([^>]*)</(\\");

		wcout << L"REGULAR EXPRESSION PARSED ! MARK COUNT [" << RegEx.mark_count() << L"] !" << endl;
	}
	catch(const regex_error& Error)
	{
		wcout << L"EXCEPTION [" << GetRegularExceptionString(Error) << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// Chybny RANGE.
		wregex													RegEx(L"<(.*)>([^>]{100,2}*)</(\\1)>");

		wcout << L"REGULAR EXPRESSION PARSED ! MARK COUNT [" << RegEx.mark_count() << L"] !" << endl;
	}
	catch(const regex_error& Error)
	{
		wcout << L"EXCEPTION [" << GetRegularExceptionString(Error) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRegularExpressionTraits(void)
{
	PrintLineSeparator();

	regex_traits<wchar_t>										Traits;
	wchar_t														Text[]{L"Timmy Anderson"};

	wcout << L"LENGTH [" << regex_traits<wchar_t>::length(Text) << L"] !" << endl;

	wcout << L"TRANSLATE [" << Traits.translate(L'C') << L"] !" << endl;
	wcout << L"TRANSFORM [" << Traits.transform(Text,Text+(sizeof(Text)/sizeof(wchar_t))-1) << L"] !" << endl;
	wcout << L"VALUE [" << Traits.value(L'8',10) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestSimpleSearch();
	//TestComplexMatch();
	//TestRegularExpressionMatch();
	//TestRegularExpressionSearch();
	//TestRegularExpressionMatchResultsIterationByIndex();
	//TestRegularExpressionMatchResultsIterationByIterators();
	//TestRegularExpressionMatchResultsFormat();
	//TestRegularExpressionIterators();
	//TestRegularExpressionTokenIterators();
	//TestRegularExpressionTokenizer();
	//TestRegularExpressionReplace();
	//TestRegularExpressionFlags();
	//TestRegularExpressionDifferentStrings();
	TestRegularExpressionTraits();
	//TestRegularExpressionErrors();
	
	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------