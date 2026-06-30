package my.example.InjectionTypes;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CInjectionTypesFieldInjection
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! FIELD MUSI byt oznaceny pomocou ANNOTATION [@Autowired].
	@Autowired
	private CInjectionTypesBean									bean;
	
	// !!!!! FIELD INJECTION NEFUNGUJE na STATIC FIELDS.
	@Autowired
	private static CInjectionTypesBean							staticBean;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		String													Text=bean.Print();
		
		System.out.printf("FIELD INJECTION - BEAN [%s].\n",Text);
	}	
//----------------------------------------------------------------------------------------------------------------------
	public void TestStatic()
	{
		if (staticBean!=null)
		{
			String												Text=staticBean.Print();
		
			System.out.printf("STATIC FIELD INJECTION - BEAN [%s].\n",Text);
		}
		else
		{
			System.out.printf("!!!!! STATIC FIELD INJECTION - DOESN'T WORK.\n");
		}
	}	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------