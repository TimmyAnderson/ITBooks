//-------------------------------------------------------------------------------------------------------
// FILE musi byt spusteny z COMMAND PROMPT prikazom [Node.exe NodeTest.js].
//-------------------------------------------------------------------------------------------------------
function TestFunction1()
{
	console.log("Hello NODE !");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction2()
{
	console.log("Hello NODE !");

	var															Callback=function()
	{
		console.log("PROCESS has EXITED !");
	};

	// !!! Zavesim CALLBACK na PROCESS EXIST.
	process.on("exit",Callback);
}
//-------------------------------------------------------------------------------------------------------
function TestFunction3()
{
	// !!! Vytvori sa FILE STREAM.
	var															FS=require("fs");

	// !!! SYNCHRONNE sa nacita obsah FILE.
	var															Text=FS.readFileSync("SimpleTextFile.txt");
	
	console.log("TEXT from FILE: [" + Text + "] !");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction4()
{
	// !!! Vytvori sa FILE STREAM.
	var															FS=require("fs");

	var															Callback=function(Error,Data)
	{
		if (Error)
		{
			console.log("TEXT from FILE: [" + Error + "] !");
		}
		else
		{
			console.log("ASYNCHRONOUS - TEXT from FILE: [" + Data + "] !");
		}
	};

	// !!! ASYNCHRONNE sa nacita obsah FILE.
	FS.readFile("SimpleTextFile.txt",Callback);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//TestFunction1();
//TestFunction2();
//TestFunction3();
TestFunction4();
//-------------------------------------------------------------------------------------------------------