package my.example.LazyBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Lazy;
//----------------------------------------------------------------------------------------------------------------------
// !!! BY DEFAULT vsetky BEANS su IMPLICITNE oznacene ako LAZY BEANS.
@Lazy(true)
@Configuration
public class CLazyBeansFactoryLazy
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! BEAN je LAZY BEAN, pretoze prebral LAZY SETTING aplikovany na TYPE.
	@Bean
	public CLazyBeansBean4 MyBean4()
	{
		CLazyBeansBean4											bean=new CLazyBeansBean4();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
	// !!! BEAN je EAGER BEAN, pretoze prepisal LAZY SETTING aplikovany na TYPE.
	@Lazy(false)
	@Bean
	public CLazyBeansBean5 MyBean5()
	{
		CLazyBeansBean5											bean=new CLazyBeansBean5();
		
		return(bean);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------