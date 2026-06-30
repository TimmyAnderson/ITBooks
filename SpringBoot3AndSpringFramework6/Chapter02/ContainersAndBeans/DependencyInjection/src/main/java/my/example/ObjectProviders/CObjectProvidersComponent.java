package my.example.ObjectProviders;
//----------------------------------------------------------------------------------------------------------------------
import java.util.Iterator;

import org.springframework.beans.factory.NoSuchBeanDefinitionException;
import org.springframework.beans.factory.NoUniqueBeanDefinitionException;

import org.springframework.beans.factory.ObjectProvider;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CObjectProvidersComponent
{
//----------------------------------------------------------------------------------------------------------------------
	private final ObjectProvider<IObjectProvidersInterfaceAAA>	providerAAA;
	private final ObjectProvider<IObjectProvidersInterfaceBBB>	providerBBB;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public CObjectProvidersComponent(ObjectProvider<IObjectProvidersInterfaceAAA> providerAAA, ObjectProvider<IObjectProvidersInterfaceBBB> providerBBB)
	{
		this.providerAAA=providerAAA;
		this.providerBBB=providerBBB;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		try
		{
			IObjectProvidersInterfaceAAA						bean=providerAAA.getObject();

			if (bean!=null)
			{
				String											beanText=bean.GetText();
				
				System.out.printf("GET OBJECT - From BEAN AAA [%s].\n",beanText);
			}
			else
			{
				System.out.printf("GET OBJECT - BEAN AAA NOT FOUND.\n");
			}
		}
		catch(NoUniqueBeanDefinitionException E)
		{
			System.out.printf("GET OBJECT - BEAN AAA - DUPLICATE EXCEPTION.\n");
		}
		catch(NoSuchBeanDefinitionException E)
		{
			System.out.printf("GET OBJECT - BEAN AAA - NOT FOUND EXCEPTION.\n");
		}
		
		try
		{
			IObjectProvidersInterfaceBBB						bean=providerBBB.getObject();

			if (bean!=null)
			{
				String											beanText=bean.GetText();
				
				System.out.printf("GET OBJECT - From BEAN BBB [%s].\n",beanText);
			}
			else
			{
				System.out.printf("GET OBJECT - BEAN BBB - NOT FOUND.\n");
			}
		}
		catch(NoUniqueBeanDefinitionException E)
		{
			System.out.printf("GET OBJECT - BEAN BBB - DUPLICATE EXCEPTION.\n");
		}
		catch(NoSuchBeanDefinitionException E)
		{
			System.out.printf("GET OBJECT - BEAN BBB - NOT FOUND EXCEPTION.\n");
		}
		
		try
		{
			IObjectProvidersInterfaceAAA						bean=providerAAA.getIfAvailable();

			if (bean!=null)
			{
				String											beanText=bean.GetText();
				
				System.out.printf("GET IF AVAILABLE - From BEAN AAA [%s].\n",beanText);
			}
			else
			{
				System.out.printf("GET IF AVAILABLE - BEAN AAA NOT FOUND.\n");
			}
		}
		catch(NoUniqueBeanDefinitionException E)
		{
			System.out.printf("GET IF AVAILABLE - BEAN AAA - DUPLICATE EXCEPTION.\n");
		}
		catch(NoSuchBeanDefinitionException E)
		{
			System.out.printf("GET IF AVAILABLE - BEAN AAA - NOT FOUND EXCEPTION.\n");
		}
		
		try
		{
			IObjectProvidersInterfaceBBB						bean=providerBBB.getIfAvailable();

			if (bean!=null)
			{
				String											beanText=bean.GetText();
				
				System.out.printf("GET IF AVAILABLE - From BEAN BBB [%s].\n",beanText);
			}
			else
			{
				System.out.printf("GET IF AVAILABLE - BEAN BBB - NOT FOUND.\n");
			}
		}
		catch(NoUniqueBeanDefinitionException E)
		{
			System.out.printf("GET IF AVAILABLE - BEAN BBB - DUPLICATE EXCEPTION.\n");
		}
		catch(NoSuchBeanDefinitionException E)
		{
			System.out.printf("GET IF AVAILABLE - BEAN BBB - NOT FOUND EXCEPTION.\n");
		}
		
		try
		{
			IObjectProvidersInterfaceAAA						bean=providerAAA.getIfUnique();

			if (bean!=null)
			{
				String											beanText=bean.GetText();
				
				System.out.printf("GET IF UNIQUE - From BEAN AAA [%s].\n",beanText);
			}
			else
			{
				System.out.printf("GET IF UNIQUE - BEAN AAA NOT FOUND.\n");
			}
		}
		catch(NoUniqueBeanDefinitionException E)
		{
			System.out.printf("GET IF UNIQUE - BEAN AAA - DUPLICATE EXCEPTION.\n");
		}
		catch(NoSuchBeanDefinitionException E)
		{
			System.out.printf("GET IF UNIQUE - BEAN AAA - NOT FOUND EXCEPTION.\n");
		}
		
		try
		{
			IObjectProvidersInterfaceBBB						bean=providerBBB.getIfUnique();

			if (bean!=null)
			{
				String											beanText=bean.GetText();
				
				System.out.printf("GET IF UNIQUE - From BEAN BBB [%s].\n",beanText);
			}
			else
			{
				System.out.printf("GET IF UNIQUE - BEAN BBB - NOT FOUND.\n");
			}
		}
		catch(NoUniqueBeanDefinitionException E)
		{
			System.out.printf("GET IF UNIQUE - BEAN BBB - DUPLICATE EXCEPTION.\n");
		}
		catch(NoSuchBeanDefinitionException E)
		{
			System.out.printf("GET IF UNIQUE - BEAN BBB - NOT FOUND EXCEPTION.\n");
		}
		
		try
		{
			Iterator<IObjectProvidersInterfaceBBB>				iterator=providerBBB.iterator();

			while(iterator.hasNext()==true)
			{
				IObjectProvidersInterfaceBBB					bean=iterator.next();
				String											beanText=bean.GetText();
				
				System.out.printf("ITERATOR - From BEAN BBB [%s].\n",beanText);
			}
		}
		catch(NoUniqueBeanDefinitionException E)
		{
			System.out.printf("ITERATOR - BEAN BBB - DUPLICATE EXCEPTION.\n");
		}
		catch(NoSuchBeanDefinitionException E)
		{
			System.out.printf("ITERATOR - BEAN BBB - NOT FOUND EXCEPTION.\n");
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------