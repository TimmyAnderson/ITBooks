package my.example.VariousBeans;
//----------------------------------------------------------------------------------------------------------------------
import java.util.ArrayList;
import java.util.List;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
//----------------------------------------------------------------------------------------------------------------------
@Configuration
public class CVariousBeansFactory
{
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public String StringBean()
	{
		System.out.printf("BEAN [String] CREATED.\n");
		
		String													bean="Timmy 1";
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public String[] StringArrayBean()
	{
		System.out.printf("BEAN [String[]] CREATED.\n");
		
		// !!!!! Pri spusteni PROGRAMU sa mi stavalo ze sa vytvoril BEAN TYPE [String] a BEAN TYPE [String[]] obsahoval iba 1 ITEM s VALUE [String]. 
		// !!!!! Toto chovanie bolo sposobene tym, ze BEAN TYPE [String[]] sa vytvori AZ po volani tejto BEAN FACTORY METHOD.
		
		String[]												bean=new String[]{"Timmy 2","Anderson 2"};
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	@Bean
	public List<String> StringListBean()
	{
		System.out.printf("BEAN [List<String>] CREATED.\n");

		// !!!!! Pri spusteni PROGRAMU sa mi stavalo ze sa vytvoril BEAN TYPE [String] a BEAN TYPE [List<String>] obsahoval iba 1 ITEM s VALUE [String].
		// !!!!! Toto chovanie bolo sposobene tym, ze BEAN TYPE [List<String>] sa vytvori AZ po volani tejto BEAN FACTORY METHOD.
		
		List<String>											bean=new ArrayList<String>();
		
		bean.add("Timmy 3");
		bean.add("Jenny 3");
		bean.add("Josh 3");
		bean.add("Lucas 3");
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------