﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace OOM
{
//-------------------------------------------------------------------------------------------------------
	public class CPerson
	{
//-------------------------------------------------------------------------------------------------------
        private string											MName;
        private string											MSocial;
        private int												MAge;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public CPerson()
		{
		}
//-------------------------------------------------------------------------------------------------------
        public CPerson(string Name, string SS, int Age)
        {
            MName=Name;
			MSocial=SS;
			MAge=Age;
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
//------------------------------------------------------------------------------------------------------
        public string											SocialSecurity 
        { 
            get
			{
				return(MSocial);
			} 
            set
			{
				MSocial=value;
			} 
        }
//------------------------------------------------------------------------------------------------------
        public int												Age 
        { 
            get
			{
				return(MAge);
			} 
            set
			{
				MAge=value;
			} 
        }
//------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------