//----------------------------------------------------------------------------------------------------------------------
function JSIncrementCounter(Value)
{
	Value++;

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
function JSShowAlert(Text)
{
	alert("MESSAGE from C# [" + Text + "] !");
}
//----------------------------------------------------------------------------------------------------------------------
function JSSetElementText(Element, Text)
{
	Element.innerText="MESSAGE from C# [" + Text + "] !";
}
//----------------------------------------------------------------------------------------------------------------------