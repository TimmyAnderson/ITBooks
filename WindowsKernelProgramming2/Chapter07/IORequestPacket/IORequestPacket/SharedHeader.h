//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#define CODE_TEST_DEBUG_IRP 0x801
#define CODE_GET_STATUS 0x802
#define CODE_CLEAR_STATUS 0x803
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct SReadWriteStatistics final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		long long												MTotalReadBytes;
		long long												MTotalWriteBytes;

	public:
		long long GetTotalReadBytes(void) const
		{
			return(MTotalReadBytes);
		}

		void SetTotalReadBytes(long long Value)
		{
			MTotalReadBytes=Value;
		}

		long long GetTotalWriteBytes(void) const
		{
			return(MTotalWriteBytes);
		}

		void SetTotalWriteBytes(long long Value)
		{
			MTotalWriteBytes=Value;
		}

	public:
		SReadWriteStatistics(void)
			: MTotalReadBytes(), MTotalWriteBytes()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------