package my.example.AutoConfigurationBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.boot.autoconfigure.AutoConfiguration;
import org.springframework.boot.autoconfigure.condition.ConditionalOnProperty;
//----------------------------------------------------------------------------------------------------------------------
// !!! Aplikuje sa ANNOTATION [@AutoConfiguration].
@AutoConfiguration
// !!! Aplikuje sa CONDITIONS. Iba ak su VSETKY splnene, tak je instancia BEAN vytvorena.
@ConditionalOnProperty(name="MyProperty1",havingValue="AAA")
@ConditionalOnProperty(name="MyProperty2",havingValue="222")
public class CAutoConfigurationBeansBean2
{
//----------------------------------------------------------------------------------------------------------------------
	public String GetText()
	{
		return("From BEAN 2.");
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------