using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.Xml;
//-------------------------------------------------------------------------------------------------------
using CResolveNameCache=System.Collections.Generic.Dictionary<string,System.Type>;
using CTryResolveTypeCache=System.Collections.Generic.Dictionary<System.Type,System.Collections.Generic.HashSet<System.Type>>;
//-------------------------------------------------------------------------------------------------------
namespace MyDataContractResolver
{
//-------------------------------------------------------------------------------------------------------
	public class CMyDataContractResolver : DataContractResolver
	{
//-------------------------------------------------------------------------------------------------------
		private object											MLock1=new object();
		private readonly object									MLock2=new object();
		private readonly CResolveNameCache						MResolveNameCache;
		private readonly CTryResolveTypeCache					MTryResolveTypeCache;
		private readonly bool									MUseCache;
		private readonly bool									MDumpToConsole;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMyDataContractResolver(bool UseCache, bool DumpToConsole)
		{
			MUseCache=UseCache;
			MDumpToConsole=DumpToConsole;

			if (UseCache==true)
			{
				MResolveNameCache=new Dictionary<string,Type>();
				MTryResolveTypeCache=new Dictionary<Type,HashSet<Type>>();
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Vola sa pri DESERIALIZACII.
		public override Type ResolveName(string TypeName, string TypeNamespace, Type DeclaredType, DataContractResolver KnownTypeResolver)
		{
			Type									Ret;

			try
			{
				if (MUseCache==true)
				{
					lock(MLock1)
					{
						if (MResolveNameCache.TryGetValue(TypeName,out Ret)==true)
						{
							return(Ret);
						}
					}
				}

				Ret=Type.GetType(TypeName);

				if (MUseCache==true)
				{
					lock(MLock1)
					{
						if (MResolveNameCache.ContainsKey(TypeName)==false)
						{
							MResolveNameCache.Add(TypeName,Ret);

							if (MDumpToConsole==true)
							{
								Console.WriteLine(string.Format("CACHE 1 - KEY: [{0}], VALUE: [{1}] !",TypeName,Ret));
							}
						}
					}
				}

				return(Ret);
			}
			catch
			{
			}

			// Skusim DEFAULT RESOLVER.
			Ret=KnownTypeResolver.ResolveName(TypeName,TypeNamespace,DeclaredType,KnownTypeResolver);

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		// Vola sa pri SERIALIZACII.
		public override bool TryResolveType(Type Type, Type DeclaredType, DataContractResolver KnownTypeResolver, out XmlDictionaryString TypeName, out XmlDictionaryString TypeNamespace)
		{
			Type									TypeToTest=Type;

			if (MUseCache==true)
			{
				lock(MLock2)
				{
					HashSet<Type>					DictionaryValue;

					if (MTryResolveTypeCache.TryGetValue(DeclaredType,out DictionaryValue)==true)
					{
						if (DictionaryValue.Contains(Type)==true)
						{
							XmlDictionary			XD=new XmlDictionary();
					
							TypeNamespace=XD.Add(Type.Namespace);
							TypeName=XD.Add(Type.AssemblyQualifiedName);
							return(true);
						}
					}
				}
			}

			while(TypeToTest!=null)
			{
				if (TypeToTest==DeclaredType)
				{
					XmlDictionary					XD=new XmlDictionary();
					
					TypeNamespace=XD.Add(Type.Namespace);
					TypeName=XD.Add(Type.AssemblyQualifiedName);

					if (MUseCache==true)
					{
						lock(MLock2)
						{
							HashSet<Type>			DictionaryValue;

							if (MTryResolveTypeCache.TryGetValue(DeclaredType,out DictionaryValue)==false)
							{
								DictionaryValue=new HashSet<Type>();
								MTryResolveTypeCache.Add(DeclaredType,DictionaryValue);
							}

							if (DictionaryValue.Contains(Type)==false)
							{
								DictionaryValue.Add(Type);

								if (MDumpToConsole==true)
								{
									Console.WriteLine(string.Format("CACHE 2 - KEY: [{0}], VALUE: [{1}] !",DeclaredType,Type));
								}
							}
						}
					}

					return(true);
				}

				TypeToTest=TypeToTest.BaseType;
			}

			// Skusim DEFAULT RESOLVER.
			bool									Ret=KnownTypeResolver.TryResolveType(Type,DeclaredType,KnownTypeResolver,out TypeName,out TypeNamespace);

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------