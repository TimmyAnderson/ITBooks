using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc.ModelBinding;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication3.Models
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class COrder
	{
//----------------------------------------------------------------------------------------------------------------------
        private int												MOrderID;
        private ICollection<CCartLine>							MLines;
        private string											MName;
        private string											MLine1;
        private string											MLine2;
        private string											MLine3;
        private string											MCity;
        private string											MState;
        private string											MZip;
        private string											MCountry;
        private bool											MGiftWrap;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        [BindNever]
		[Key]
        public int												OrderID
		{
			get
			{
				return(MOrderID);
			}
			set
			{
				MOrderID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
        [BindNever]
        public ICollection<CCartLine>							Lines
		{
			get
			{
				return(MLines);
			}
			set
			{
				MLines=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
        [Required(ErrorMessage="Please enter a name.")]
        public string											Name
		{
			get
			{
				return(MName);
			}
			set
			{
				MName=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
        [Required(ErrorMessage="Please enter the first address line.")]
        public string											Line1
		{
			get
			{
				return(MLine1);
			}
			set
			{
				MLine1=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
        public string											Line2
		{
			get
			{
				return(MLine2);
			}
			set
			{
				MLine2=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
        public string											Line3
		{
			get
			{
				return(MLine3);
			}
			set
			{
				MLine3=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
        [Required(ErrorMessage="Please enter a city name.")]
        public string											City
		{
			get
			{
				return(MCity);
			}
			set
			{
				MCity=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
        [Required(ErrorMessage="Please enter a state name.")]
        public string											State
		{
			get
			{
				return(MState);
			}
			set
			{
				MState=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
        public string											Zip
		{
			get
			{
				return(MZip);
			}
			set
			{
				MZip=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
        [Required(ErrorMessage="Please enter a country name.")]
        public string											Country
		{
			get
			{
				return(MCountry);
			}
			set
			{
				MCountry=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
        public bool												GiftWrap
		{
			get
			{
				return(MGiftWrap);
			}
			set
			{
				MGiftWrap=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------