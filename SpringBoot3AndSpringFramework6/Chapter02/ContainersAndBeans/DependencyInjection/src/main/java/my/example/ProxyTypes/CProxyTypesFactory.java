package my.example.ProxyTypes;
//----------------------------------------------------------------------------------------------------------------------
import java.util.UUID;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! SPRING FRAMEWORK vytvara pre CONFIGURATION TYPES DERIVED TYPES, ktore sluzia ako PROXY OBJECTS.
@Configuration
public class CProxyTypesFactory
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CProxyTypesRandomValueBean1 MyBeanRandomValue1()
	{
		System.out.printf("BEAN 1 CREATED. TYPE [%s].\n",this.getClass().getSimpleName());
		
		String													id=UUID.randomUUID().toString();
		CProxyTypesRandomValueBean1								bean=new CProxyTypesRandomValueBean1(id);
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CProxyTypesRandomValueBean2 MyBeanRandomValue2()
	{
		System.out.printf("BEAN 2 CREATED. TYPE [%s].\n",this.getClass().getSimpleName());
		
		// !!!!! Volanie METHOD [CProxyTypesRandomValueBean1 MyBeanRandomValue1()] v skutocnosti NEZAVOLA PRIAMO tuto METHOD, pretoze cela CLASS je PROXY CLASS. Namiesto METHOD sa zavola PROXY METHOD, ktora vykonava kontrolu ci BEAN [CProxyTypesRandomValueBean1], a ak bol, NEVYTVORI NOVY BEAN, ale vracia instanciu UZ VYTVORENEHO BEAN. Preto BEAN [CProxyTypesRandomValueBean1] aj BEAN [CProxyTypesRandomValueBean2] budu obsahovat ROVNAKU VALUE. 
		CProxyTypesRandomValueBean1								bean1=MyBeanRandomValue1();

		String													id=bean1.getValue();
		
		CProxyTypesRandomValueBean2								bean2=new CProxyTypesRandomValueBean2(id);
		
		return(bean2);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CProxyTypesRandomValueBean3 MyBeanRandomValue3()
	{
		// !!!!! Explicitne sa vytvori TYPE [CProxyTypesFactory], a NIE PROXY TYPE.
		CProxyTypesFactory										myFactory=new CProxyTypesFactory();

		System.out.printf("BEAN 3 CREATED. THIS TYPE [%s] MY FACTORY TYPE [%s].\n",this.getClass().getSimpleName(),myFactory.getClass().getSimpleName());
		
		// !!!!! Zavola sa PRIAMO FACTORY METHOD, a NIE PROXY METHOD.
		CProxyTypesRandomValueBean1								bean1=myFactory.MyBeanRandomValue1();

		// !!!!! Vysledkom je, ze ID je NEZAVISLE na ID v BEAN [CProxyTypesRandomValueBean1] a BEAN [CProxyTypesRandomValueBean2].
		String													id=bean1.getValue();
		
		CProxyTypesRandomValueBean3								bean3=new CProxyTypesRandomValueBean3(id);
		
		return(bean3);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------