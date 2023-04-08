//----------------------------------------------------------------------------------------------------------------------
function JSCallStaticCSharpMethod(Value)
{
	// !!!!! Zavola sa STATIC C# METHOD 'IncrementCounterCalledFromJavaScript' v ASSEMBLY 'AdvancedBlazorFeatures'.
	DotNet.invokeMethodAsync("AdvancedBlazorFeatures", "IncrementCounterCalledFromJavaScript",Value)
}
//----------------------------------------------------------------------------------------------------------------------