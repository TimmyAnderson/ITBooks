using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security;
using System.Security.Policy;
using System.Security.Permissions;
using System.Security.Cryptography;
using System.Security.Cryptography.X509Certificates;
//-------------------------------------------------------------------------------------------------------
namespace SecurityAttributes
{
//-------------------------------------------------------------------------------------------------------
    [AttributeUsage(AttributeTargets.Method | AttributeTargets.Constructor | AttributeTargets.Class | AttributeTargets.Struct | AttributeTargets.Assembly,AllowMultiple=true,Inherited=false)]
	[Serializable]
	// CLASS reprezentuje CUSTOM PERMISSION ATTRIBUTE.
	public sealed class CMyCustomPermissionAttribute : CodeAccessSecurityAttribute
	{
//-------------------------------------------------------------------------------------------------------
        private EMyCustomPermissionActions						MActions=EMyCustomPermissionActions.E_NONE;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public CMyCustomPermissionAttribute(SecurityAction Actions)
			: base(Actions)
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public EMyCustomPermissionActions						Actions
		{
            get
			{
				return(MActions);
			}
            set
			{
				MActions=value;
			}
        }
//-------------------------------------------------------------------------------------------------------
        public bool												CanRead
		{
            get
			{
				if ((Actions & EMyCustomPermissionActions.E_READ)!=EMyCustomPermissionActions.E_NONE)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}
            set
			{
                if (value==true)
				{
                    Actions|=EMyCustomPermissionActions.E_READ;
                }
				else
				{
                    Actions&=~EMyCustomPermissionActions.E_WRITE;
                }
            }
        }
//-------------------------------------------------------------------------------------------------------
        public bool												CanWrite
		{
            get
			{
				if ((Actions & EMyCustomPermissionActions.E_WRITE)!=EMyCustomPermissionActions.E_NONE)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}
            set
			{
                if (value==true)
				{
                    Actions|=EMyCustomPermissionActions.E_READ;
                }
				else
				{
                    Actions&=~EMyCustomPermissionActions.E_WRITE;
                }
            }
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD vytvara instanciu PERMISSION CLASS.
        public override IPermission CreatePermission()
		{
			CMyCustomPermission									MyCustomPermission=new CMyCustomPermission(Actions);
       
            return(MyCustomPermission);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------