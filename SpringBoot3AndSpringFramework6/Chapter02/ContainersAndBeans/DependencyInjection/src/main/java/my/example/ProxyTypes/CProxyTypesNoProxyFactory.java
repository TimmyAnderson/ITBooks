package my.example.ProxyTypes;
//----------------------------------------------------------------------------------------------------------------------
import java.util.UUID;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! SPRING FRAMEWORK NEVYTVORI pre TYPE PROXY OBJECT.
@Configuration(proxyBeanMethods=false)
public class CProxyTypesNoProxyFactory
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CProxyTypesRandomValueNoProxyBean1 MyBeanRandomValueNoProxy1()
	{
		System.out.printf("BEAN 1 CREATED. TYPE [%s].\n",this.getClass().getSimpleName());
		
		String													id=UUID.randomUUID().toString();
		CProxyTypesRandomValueNoProxyBean1						bean=new CProxyTypesRandomValueNoProxyBean1(id);
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public CProxyTypesRandomValueNoProxyBean2 MyBeanRandomValueNoProxy2()
	{
		System.out.printf("BEAN 2 CREATED. TYPE [%s].\n",this.getClass().getSimpleName());
		
		// !!!!! Volanie METHOD [CProxyTypesRandomValueNoProxyBean1 MyBeanRandomValueNoProxy1()] zavola PRIAMO FACTORY METHOD, pretoze PROXY CLASS sa NEGENERUJE.
		// !!!!! Vytvori sa nova instancia OBJECT.
		CProxyTypesRandomValueNoProxyBean1						bean1=MyBeanRandomValueNoProxy1();

		// !!!!! ID sa bude LISIT od ID BEAN [CProxyTypesRandomValueNoProxyBean1].
		String													id=bean1.getValue();
		
		CProxyTypesRandomValueNoProxyBean2						bean2=new CProxyTypesRandomValueNoProxyBean2(id);
		
		return(bean2);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------