﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Templates
{
//-------------------------------------------------------------------------------------------------------
	class Employee
	{
//-------------------------------------------------------------------------------------------------------
        private string											MName;
        private string											MFace;
        private DateTime										MBirthDate;
        private bool											MLeftHanded;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public Employee()
        {
        }
//-------------------------------------------------------------------------------------------------------
        public Employee(string Name, string Face, DateTime BirthDate, bool LeftHanded)
        {
            MName=Name;
            MFace=Face;
            MBirthDate=BirthDate;
            MLeftHanded=LeftHanded;
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------------
        public string											Face
        {
            get
			{
				return(MFace);
			}
            set
			{
				MFace=value;
			}
        }
//-------------------------------------------------------------------------------------------------------
        public DateTime											BirthDate
        {
            get
			{
				return(MBirthDate);
			}
            set
			{
				MBirthDate=value;
			}
        }
//-------------------------------------------------------------------------------------------------------
        public bool												LeftHanded
        {
            get
			{
				return(MLeftHanded);
			}
            set
			{
				MLeftHanded=value;
			}
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------