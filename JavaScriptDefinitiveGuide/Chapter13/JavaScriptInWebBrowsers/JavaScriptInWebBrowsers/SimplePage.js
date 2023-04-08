//-------------------------------------------------------------------------------------------------------
function MyClick()
{
	var															NewElement=window.document.createTextNode("Hello World !!!");
    var															MyParagraph=window.document.getElementById("MyParagraph");
         
    MyParagraph.style.backgroundColor="green";

	MyParagraph.appendChild(NewElement);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
function TestFunction1()
{
	// !!! Priame vyuzitie GLOBALNEHO OBJECTU 'Window'.
    document.write("<p>VALUE location: [" + location + "] !</p>");
	// !!! Priame vyuzitie GLOBALNEHO OBJECTU 'Window' cez PROPERTY 'window'.
    document.write("<p>VALUE window.location: [" + window.location + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction2()
{
	window.alert("Hello WORLD !");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction3()
{
	var															MyParagraph=window.document.getElementById("MyParagraph");
	var															NewElement=window.document.createTextNode("Hello World !!!");

	MyParagraph.style.backgroundColor="red";

	MyParagraph.appendChild(NewElement);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//TestFunction1();
//TestFunction2();
TestFunction3();
//-------------------------------------------------------------------------------------------------------