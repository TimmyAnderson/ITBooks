package my.example.OutsidePackage;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! BEAN COMPONENT nie je zavedeny do BEAN CONTAINER, pretoze sa nenachadza v APPLICATION PACKAGE ani v jeho CHILD PACKAGES.
@Component
public class COutsidePackageComponent
{
//----------------------------------------------------------------------------------------------------------------------
	public void Print()
	{
		System.out.print("This is COMPONENT [OUTSIDE PACKAGE].\n");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------