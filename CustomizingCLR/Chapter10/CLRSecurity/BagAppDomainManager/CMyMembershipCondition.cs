using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Security;
using System.Security.Policy;
//------------------------------------------------------------------------------------------------------
namespace BagAppDomainManager
{
//------------------------------------------------------------------------------------------------------
	public sealed class CMyMembershipCondition : IMembershipCondition
	{
//------------------------------------------------------------------------------------------------------
        public bool Check(Evidence Evidence)
        {
            if (Evidence==null)
			{
                return(false);
			}

            IEnumerator											Enumerator=Evidence.GetHostEnumerator();

            while (Enumerator.MoveNext()==true)
            {
                Object											Object=Enumerator.Current;

                // !!! Zistujem ci medzi EVIDENCES sa nachadza CLASS CMyEvidence.
                if ((Object is CMyEvidence)==true)
                {
                    return(true);
                }
            }

            return(false);
        }
//------------------------------------------------------------------------------------------------------
        public IMembershipCondition Copy()
        {
            return(new CMyMembershipCondition());
        }
//------------------------------------------------------------------------------------------------------
        // !!! Tato METHOD je NEVYHNUTNA iba pre ENTEPRISE, MACHINE a USER POLICY LEVELS. Pre APP DOMAIN POLICY LEVEL, ktora sa pouziva v tomto priklade NIE JE implementacia tejto METHOD NEVYHNUTNA.
        public SecurityElement ToXml()
		{
			throw(new NotSupportedException());
		}
//------------------------------------------------------------------------------------------------------
        // !!! Tato METHOD je NEVYHNUTNA iba pre ENTEPRISE, MACHINE a USER POLICY LEVELS. Pre APP DOMAIN POLICY LEVEL, ktora sa pouziva v tomto priklade NIE JE implementacia tejto METHOD NEVYHNUTNA.
        public void FromXml(SecurityElement E)
		{
			throw(new NotSupportedException());
		}
//------------------------------------------------------------------------------------------------------
        // !!! Tato METHOD je NEVYHNUTNA iba pre ENTEPRISE, MACHINE a USER POLICY LEVELS. Pre APP DOMAIN POLICY LEVEL, ktora sa pouziva v tomto priklade NIE JE implementacia tejto METHOD NEVYHNUTNA.
        public SecurityElement ToXml(PolicyLevel Level)
		{
			throw(new NotSupportedException());
		}
//------------------------------------------------------------------------------------------------------
        // !!! Tato METHOD je NEVYHNUTNA iba pre ENTEPRISE, MACHINE a USER POLICY LEVELS. Pre APP DOMAIN POLICY LEVEL, ktora sa pouziva v tomto priklade NIE JE implementacia tejto METHOD NEVYHNUTNA.
        public void FromXml(SecurityElement E, PolicyLevel Level)
		{
			throw(new NotSupportedException());
		}
//------------------------------------------------------------------------------------------------------
        public override bool Equals(object Other)
        {
            CMyMembershipCondition								TypedOther=(Other as CMyMembershipCondition);

            if (TypedOther!=null)
            {
                return(true);
            }
			else
			{
				return(false);
			}
        }
//------------------------------------------------------------------------------------------------------
		public override int GetHashCode()
		{
			return(base.GetHashCode());
		}
//------------------------------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------------