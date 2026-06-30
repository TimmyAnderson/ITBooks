package my.example.Components;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.ComponentScan;
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS je pouzita ako CONFIGURATION CLASS pre METHOD [SpringApplication.run()].
// !!!!! Pretoze na CLASS je applikovana ANNOTATION [@ComponentScan], ktora je pouzita BEZ PARAMETERS, vykona sa COMPONENT SCAN na CURRENT PACKAGE a vsetkych CHILD PACKAGES.
@ComponentScan
public class CMyCustomMainConfigurationWithComponentScan
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------