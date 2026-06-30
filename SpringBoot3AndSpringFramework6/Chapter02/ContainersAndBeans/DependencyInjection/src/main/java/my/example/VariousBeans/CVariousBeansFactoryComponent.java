package my.example.VariousBeans;
//----------------------------------------------------------------------------------------------------------------------
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CVariousBeansFactoryComponent
{
//----------------------------------------------------------------------------------------------------------------------
	private final String										component1;
	private final String[]										component2;
	private final List<String>									component3;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CVariousBeansFactoryComponent(String component1, String[] component2, List<String> component3)
	{
		System.out.printf("BEAN [CVariousBeansFactoryComponent] CREATING.\n");
		
		this.component1=component1;
		this.component2=component2;
		this.component3=component3;
		
		System.out.printf("BEAN [CVariousBeansFactoryComponent] CREATED.\n");
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		System.out.printf("COMPONENT - String - BEAN VALUE [%s].\n",component1);
		
		for(int Index=0;Index<component2.length;Index++)
		{
			String												value=component2[Index];
			
			System.out.printf("COMPONENT - String[] - BEAN VALUE [%s].\n",value);
		}
		
		for(int Index=0;Index<component3.size();Index++)
		{
			String												value=component3.get(Index);
			
			System.out.printf("COMPONENT - List<String> - BEAN VALUE [%s].\n",value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------