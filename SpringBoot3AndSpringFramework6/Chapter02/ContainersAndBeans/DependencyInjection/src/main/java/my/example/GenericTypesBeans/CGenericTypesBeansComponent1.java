package my.example.GenericTypesBeans;
//----------------------------------------------------------------------------------------------------------------------
import java.util.UUID;

import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! SPRING FRAMEWORK vytvori VZDY iba 1 INSTANCIU GENERIC TYPE SPRING MANAGED BEAN. To znamena, ze GENERIC TYPE SPRING MANAGED BEANS MUSIA byt VZDY vytvarane pomocou FACTORY METHODS.
@Component
public class CGenericTypesBeansComponent1<TType>
{
//----------------------------------------------------------------------------------------------------------------------
	private String												id;
	private final TType											value;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Kedze COMPONENT, ktory NIE JE VYTVARANY FACTORY METHOD, ale priamo SPRING FRAMEWORK ma ako PARAMETER TYPE [TType], aj tento TYPE musi byt definovany ako BEAN.
	// !!!!! BEAN MUSEL mat 1 LUBOVOLNY TYPE oznaceny ako PRIMARY, aby SPRING FRAMEWORK vytvorit instanciu tohto BEAN. Za PRIMARY som oznacil TYPE [Boolean].
	@Autowired
	public CGenericTypesBeansComponent1(TType value)
	{
		this.id=UUID.randomUUID().toString();
		this.value=value;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public String Print()
	{
		String													text=String.format("COMPONENT 1 - ID [%s] VALUE [%s].",id,value);

		return(text);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------