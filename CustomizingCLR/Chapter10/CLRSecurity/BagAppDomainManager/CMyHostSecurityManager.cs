using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Security;
using System.Security.Policy;
using System.Security.Permissions;
using System.Reflection;
//------------------------------------------------------------------------------------------------------
namespace BagAppDomainManager
{
//------------------------------------------------------------------------------------------------------
	public sealed class CMyHostSecurityManager : HostSecurityManager
	{
//------------------------------------------------------------------------------------------------------
		// !!!!! IDENTIFIKATOR sa MUSI ZHODOVAT s ROVNAKO POMENOVANYM IDENTIFIKATOROM v BagHost.
		private static int										ASSEMBLY_FROM_BAG=999;
//------------------------------------------------------------------------------------------------------
        private static byte[]									MMSPublicKey={0,36,0,0,4,128,0,0,148,0,0,0,6,2,0,0,0,36,0,0,82,83,65,49,0,4,0,0,1,0,1,0,7,209,250,87,196, 174, 217, 240, 163,46,132,170,15,174,253,13,233,232,253,106,236,143,135,251,3,118,108,131,76,153,146,30,178,59,231,154,217,213,220,193,221,154,210,54,19,33,2,144,11,114,60,249,128,149,127,196,225,119,16,143,198,7,119,79,41,232,50,14,146,234,5,236,228,232,33,192,165,239,232,241,100,92,76,12,147,193,171,153,40,93,98,44,170,101,44,29,250,214,61,116,93,111,45,229,241,126,94,175,15,196,150,61,38,28,138,18,67,101,24,32,109,192,147,52,77,90,210,147};
        private static byte[]									MECMAPublicKey={0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0};
		// !!!!! Toto je PUBLIC KEY, ktorym je SIGNED ASSEMBLY BagAppDomainManager.
        private static byte[]									MBagHostRuntimePublicKey={7,2,0,0,0,36,0,0,82,83,65,50,0,4,0,0,1,0,1,0,111,59,10,221,162,92,169,0,192,17,176,126,13,240,223,46,126,209,133,184,17,90,108,106,193,82,217,140,125,203,120,154,152,153,114,6,156,130,63,93,166,88,155,12,46,142,75,239,64,18,13,87,115,228,19,215,213,11,110,51,150,51,105,242,120,159,128,146,57,249,5,227,132,70,4,10,170,21,16,158,215,76,11,73,202,144,38,178,144,106,135,205,79,64,127,140,249,29,103,15,122,159,42,30,148,150,22,197,68,116,54,69,102,215,57,46,225,46,239,162,52,225,220,153,211,198,254,199,69,240,217,183,98,82,79,124,181,215,193,89,84,39,100,80,59,102,14,82,200,168,181,227,173,104,120,59,230,211,174,143,108,150,108,119,100,14,49,215,248,158,217,5,100,234,216,73,215,128,191,174,243,42,63,169,40,194,55,155,36,41,15,233,35,250,95,140,183,91,204,32,9,136,231,91,209,42,110,63,77,25,239,255,230,136,105,75,60,186,127,8,91,180,27,36,134,43,38,173,106,212,19,116,119,15,144,115,123,245,152,238,140,158,102,150,51,91,213,10,248,123,215,207,101,112,174,219,5,73,190,39,45,38,15,251,231,59,120,212,67,126,199,179,219,117,140,3,142,235,224,190,81,123,140,171,64,10,27,124,20,146,22,147,9,68,29,108,84,168,73,110,11,32,80,90,96,53,134,12,18,64,27,40,192,15,22,23,142,62,212,206,33,0,126,97,182,75,125,57,141,22,106,102,61,122,151,174,143,136,66,218,32,13,156,102,108,57,130,154,133,150,197,86,141,118,78,214,139,7,45,5,229,17,166,162,73,208,108,56,102,214,78,32,33,16,64,204,85,3,160,191,206,60,244,163,47,100,196,232,65,230,35,157,212,5,105,69,236,22,49,87,104,72,14,210,49,180,128,149,61,216,87,9,127,25,49,187,192,148,211,117,146,94,46,204,35,100,192,7,89,100,35,114,253,7,233,8,164,104,23,11,14,161,79,251,190,167,109,77,1,188,69,165,234,224,105,190,28,131,219,10,110,15,221,192,119,220,165,105,18,146,242,179,45,110,149,52,82,207,122,198,159,191,226,43,95,154,34,137,31,92,76,13,207,0,81,216,8,191,149,153,154,48,43,189,250,143,10,43,167,124,38,49,166,20,142,59,109,84,114,146,217,152,235,68,35,255,115,140,251,110,1,73,12,164,226,59,55,157,166,87,181,210,242,63,154,234,0,213,236,11,74,127,253,113,45,123,12,181,23,9,127,242,201,91,131,69,97,5,246,19,177,41,242,47,218,180};
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		public override HostSecurityManagerOptions				Flags
		{
			get
			{
				Console.WriteLine("++++++++++ Flags is CALLED !");

				// !!! Urcuje, ake typy CUSTOMIZATION bude CMyHostSecurityManager podporovat.
				// !!! FLAG HostSecurityManagerOptions.HostPolicyLevel je OBSOLETE.
				//return(HostSecurityManagerOptions.HostAssemblyEvidence | HostSecurityManagerOptions.HostPolicyLevel);

				return(HostSecurityManagerOptions.AllFlags);
			}
		}
//------------------------------------------------------------------------------------------------------
		/*
		// !!!!! PROPERTY NIE JE VOLANA, pretoze je OBSOLETE.
        public override PolicyLevel								DomainPolicy
        {
            get 
            {
				Console.WriteLine("++++++++++ DomainPolicy is CALLED !");

				// !!! Vytvori APP DOMAIN POLICY LEVEL.
				// !!! APP DOMAIN POLICY LEVELS su OBSOLETE.
                PolicyLevel										Policy=PolicyLevel.CreateAppDomainLevel();

                Policy.RootCodeGroup.PolicyStatement=new PolicyStatement(new PermissionSet(PermissionState.None));

                // !!! Vytvori CODE GROUP s MEMBERSHIP CONDITION pre MS PLATFORM KEY.
				// !!! Do tejto CODE GROUP patria MICROSOFT ASSEMBLIES.
                UnionCodeGroup									MSKeyCG=new UnionCodeGroup(new StrongNameMembershipCondition(new StrongNamePublicKeyBlob(MMSPublicKey),null,null),new PolicyStatement(new PermissionSet(PermissionState.Unrestricted)));

                Policy.RootCodeGroup.AddChild(MSKeyCG);

                // !!! Vytvori CODE GROUP s MEMBERSHIP CONDITION pre ECMA KEY.
				// !!! Do tejto CODE GROUP patria .NET ASSEMBLIES.
                UnionCodeGroup									ECMAKeyCG=new UnionCodeGroup(new StrongNameMembershipCondition(new StrongNamePublicKeyBlob(MECMAPublicKey),null,null),new PolicyStatement(new PermissionSet(PermissionState.Unrestricted)));

                Policy.RootCodeGroup.AddChild(ECMAKeyCG);

                // Vytvori CODE GROUP s MEMBERSHIP CONDITION pre KEY, ktorym su podpisanym BAG HOST RUNTIME.
				// !!! Do tejto CODE GROUP patri BagAppDomainManager ASSEMBLY.
                UnionCodeGroup									HostKeyCG=new UnionCodeGroup(new StrongNameMembershipCondition(new StrongNamePublicKeyBlob(MBagHostRuntimePublicKey),null,null),new PolicyStatement(new PermissionSet(PermissionState.Unrestricted)));

                Policy.RootCodeGroup.AddChild(HostKeyCG);

				// !!! Vytvori PERMISSION SET, ktory GRANTUJE PERMISSIONS ASSEMBLIES, ktore splnia CUSTOM MEMBERSHIP CONDITION CMyMembershipCondition.
                PermissionSet									Set=new PermissionSet(PermissionState.None);

                // !!! Pridam PERMISSION na EXECUTE.
                Set.AddPermission(new SecurityPermission(SecurityPermissionFlag.Execution));

                // !!! Pridam PERMISSION na zobrazenie GUI.
                Set.AddPermission(new UIPermission(PermissionState.Unrestricted));

                // !!! Pridam PERMISSION na pristup k ISOLATED STORAGE.
                IsolatedStorageFilePermission					IsloatedStorePermission=new IsolatedStorageFilePermission(PermissionState.None);

                IsloatedStorePermission.UsageAllowed=IsolatedStorageContainment.DomainIsolationByUser;
                IsloatedStorePermission.UserQuota=10000;

                Set.AddPermission(IsloatedStorePermission);

				// !!! Vytvori CODE GROUP s CUSTOM MEMBERSHIP CONDITION CMyMembershipCondition a riradi jej vytvoreny PERMISSION SET.
				// !!! Do tejto CODE GROUP patria ASSEMBLIES z BAG FILE.
                UnionCodeGroup									BagCG=new UnionCodeGroup(new CMyMembershipCondition(),new PolicyStatement(Set));

                Policy.RootCodeGroup.AddChild(BagCG);

                return(Policy);
            }
        }
		*/
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		// !!! METHOD je volana pre KAZDU ASSEMBLY, ktora ma byt nacitana do niektorej APP DOMAIN. METHOD dostava EVIDENCES ako PARAMETER. Tento moze LUBOVOLNE MODIFIKOVAT a vratit v RETURN VALUE.
		public override Evidence ProvideAssemblyEvidence(Assembly LoadedAssembly,Evidence InputEvidence)
		{
            if (LoadedAssembly.HostContext==ASSEMBLY_FROM_BAG)
            {
                InputEvidence.AddHostEvidence(new Zone(SecurityZone.MyComputer));
                InputEvidence.AddHostEvidence(new CMyEvidence());

                Console.WriteLine(string.Format("++++++++++ CUSTOM EVIDENCE ADDED to ASSEMBLY [{0}] !",LoadedAssembly.FullName));
            }
			else
			{
                Console.WriteLine(string.Format("++++++++++ CUSTOM EVIDENCE NOT ADDED to ASSEMBLY [{0}] !",LoadedAssembly.FullName));
			}

            return(InputEvidence);
		}
//------------------------------------------------------------------------------------------------------
		public override PermissionSet ResolvePolicy(Evidence Evidence)
		{
            Console.WriteLine(string.Format("++++++++++ ResolvePolicy() CALLED !"));

			if (Evidence.GetHostEvidence<CMyEvidence>()!=null)
			{
	            Console.WriteLine(string.Format("++++++++++ ResolvePolicy() CALLED returning CUSTOM PERMISSIONS !"));

				// !!! Vytvori PERMISSION SET, ktory GRANTUJE PERMISSIONS ASSEMBLIES, ktore splnia CUSTOM MEMBERSHIP CONDITION CMyMembershipCondition.
                PermissionSet									Set=new PermissionSet(PermissionState.Unrestricted);

				/*
                // !!! Pridam PERMISSION na EXECUTE.
                Set.AddPermission(new SecurityPermission(SecurityPermissionFlag.AllFlags));

                // !!! Pridam PERMISSION na zobrazenie GUI.
                Set.AddPermission(new UIPermission(PermissionState.Unrestricted));

                // !!! Pridam PERMISSION na pristup k ISOLATED STORAGE.
                IsolatedStorageFilePermission					IsloatedStorePermission=new IsolatedStorageFilePermission(PermissionState.None);

                IsloatedStorePermission.UsageAllowed=IsolatedStorageContainment.DomainIsolationByUser;
                IsloatedStorePermission.UserQuota=10000;

                Set.AddPermission(IsloatedStorePermission);
				*/

				return(Set);
			}
			else
			{
	            Console.WriteLine(string.Format("++++++++++ ResolvePolicy() CALLED returning DEFAULT PERMISSIONS !"));

				return(base.ResolvePolicy(Evidence));
			}
		}
//------------------------------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------------