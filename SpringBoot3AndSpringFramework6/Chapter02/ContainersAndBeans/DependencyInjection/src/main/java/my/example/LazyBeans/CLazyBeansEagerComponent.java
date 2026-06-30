package my.example.LazyBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.context.annotation.Lazy;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
// !!! COMPONENT je EAGER COMPONENT.
@Component
public class CLazyBeansEagerComponent
{
//----------------------------------------------------------------------------------------------------------------------
	private final CLazyBeansBean6								bean6;
	private final CLazyBeansBean7								bean7;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	// !!! Vdaka aplikacii ANNOTATION [@Lazy(false)] na LAZY BEAN [CLazyBeansBean6] vytvori EAGER sposobom.
	// !!! Vdaka aplikacii ANNOTATION [@Lazy(true)] na LAZY BEAN [CLazyBeansBean7] vytvori LAZY sposobom.
	@Autowired
	public CLazyBeansEagerComponent(@Lazy(false) CLazyBeansBean6 bean6, @Lazy(true) CLazyBeansBean7 bean7)
	{
		this.bean6=bean6;
		this.bean7=bean7;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		String													beanText6=bean6.GetText();
		String													beanText7=bean7.GetText();
		
		System.out.printf("BEAN 6 - VALUE [%s].\n",beanText6);
		System.out.printf("BEAN 7 - VALUE [%s].\n",beanText7);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------