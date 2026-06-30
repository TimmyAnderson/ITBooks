package my.example.ImportConfigurations1;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.ImportSelector;
import org.springframework.core.type.AnnotationMetadata;

import my.example.ImportConfigurations3.CImportConfigurations3Bean;
import my.example.ImportConfigurations3.CImportConfigurations3Component;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS implementuje INTEFACE [ImportSelector], ktory umoznuje DYNAMICKY definovat, ktore CONFIGURATION TYPES a COMPONENT TYPES budu impoerovane.
public class CMyImportSelector implements ImportSelector
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public String[] selectImports(AnnotationMetadata importingClassMetadata)
	{
		String[]												classNames=new String[]{CImportConfigurations3Bean.class.getName(),CImportConfigurations3Component.class.getName()};
		
		return(classNames);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------