﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Newtonsoft.Json;
//----------------------------------------------------------------------------------------------------------------------
namespace Client
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CPaginationCursorBasedPageInfo
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MStartCursor;
		private string											MEndCursor;
		private bool											MHasPreviousPage;
		private bool											MHasNextPage;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CPaginationCursorBasedPageInfo()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[JsonProperty("startCursor")]
		public string											StartCursor
		{
			get
			{
				return(MStartCursor);
			}
			set
			{
				MStartCursor=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[JsonProperty("endCursor")]
		public string											EndCursor
		{
			get
			{
				return(MEndCursor);
			}
			set
			{
				MEndCursor=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[JsonProperty("hasPreviousPage")]
		public bool												HasPreviousPage
		{
			get
			{
				return(MHasPreviousPage);
			}
			set
			{
				MHasPreviousPage=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[JsonProperty("hasNextPage")]
		public bool												HasNextPage
		{
			get
			{
				return(MHasNextPage);
			}
			set
			{
				MHasNextPage=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------