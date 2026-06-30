package my.example.Components;
//----------------------------------------------------------------------------------------------------------------------
import my.example.Package1.CPackage1Class;
import my.example.Package2.CPackage2Class;

import org.springframework.context.annotation.ComponentScan;
//----------------------------------------------------------------------------------------------------------------------
@ComponentScan(basePackageClasses={CPackage1Class.class,CPackage2Class.class})
public class CMyCustomMainConfigurationBasePackageClasses
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------