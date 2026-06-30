package my.example.Components.InsidePackage;
//----------------------------------------------------------------------------------------------------------------------
import my.example.Components.Annotations.IMyCustomComponentAnnotation;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! BEAN COMPONENT pouziva CUSTOM ANNOTATION.
@IMyCustomComponentAnnotation
public class CComponentWithCustomAnnotation
{
//----------------------------------------------------------------------------------------------------------------------
	public void Print()
	{
		System.out.print("This is COMPONENT [COMPONENT WITH CUSTOM ANNOTATION].\n");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------