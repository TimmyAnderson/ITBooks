package my.example.CollectionBeans;
//----------------------------------------------------------------------------------------------------------------------
import java.util.List;
import java.util.Map;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CCollectionBeansComponent
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Do FIELD sa ulozia VSETKY BEANS daneho TYPE.
	private final ICollectionBeansInterface[]					beansArray;
	// !!!!! Do FIELD sa ulozia VSETKY BEANS daneho TYPE.
	private final List<ICollectionBeansInterface>				beansList;
	// !!!!! Do FIELD sa ulozia VSETKY BEANS daneho TYPE, spolu s ich NAMES.
	private final Map<String,ICollectionBeansInterface>			beansMap;
	// !!!!! Do FIELD sa ulozia FILTROVANE BEANS daneho TYPE.
	private final ICollectionBeansInterface[]					filteredBeansArray;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	// !!!!! ANNOTATION [ICollectionBeansAnnotation] realizuje FILTERING BEANS.
	public CCollectionBeansComponent(ICollectionBeansInterface[] beansArray, List<ICollectionBeansInterface> beansList, Map<String,ICollectionBeansInterface> beansMap, @ICollectionBeansAnnotation(ICollectionBeansAnnotation.EValue.VALUE_2) ICollectionBeansInterface[] filteredBeansArray)
	{
		this.beansArray=beansArray;
		this.beansList=beansList;
		this.beansMap=beansMap;
		this.filteredBeansArray=filteredBeansArray;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private static void PrintSeparator()
	{
		System.out.println("--------------------------------------------------------------------------------");
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		for(int index=0;index<beansArray.length;index++)
		{
			ICollectionBeansInterface							bean=beansArray[index];
			String												beanText=bean.GetText();
			
			System.out.printf("BEANS ARRAY [%s] - VALUE [%s].\n",index+1,beanText);
		}
		
		PrintSeparator();
		
		for(int index=0;index<beansList.size();index++)
		{
			ICollectionBeansInterface							bean=beansList.get(index);
			String												beanText=bean.GetText();
			
			System.out.printf("BEANS LIST [%s] - VALUE [%s].\n",index+1,beanText);
		}
		
		PrintSeparator();

		for(String beanName : beansMap.keySet())
		{
			ICollectionBeansInterface							bean=beansMap.get(beanName);
			String												beanText=bean.GetText();
			
			System.out.printf("BEANS MAP [%s] - VALUE [%s].\n",beanName,beanText);
		}
		
		PrintSeparator();
		
		for(int index=0;index<filteredBeansArray.length;index++)
		{
			ICollectionBeansInterface							bean=filteredBeansArray[index];
			String												beanText=bean.GetText();
			
			System.out.printf("FILTERED BEANS ARRAY [%s] - VALUE [%s].\n",index+1,beanText);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------