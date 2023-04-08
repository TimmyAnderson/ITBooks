//----------------------------------------------------------------------------------------------------------------------
package main;
//----------------------------------------------------------------------------------------------------------------------
import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! ANNOTATION [@Component] urcuje, ze instancia CLASS [CMyStereotypeBean2] bude vytvorena ako SPRING BEAN pomocou STEREOTYPES.
@Component
class CMyStereotypeBean2
{
//----------------------------------------------------------------------------------------------------------------------
	private String												MValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION [@PostConstruct] urcuje METHOD, ktora sa ma zavolat po vytvoreni instancie SPRING BEAN.
	@PostConstruct
	public void InitializeBean()
	{
		MValue="INITIALIZED BEAN !"; 	
	
		System.out.format("BEAN [%s] was INITIALIZED !\n",MValue);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION [@PreDestroy] urcuje METHOD, ktora sa ma zavolat pred uvolnenim instancie SPRING BEAN.
	@PreDestroy
	public void DestroyBean()
	{ 	
		System.out.format("BEAN [%s] was DESTROYED !\n",MValue);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public String getValue()
	{
		return(MValue);
	}
//----------------------------------------------------------------------------------------------------------------------
	public void setValue(String Value)
	{
		MValue=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------