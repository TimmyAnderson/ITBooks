package my.example.CacheableBeans;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.stereotype.Component;
//----------------------------------------------------------------------------------------------------------------------
@Component
public class CCacheableBeansComponent
{
//----------------------------------------------------------------------------------------------------------------------
	private final CCacheableBeansBean							bean;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	@Autowired
	public CCacheableBeansComponent(CCacheableBeansBean bean)
	{
		this.bean=bean;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public void Test()
	{
		try
		{
			{
				Long											key=1l;
				
				String											value1=bean.MyCachableMethod(key);

				System.out.printf("VALUE [%s] ATTEMT [1] - VALUE [%s].\n",key,value1);
			
				Thread.sleep(2000);
				
				String											value2=bean.MyCachableMethod(key);

				System.out.printf("VALUE [%s] ATTEMT [2] - VALUE [%s].\n",key,value2);
			}
			
			{
				Long											key=2l;
				
				String											value1=bean.MyCachableMethod(key);

				System.out.printf("VALUE [%s] ATTEMT [1] - VALUE [%s].\n",key,value1);
			
				Thread.sleep(2000);
				
				String											value2=bean.MyCachableMethod(key);

				System.out.printf("VALUE [%s] ATTEMT [2] - VALUE [%s].\n",key,value2);
			}

			{
				// !!! DOESN'T CACHE.
				Long											key=100l;
				
				String											value1=bean.MyCachableMethod(key);

				System.out.printf("VALUE [%s] ATTEMT [1] - VALUE [%s].\n",key,value1);
			
				Thread.sleep(2000);
				
				String											value2=bean.MyCachableMethod(key);

				System.out.printf("VALUE [%s] ATTEMT [2] - VALUE [%s].\n",key,value2);
			}
		}
		catch (InterruptedException e)
		{
			System.out.printf("EXCEPTION [%s].\n",e.getMessage());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------