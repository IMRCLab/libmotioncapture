#pragma once

#include "SeekerSDKTypes.h"

#if defined( __cplusplus )
extern "C" {
#endif

	//===============================XingYing_GetVersion===================================
	
	/** This function returns a 4-byte version number.
	 *
	 *  The format of XINGYINGLIB version is [major.minor.build.revision]
	 *
	 *  \param outVersion - [major.minor.build.revision]
	 *
	 *  \return XINGYING_API void XINGYING_CALLCONV
	*/
	XINGYING_API void XINGYING_CALLCONV XingYing_GetVersion(unsigned char outVersion[4]);


	//===============================XingYing_DecodeTimecode===================================
	
	/** This function Decode the timecode.
	 *
	 *  the timecode is ...
	 *
	 *  \param timecode
	 *  \param timecodeSubframe
	 *  \param pOutHour
	 *  \param pOutMinute
	 *  \param pOutSecond
	 *  \param pOutFrame
	 *  \param pOutSubframe
	 *
	 *  \return bool
	*/
	XINGYING_API bool XINGYING_CALLCONV XingYing_DecodeTimecode(unsigned int timecode, unsigned int timecodeSubframe, int* pOutHour, int* pOutMinute, int* pOutSecond, int* pOutFrame, int* pOutSubframe);



	//===============================XingYing_TimecodeStringify===================================
	
	/** This function Encode the timecode
	 *
	 *  
	 *
	 *  \param timecode
	 *  \param timecodeSubframe
	 *  \param outBuffer
	 *  \param outBufferSize
	 *
	 *  \return bool
	*/
	XINGYING_API bool XINGYING_CALLCONV XingYing_TimecodeStringify(unsigned int timecode, unsigned int timecodeSubframe, char* outBuffer, int outBufferSize);

	//===============================XingYing_CopyFrame===================================
	
	/** Helper that performs a deep copy from <paramref name="pSrc"/> into <paramref name="pDst"/>.
	 *
	 *  Some members of <paramref name="pDst"/> will be dynamically allocated. Call <see cref="XingYing_FreeFrame"/> to deallocate them.
	 *
	 *  \param pSrc - the const pointer of source 
	 *  \param pDst - the pointer of destination
	 *
	 *  \return XINGYING_API ErrorCode XINGYING_CALLCONV
	*/
	XINGYING_API ErrorCode XINGYING_CALLCONV XingYing_CopyFrame(const sFrameOfMocapData* pSrc, sFrameOfMocapData* pDst);

	//===============================XingYing_FreeFrame===================================
	
	/** Frees the dynamically allocated members of a frame copy created using <see cref="NatNet_CopyFrame"/>.
	 *
	 *  The object pointed to by <paramref name="pFrame"/> itself is NOT de-allocated, only its nested members which were dynamically allocated.
	 * 
	 *  Warning: Do not call this on any <paramref name="pFrame"/> that was not the destination of a call to <see cref="XingYing_CopyFrame"/>.
	 * 
	 *  \param pFrame
	 *
	 *  \return XINGYING_API ErrorCode XINGYING_CALLCONV
	*/
	XINGYING_API ErrorCode XINGYING_CALLCONV XingYing_FreeFrame(sFrameOfMocapData* pFrame);

	//===============================XingYing_FreeDescriptions===================================
	
	/** Deallocates <paramref name="pDesc"/> and all of its members; after this call, the object is no longer valid.
	 *
	 *  \param pDesc - the pointer of sDataDescriptions which need to be free
	 *
	 *  \return XINGYING_API ErrorCode XINGYING_CALLCONV
	*/
	XINGYING_API ErrorCode XINGYING_CALLCONV XingYing_FreeDescriptions(sDataDescriptions* pDesc);

#if defined( __cplusplus )
} // extern "C"
#endif
