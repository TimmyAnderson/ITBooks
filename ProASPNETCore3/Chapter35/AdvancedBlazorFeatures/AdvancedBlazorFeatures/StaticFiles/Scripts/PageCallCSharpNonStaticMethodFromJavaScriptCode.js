//----------------------------------------------------------------------------------------------------------------------
function JSCallNonStaticCSharpMethod(CSharpObject, Value)
{
	// !!!!! Zavola sa NON-STATIC C# METHOD 'IncrementCounterCalledFromJavaScript' pre OBJECT 'CSharpObject'.
	CSharpObject.invokeMethodAsync("IncrementCounterCalledFromJavaScript",Value)
}
//----------------------------------------------------------------------------------------------------------------------