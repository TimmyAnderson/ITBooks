using System;
using System.Collections.Generic;
using System.Text;
//------------------------------------------------------------------------
namespace DissectingControls
{
//------------------------------------------------------------------------
    public class CTypeComparer : IComparer<Type>
    {
//------------------------------------------------------------------------
        public int Compare(Type X, Type Y)
        {
            return(X.Name.CompareTo(Y.Name));
        }
//------------------------------------------------------------------------
    }
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------