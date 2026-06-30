package my.example.BeanInjectionPoints;
//----------------------------------------------------------------------------------------------------------------------
import java.lang.reflect.Field;
import java.lang.reflect.Member;

import org.springframework.beans.factory.InjectionPoint;
import org.springframework.beans.factory.config.ConfigurableBeanFactory;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Scope;

import org.springframework.core.MethodParameter;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CBeanInjectionPointsFactory
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Kedze PROGRAM bude obsahovat VIACERO instancii tohto BEAN, je NUTNE nastavit SCOPE BEAN na SCOPE [PROTOTYPE].
	// !!!!! METHOD ma PARAMETER TYPE [InjectionPoint], ktory umoznuje zistit informacie o mieste, kde je novy BEAN vkladany. 
	@Bean
	@Scope(ConfigurableBeanFactory.SCOPE_PROTOTYPE)
	public CBeanInjectionPointsBean MyBean(InjectionPoint injectionPoint)
	{
		Field													field=injectionPoint.getField();
		Member													member=injectionPoint.getMember();
		MethodParameter											methodParameter=injectionPoint.getMethodParameter();
		
		String													fieldText=(field!=null) ? field.toString() : "";
		String													memberText=(member!=null) ? member.toString() : "";
		String													methodParameterText=(methodParameter!=null) ? methodParameter.toString() : "";
		
		String													text=String.format("MY BEAN - FIELD [%s] MEMBER [%s] METHOD PARAMETER [%s].",fieldText,memberText,methodParameterText);
		CBeanInjectionPointsBean								bean=new CBeanInjectionPointsBean(text);
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------