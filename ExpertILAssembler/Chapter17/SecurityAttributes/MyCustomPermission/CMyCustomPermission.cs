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
// !!! ASSEMBLY ma STRONG NAME.
// !!! ASSEMBLY MUSI byt zaregistrovany v GAC.
//-------------------------------------------------------------------------------------------------------
namespace SecurityAttributes
{
//-------------------------------------------------------------------------------------------------------
	// !!! CUSTOM PERMISSION MUSI byt SERIALIZABLE.
	[Serializable]
	// CLASS reprezentuje CUSTOM PERMISSION.
    public sealed class CMyCustomPermission : CodeAccessPermission, IUnrestrictedPermission
    {
//-------------------------------------------------------------------------------------------------------
        private EMyCustomPermissionActions						MActions;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public CMyCustomPermission(PermissionState State)
		{
            if (State==PermissionState.None)
			{
                this.Actions=EMyCustomPermissionActions.E_NONE;
            }
			else if (State==PermissionState.Unrestricted)
			{
                this.Actions=EMyCustomPermissionActions.E_ALL;
            }
			else
			{
				throw(new ArgumentException("State contains INVALID VALUE !"));
            }
        }
//-------------------------------------------------------------------------------------------------------
        public CMyCustomPermission(EMyCustomPermissionActions Actions)
		{   
			this.Actions=Actions;
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
				if (Enum.IsDefined(typeof(EMyCustomPermissionActions),value)==false)
				{
					throw(new ArgumentException("Actions contains INVALID VALUE !"));
				}

				MActions=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Vykona DEEP COPY instancie CMyCustomPermission.
		public override IPermission Copy()
		{
			Console.WriteLine("!!! METHOD CMyCustomPermission.Copy() CALLED !");

			CMyCustomPermission									NewPermission=new CMyCustomPermission(Actions);

			return(NewPermission);
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Vykonava INTERSECTION instanciu CMyCustomPermission s inou instanciou CMyCustomPermission.
		public override IPermission Intersect(IPermission Target)
		{
			Console.WriteLine("!!! METHOD CMyCustomPermission.Intersect() CALLED !");

            if (Target==null)
			{
                return(null);            
            } 

            if ((Target is CMyCustomPermission)==true)
			{
				CMyCustomPermission								TypedPermission=(CMyCustomPermission) Target;
				EMyCustomPermissionActions						Actions=(this.Actions & TypedPermission.Actions);
				CMyCustomPermission								NewPermission=new CMyCustomPermission(Actions);

                return(NewPermission);
            }
			else
			{
				throw(new ArgumentException("Target contains INVALID VALUE !"));
            }
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Vykonava UNION instancie CMyCustomPermission s inou instanciou CMyCustomPermission.
		public override IPermission Union(IPermission Target)
		{
			Console.WriteLine("!!! METHOD CMyCustomPermission.Union() CALLED !");

            if (Target==null)
			{
                return(null);    
            }
			
            if ((Target is CMyCustomPermission)==true)
			{
				CMyCustomPermission								TypedPermission=(CMyCustomPermission) Target;
				EMyCustomPermissionActions						Actions=(this.Actions | TypedPermission.Actions);
				CMyCustomPermission								NewPermission=new CMyCustomPermission(Actions);

                return(NewPermission);
			}
			else
			{
				throw(new ArgumentException("Target contains INVALID VALUE !"));
            }
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Urcuje ci CURRENT instancia CMyCustomPermission je SUBSET zadanej instancii CMyCustomPermission.
		public override bool IsSubsetOf(IPermission Target)
		{
			Console.WriteLine("!!! METHOD CMyCustomPermission.IsSubsetOf() CALLED !");

            if (Target==null)
			{
                return(false);
            } 

            if ((Target is CMyCustomPermission)==true)
			{
				CMyCustomPermission								TypedPermission=(CMyCustomPermission) Target;
				EMyCustomPermissionActions						Actions=(this.Actions & (~TypedPermission.Actions));

				if (Actions==EMyCustomPermissionActions.E_NONE)
				{
					return(true);
				}
				else
				{
					return(false);
				}
            }
			else
			{
				throw(new ArgumentException("Target contains INVALID VALUE !"));
            }
		}
//-------------------------------------------------------------------------------------------------------
		public override void FromXml(SecurityElement Element)
		{
			Console.WriteLine("!!! METHOD CMyCustomPermission.FromXml() CALLED !");

			if (Element==null)
			{
				throw(new ArgumentNullException("Element MUST NOT be NULL !"));
			}

            if (Element.Tag!="IPermission")
			{
				throw new ArgumentException("Element MUST be IPermission !");
            }
			else
			{
                if (Element.Attribute("Unrestricted")=="true")
				{
					Actions=EMyCustomPermissionActions.E_ALL;
                }
				else
				{
					Actions=EMyCustomPermissionActions.E_NONE;
        
                    if (Element.Attribute("Read")=="true")
					{
                        Actions=(Actions | EMyCustomPermissionActions.E_READ);
                    }

                    if (Element.Attribute("Write")=="true")
					{
                        Actions=(Actions | EMyCustomPermissionActions.E_WRITE);
                    }
                }
            }
		}
//-------------------------------------------------------------------------------------------------------
		public override SecurityElement ToXml()
		{
			Console.WriteLine("!!! METHOD CMyCustomPermission.ToXml() CALLED !");

            SecurityElement										Element=new SecurityElement("IPermission");

            Element.AddAttribute("class",GetType().AssemblyQualifiedName);
            Element.AddAttribute("version","1");

            if (IsUnrestricted()==true)
			{
                Element.AddAttribute("Unrestricted","true");
			}
			else
			{
                if ((Actions & EMyCustomPermissionActions.E_READ)!=EMyCustomPermissionActions.E_NONE)
				{
                    Element.AddAttribute("Read","true");
                }

                if ((Actions & EMyCustomPermissionActions.E_WRITE)!=EMyCustomPermissionActions.E_NONE)
				{
                    Element.AddAttribute("Write","true");
                }
			}

			return(Element);
		}
//-------------------------------------------------------------------------------------------------------
		public bool IsUnrestricted()
		{
			Console.WriteLine("!!! METHOD CMyCustomPermission.IsUnrestricted() CALLED !");

			if (Actions==EMyCustomPermissionActions.E_ALL)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------