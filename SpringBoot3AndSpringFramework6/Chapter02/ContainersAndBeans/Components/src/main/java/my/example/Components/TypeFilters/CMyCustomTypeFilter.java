package my.example.Components.TypeFilters;
import java.io.IOException;

import org.springframework.core.type.ClassMetadata;
import org.springframework.core.type.classreading.MetadataReader;
import org.springframework.core.type.classreading.MetadataReaderFactory;
//----------------------------------------------------------------------------------------------------------------------
import org.springframework.core.type.filter.TypeFilter;
//----------------------------------------------------------------------------------------------------------------------
public final class CMyCustomTypeFilter implements TypeFilter
{
//----------------------------------------------------------------------------------------------------------------------
	@Override
	public boolean match(MetadataReader metadataReader, MetadataReaderFactory metadataReaderFactory) throws IOException
	{
		ClassMetadata											classMetadata=metadataReader.getClassMetadata();
		String													className=classMetadata.getClassName();

		if (className.contains("2Class")==true)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------