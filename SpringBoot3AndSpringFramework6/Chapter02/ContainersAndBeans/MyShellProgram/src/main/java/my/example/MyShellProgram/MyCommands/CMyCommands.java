package my.example.MyShellProgram.MyCommands;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.shell.core.command.annotation.Command;
import org.springframework.shell.core.command.annotation.Option;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!! ANNOTATION definuje CLASS, ktora obsahuje SHELL COMMANDS.
@Component
public class CMyCommands
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION umoznuje definovat SHELL COMMAND.
	@Command("This is MY METHOD 1.")
	public String Method1()
	{
		return("Hello World!");
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION umoznuje definovat SHELL COMMAND s CUSTOM COMMAND NAME.
	@Command(description="This is MY METHOD 2.",name={"mm2"})
	public int Method2()
	{
		return(123);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION umoznuje definovat SHELL COMMAND s CUSTOM COMMAND NAME.
	@Command(description="This is MY METHOD 3.",name={"mm3"})
	// !!! ANNOTATION [@Option] definuje PARAMETER.
	public String Method3(@Option(shortName='n',longName="name",description="Some name.",defaultValue="World") String name)
	{
		String													output=String.format("Hello [%s].",name);
		
		return(output);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION umoznuje definovat SHELL COMMAND s CUSTOM COMMAND NAME.
	@Command(description="This is MY METHOD 4.",name={"mm4"})
	// !!! ANNOTATION [@Option] definuje PARAMETER.
	public String Method4(@Option(shortName='a',longName="name1",description="Some name 1.",defaultValue="Timmy") String name1, @Option(shortName='b',longName="name2",description="Some name 2.",defaultValue="Jenny") String name2)
	{
		String													output=String.format("Hello [%s]. Hello [%s].",name1,name2);
		
		return(output);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! ANNOTATION umoznuje definovat SHELL COMMAND s CUSTOM COMMAND NAME.
	@Command(description="This is MY METHOD 5.",name={"mm5"})
	// !!! ANNOTATION [@Option] definuje PARAMETER.
	public void Method5(@Option(shortName='a',longName="name1",description="Some name 1.",defaultValue="Timmy") String name1, @Option(shortName='b',longName="name2",description="Some name 2.",defaultValue="Jenny") String name2)
	{
		String													output=String.format("Hello [%s]. Hello [%s].\n",name1,name2);
		
		System.out.print(output);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------