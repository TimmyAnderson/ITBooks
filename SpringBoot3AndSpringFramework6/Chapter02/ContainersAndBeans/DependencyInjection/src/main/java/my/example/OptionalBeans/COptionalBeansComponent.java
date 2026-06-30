package my.example.OptionalBeans;
//----------------------------------------------------------------------------------------------------------------------
import jakarta.annotation.Nullable;

import java.util.Optional;

import org.springframework.beans.factory.ObjectProvider;
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class COptionalBeansComponent
{
//----------------------------------------------------------------------------------------------------------------------
	private final COptionalBeansBean							bean;
	// !!!!! CLASSES NIE SU BEAN.
	private final COptionalBeansNotBean							notBean1;
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	@Nullable
	private COptionalBeansNotBean								notBean2;
	private Optional<COptionalBeansNotBean>						notBean3;
	// !!! CLASS [ObjectProvider] implementuje LAZY LOADING.
	private ObjectProvider<COptionalBeansNotBean>				notBean4;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! ANNOTATION [@Autowired] moze byt aplikovana aj na PARAMETERS.
	// !!!!! Nastavenie PARAMETER [required] na VALUE [false] robi BEAN OPTIONAL.
	@Autowired
	public COptionalBeansComponent(COptionalBeansBean bean, @Autowired(required=false) COptionalBeansNotBean notBean1)
	{
		this.bean=bean;
		this.notBean1=notBean1;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	private void MySetter(Optional<COptionalBeansNotBean> notBean3, ObjectProvider<COptionalBeansNotBean> notBean4)
	{
		System.out.printf("SETTER is CALLED.\n");
		
		this.notBean3=notBean3;
		this.notBean4=notBean4;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		String													TextBean=bean.Print();
		
		System.out.printf("OPTIONAL BEANS - BEAN [%s].\n",TextBean);
		
		if (notBean1!=null)
		{
			String												TextNotBean=notBean1.Print();
		
			System.out.printf("OPTIONAL BEANS - NOT BEAN 1 [%s].\n",TextNotBean);
		}
		else
		{
			System.out.printf("!!!!! OPTIONAL BEANS - NOT BEAN 1 DOESN'T EXIST.\n");
		}
		
		if (notBean2!=null)
		{
			String												TextNotBean=notBean2.Print();
		
			System.out.printf("OPTIONAL BEANS - NOT BEAN 2 [%s].\n",TextNotBean);
		}
		else
		{
			System.out.printf("!!!!! OPTIONAL BEANS - NOT BEAN 2 DOESN'T EXIST.\n");
		}
		
		if (notBean3.isPresent()==true)
		{
			String												TextNotBean=notBean3.get().Print();
		
			System.out.printf("OPTIONAL BEANS - NOT BEAN 3 [%s].\n",TextNotBean);
		}
		else
		{
			System.out.printf("!!!!! OPTIONAL BEANS - NOT BEAN 3 DOESN'T EXIST.\n");
		}
		
		try
		{
			if (notBean4.getObject()!=null)
			{
				String											TextNotBean=notBean4.getObject().Print();
			
				System.out.printf("OPTIONAL BEANS - NOT BEAN 4 [%s].\n",TextNotBean);
			}
			else
			{
				System.out.printf("!!!!! OPTIONAL BEANS - NOT BEAN 4 DOESN'T EXIST.\n");
			}
		}
		catch(Exception e)
		{
			System.out.printf("!!!!! OPTIONAL BEANS - NOT BEAN 4 DOESN'T EXIST - EXCEPTION [%s].\n",e.getMessage());
		}
	}	
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------