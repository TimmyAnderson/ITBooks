//----------------------------------------------------------------------------------------------------------------------
package main;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Primary;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS predstavuje CONFIGURATION CLASS pre SPRING BEANS.
// !!!!! CLASS MUSI mat ANNOTATION [@Configuration].
@Configuration
// !!!!! ANNOTATION [@ComponentScan] urcuje, v ktorych PACKAGES sa maju hladat CLASSES oznacene ako BEANS na zaklade STEREOTYPE ANNOTATION.
@ComponentScan(basePackages="main") 
public class CProjectConfiguration
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aby OBJECTS z CLASS [String] mohli byt vytvarane ako BEANS, je nutne na METHOD aplikovat ANNOTATION [@Bean].
	// !!!!! METHOD je pouzita SPRING na vytvorenie SPRING BEAN z CLASS [String] na zaklade TYPE RETURN VALUE. 
	@Bean
	public String CreateString()	
	{
		String													Bean="Hello BEAN !!!";
		
		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aby OBJECTS z CLASS [Integer] mohli byt vytvarane ako BEANS, je nutne na METHOD aplikovat ANNOTATION [@Bean].
	// !!!!! METHOD je pouzita SPRING na vytvorenie SPRING BEAN z CLASS [Integer] na zaklade TYPE RETURN VALUE. 
	@Bean
	public Integer CreateInteger()	
	{
		Integer													Bean=123;
		
		return(Bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aby OBJECTS z CLASS [CMyBean1] mohli byt vytvarane ako BEANS, je nutne na METHOD aplikovat ANNOTATION [@Bean].
	// !!!!! METHOD je pouzita SPRING na vytvorenie SPRING BEAN z CLASS [CMyBean1] na zaklade TYPE RETURN VALUE. 
	@Bean
	public CMyBean1 CreateMyBean1()	
	{
		CMyBean1													MyBean=new CMyBean1();
		
		MyBean.setValue("BEAN 1 - VALUE set in CProjectConfiguration.");
		
		return(MyBean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aby OBJECTS z CLASS [CMyBean2] mohli byt vytvarane ako BEANS, je nutne na METHOD aplikovat ANNOTATION [@Bean].
	// !!!!! METHOD je pouzita SPRING na vytvorenie SPRING BEAN z CLASS [CMyBean2] na zaklade TYPE RETURN VALUE. 	@Bean
	@Bean
	public CMyBean2 CreateMyBean21()	
	{
		CMyBean2													MyBean=new CMyBean2();
		
		MyBean.setValue("BEAN 2 - VALUE [111].");
		
		return(MyBean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aby OBJECTS z CLASS [CMyBean2] mohli byt vytvarane ako BEANS, je nutne na METHOD aplikovat ANNOTATION [@Bean].
	// !!!!! METHOD je pouzita SPRING na vytvorenie SPRING BEAN z CLASS [CMyBean2] na zaklade TYPE RETURN VALUE. 	@Bean
	@Bean
	public CMyBean2 CreateMyBean22()	
	{
		CMyBean2													MyBean=new CMyBean2();
		
		MyBean.setValue("BEAN 2 - VALUE [222].");
		
		return(MyBean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aby OBJECTS z CLASS [CMyBean2] mohli byt vytvarane ako BEANS, je nutne na METHOD aplikovat ANNOTATION [@Bean].
	// !!!!! METHOD je pouzita SPRING na vytvorenie SPRING BEAN z CLASS [CMyBean2] na zaklade TYPE RETURN VALUE. 	@Bean
	@Bean
	public CMyBean2 CreateMyBean23()	
	{
		CMyBean2													MyBean=new CMyBean2();
		
		MyBean.setValue("BEAN 2 - VALUE [333].");
		
		return(MyBean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aby OBJECTS z CLASS [CMyBean3] mohli byt vytvarane ako BEANS, je nutne na METHOD aplikovat ANNOTATION [@Bean].
	// !!!!! METHOD je pouzita SPRING na vytvorenie SPRING BEAN z CLASS [CMyBean3] na zaklade TYPE RETURN VALUE. 	@Bean
	// !!!!! DEFAULT BEAN METHOD, ktora sa pouziva ak sa BEAN vytvara IBA na zaklade TYPE, a nie na zaklade NAME. 
	@Bean
	@Primary
	public CMyBean3 CreateMyBeanDefault()	
	{
		CMyBean3													MyBean=new CMyBean3();
		
		MyBean.setValue("BEAN 3 - VALUE [DEFAULT].");
		
		return(MyBean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aby OBJECTS z CLASS [CMyBean3] mohli byt vytvarane ako BEANS, je nutne na METHOD aplikovat ANNOTATION [@Bean].
	// !!!!! METHOD je pouzita SPRING na vytvorenie SPRING BEAN z CLASS [CMyBean3] na zaklade TYPE RETURN VALUE. 	@Bean
	@Bean
	public CMyBean3 CreateMyBean31()	
	{
		CMyBean3													MyBean=new CMyBean3();
		
		MyBean.setValue("BEAN 3 - VALUE [111].");
		
		return(MyBean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aby OBJECTS z CLASS [CMyBean3] mohli byt vytvarane ako BEANS, je nutne na METHOD aplikovat ANNOTATION [@Bean].
	// !!!!! METHOD je pouzita SPRING na vytvorenie SPRING BEAN z CLASS [CMyBean3] na zaklade TYPE RETURN VALUE. 	@Bean
	@Bean
	public CMyBean3 CreateMyBean32()	
	{
		CMyBean3													MyBean=new CMyBean3();
		
		MyBean.setValue("BEAN 3 - VALUE [222].");
		
		return(MyBean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aby OBJECTS z CLASS [CMyBean3] mohli byt vytvarane ako BEANS, je nutne na METHOD aplikovat ANNOTATION [@Bean].
	// !!!!! METHOD je pouzita SPRING na vytvorenie SPRING BEAN z CLASS [CMyBean3] na zaklade TYPE RETURN VALUE. 	@Bean
	@Bean
	public CMyBean3 CreateMyBean33()	
	{
		CMyBean3													MyBean=new CMyBean3();
		
		MyBean.setValue("BEAN 3 - VALUE [333].");
		
		return(MyBean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aby OBJECTS z CLASS [CMyBean4] mohli byt vytvarane ako BEANS, je nutne na METHOD aplikovat ANNOTATION [@Bean].
	// !!!!! METHOD je pouzita SPRING na vytvorenie SPRING BEAN z CLASS [CMyBean4] na zaklade TYPE RETURN VALUE. 	@Bean
	// !!!!! BEAN pouziva CUSTOM NAME.
	@Bean(name="Bean1")
	public CMyBean4 CreateMyBean41()
	{
		CMyBean4													MyBean=new CMyBean4();
		
		MyBean.setValue("BEAN 4 - VALUE [111].");
		
		return(MyBean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aby OBJECTS z CLASS [CMyBean4] mohli byt vytvarane ako BEANS, je nutne na METHOD aplikovat ANNOTATION [@Bean].
	// !!!!! METHOD je pouzita SPRING na vytvorenie SPRING BEAN z CLASS [CMyBean4] na zaklade TYPE RETURN VALUE. 	@Bean
	// !!!!! BEAN pouziva CUSTOM NAME.
	@Bean(value="Bean2")
	public CMyBean4 CreateMyBean42()
	{
		CMyBean4													MyBean=new CMyBean4();
		
		MyBean.setValue("BEAN 4 - VALUE [222].");
		
		return(MyBean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Aby OBJECTS z CLASS [CMyBean4] mohli byt vytvarane ako BEANS, je nutne na METHOD aplikovat ANNOTATION [@Bean].
	// !!!!! METHOD je pouzita SPRING na vytvorenie SPRING BEAN z CLASS [CMyBean4] na zaklade TYPE RETURN VALUE. 	@Bean
	// !!!!! BEAN pouziva CUSTOM NAME.
	@Bean("Bean3")
	public CMyBean4 CreateMyBean43()
	{
		CMyBean4													MyBean=new CMyBean4();
		
		MyBean.setValue("BEAN 4 - VALUE [333].");
		
		return(MyBean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------