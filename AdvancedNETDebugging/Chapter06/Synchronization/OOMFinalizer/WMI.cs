﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Runtime.InteropServices;
using System.Management;
//-------------------------------------------------------------------------------------------------------
namespace OOMFinalizer
{
//-------------------------------------------------------------------------------------------------------
	public class WMI
	{
//-------------------------------------------------------------------------------------------------------
        private ManagementClass									MObject;
        private byte[]											MData;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public WMI(byte[] Data)
        {
            MData=Data;
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Finalizer.
        ~WMI()
        {
            // Tu mozem vymazat NATIVE RESOURCES.
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public void ProcessData()
        {
            MObject=new ManagementClass("Win32_Environment");
            MObject.Get();
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------