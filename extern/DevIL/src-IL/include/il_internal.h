//-----------------------------------------------------------------------------
//
// ImageLib Sources
// Copyright (C) 2000-2002 by Denton Woods
// Last modified: 02/19/2002 <--Y2K Compliant! =]
//
// Filename: src-IL/include/il_internal.h
//
// Description: Internal stuff for DevIL
//
//-----------------------------------------------------------------------------
#ifndef INTERNAL_H
#define INTERNAL_H
#define _IL_BUILD_LIBRARY

// Standard headers
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// Local headers
#define HAVE_CONFIG_H

#ifdef HAVE_CONFIG_H
#include <IL/config.h>
#endif

#include <IL/il.h>
#include <IL/devil_internal_exports.h>
#include "il_files.h"
#include "il_endian.h"

// Windows-specific
#ifdef _WIN32
#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#pragma intrinsic(memcpy)
#pragma intrinsic(memset)
#pragma intrinsic(strcmp)
#pragma intrinsic(strlen)
#pragma intrinsic(strcpy)
#endif // _MSC_VER > 1000
#endif // _MSC_VER
 
#define WIN32_LEAN_AND_MEAN				// Exclude rarely-used stuff from Windows headers
#include <windows.h>
#endif // _WIN32

#ifdef _UNICODE
#define IL_TEXT(s)	L##s
#else
#define IL_TEXT(s)	(s)
#endif

extern ILimage*	 iCurImage;
#define BIT_0	0x00000001
#define BIT_1	0x00000002
#define BIT_2	0x00000004
#define BIT_3	0x00000008
#define BIT_4	0x00000010
#define BIT_5	0x00000020
#define BIT_6	0x00000040
#define BIT_7	0x00000080
#define BIT_8	0x00000100
#define BIT_9	0x00000200
#define BIT_10	0x00000400
#define BIT_11	0x00000800
#define BIT_12	0x00001000
#define BIT_13	0x00002000
#define BIT_14	0x00004000
#define BIT_15	0x00008000
#define BIT_16	0x00010000
#define BIT_17	0x00020000
#define BIT_18	0x00040000
#define BIT_19	0x00080000
#define BIT_20	0x00100000
#define BIT_21	0x00200000
#define BIT_22	0x00400000
#define BIT_23	0x00800000
#define BIT_24	0x01000000
#define BIT_25	0x02000000
#define BIT_26	0x04000000
#define BIT_27	0x08000000
#define BIT_28	0x10000000
#define BIT_29	0x20000000
#define BIT_30	0x40000000
#define BIT_31	0x80000000
#define NUL		'\0'					// Easier to type and ?portable?

#if !_WIN32 || _WIN32_WCE
int stricmp(const char* src1, const char* src2);
int strnicmp(const char* src1, const char* src2, size_t max);
#endif //_WIN32

int iStrCmp(const ILstring src1, const ILstring src2);

//
// Some math functions
//
// A fast integer squareroot, completely accurate for x < 289.
// Taken from http://atoms.org.uk/sqrt/
// There is also a version that is accurate for all integers
// < 2^31, if we should need it
int iSqrt(int x);

//
// Useful miscellaneous functions
//
ILboolean iCheckExtension(const ILstring Arg, const ILstring Ext);
ILbyte*	 iFgets(char* buffer, ILuint maxlen);
ILboolean iFileExists(const ILstring FileName);
ILstring iGetExtension(const ILstring FileName);
char*  ilStrDup(const char* Str);
ILuint ilStrLen(const char* Str);

// Miscellaneous functions
ILvoid ilDefaultStates(ILvoid);
ILenum iGetHint(ILenum Target);
ILint iGetInt(ILenum Mode);
ILvoid ilRemoveRegistered(ILvoid);
ILAPI ILvoid ILAPIENTRY ilSetCurImage(ILimage* Image);

//
// Rle compression
//
#define IL_TGACOMP	0x01
#define IL_PCXCOMP	0x02
#define IL_SGICOMP	0x03
#define IL_BMPCOMP	0x04
ILboolean ilRleCompressLine(ILubyte* ScanLine, ILuint Width, ILubyte Bpp, ILubyte* Dest, ILuint* DestWidth, ILenum CompressMode);
ILuint ilRleCompress(ILubyte* Data, ILuint Width, ILuint Height, ILuint Depth, ILubyte Bpp, ILubyte* Dest, ILenum CompressMode, ILuint* ScanTable);
ILvoid iSetImage0(ILvoid);

// Conversion functions
ILboolean ilAddAlpha(ILvoid);
ILboolean ilAddAlphaKey(ILimage* Image);
ILboolean iFastConvert(ILenum DestFormat);
ILboolean ilFixImage(ILvoid);
ILboolean ilRemoveAlpha(ILvoid);
ILboolean ilSwapColours(ILvoid);

// Miscellaneous functions
char*  iGetString(ILenum StringName);	// Internal version of ilGetString

//
// Image loading/saving functions
//
ILboolean ilIsValidBmp(const ILstring FileName);
ILboolean ilIsValidBmpF(ILHANDLE File);
ILboolean ilIsValidBmpL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadBmp(const ILstring FileName);
ILboolean ilLoadBmpF(ILHANDLE File);
ILboolean ilLoadBmpL(const ILvoid* Lump, ILuint Size);
ILboolean ilSaveBmp(const ILstring FileName);
ILboolean ilSaveBmpF(ILHANDLE File);
ILboolean ilSaveBmpL(ILvoid* Lump, ILuint Size);
ILboolean ilSaveCHeader(const ILstring FileName, const char* InternalName);
ILboolean ilLoadCut(const ILstring FileName);
ILboolean ilLoadCutF(ILHANDLE File);
ILboolean ilLoadCutL(const ILvoid* Lump, ILuint Size);
ILboolean ilIsValidDcx(const ILstring FileName);
ILboolean ilIsValidDcxF(ILHANDLE File);
ILboolean ilIsValidDcxL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadDcx(const ILstring FileName);
ILboolean ilLoadDcxF(ILHANDLE File);
ILboolean ilLoadDcxL(const ILvoid* Lump, ILuint Size);
ILboolean ilIsValidDds(const ILstring FileName);
ILboolean ilIsValidDdsF(ILHANDLE File);
ILboolean ilIsValidDdsL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadDds(const ILstring FileName);
ILboolean ilLoadDdsF(ILHANDLE File);
ILboolean ilLoadDdsL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadPvr(const ILstring FileName);
ILboolean ilLoadPvrF(ILHANDLE File);
ILboolean ilLoadPvrL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadKtx(const ILstring FileName);
ILboolean ilLoadKtxF(ILHANDLE File);
ILboolean ilLoadKtxL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadAtc(const ILstring FileName);
ILboolean ilLoadAtcF(ILHANDLE File);
ILboolean ilLoadAtcL(const ILvoid* Lump, ILuint Size);
ILboolean ilSaveDds(const ILstring FileName);
ILboolean ilSaveDdsF(ILHANDLE File);
ILboolean ilSaveDdsL(ILvoid* Lump, ILuint Size);
ILboolean ilLoadDoom(const ILstring FileName);
ILboolean ilLoadDoomF(ILHANDLE File);
ILboolean ilLoadDoomL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadDoomFlat(const ILstring FileName);
ILboolean ilLoadDoomFlatF(ILHANDLE File);
ILboolean ilLoadDoomFlatL(const ILvoid* Lump, ILuint Size);
ILboolean ilIsValidGif(const ILstring FileName);
ILboolean ilIsValidGifF(ILHANDLE File);
ILboolean ilIsValidGifL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadGif(const ILstring FileName);
ILboolean ilLoadGifF(ILHANDLE File);
ILboolean ilLoadGifL(const ILvoid* Lump, ILuint Size);
ILboolean ilIsValidHdr(const ILstring FileName);
ILboolean ilIsValidHdrF(ILHANDLE File);
ILboolean ilIsValidHdrL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadHdr(const ILstring FileName);
ILboolean ilLoadHdrF(ILHANDLE File);
ILboolean ilLoadHdrL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadIcon(const ILstring FileName);
ILboolean ilLoadIconF(ILHANDLE File);
ILboolean ilLoadIconL(const ILvoid* Lump, ILuint Size);
ILboolean ilIsValidJpg(const ILstring FileName);
ILboolean ilIsValidJpgF(ILHANDLE File);
ILboolean ilIsValidJpgL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadJpeg(const ILstring FileName);
ILboolean ilLoadJpegF(ILHANDLE File);
ILboolean ilLoadJpegL(const ILvoid* Lump, ILuint Size);
ILboolean ilSaveJpeg(const ILstring FileName);
ILboolean ilSaveJpegF(ILHANDLE File);
ILboolean ilSaveJpegL(ILvoid* Lump, ILuint Size);
ILboolean ilIsValidLif(const ILstring FileName);
ILboolean ilIsValidLifF(ILHANDLE File);
ILboolean ilIsValidLifL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadLif(const ILstring FileName);
ILboolean ilLoadLifF(ILHANDLE File);
ILboolean ilLoadLifL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadMdl(const ILstring FileName);
ILboolean ilLoadMdlF(ILHANDLE File);
ILboolean ilLoadMdlL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadMng(const ILstring FileName);
ILboolean ilLoadMngF(ILHANDLE File);
ILboolean ilLoadMngL(const ILvoid* Lump, ILuint Size);
ILboolean ilSaveMng(const ILstring FileName);
ILboolean ilSaveMngF(ILHANDLE File);
ILboolean ilSaveMngL(ILvoid* Lump, ILuint Size);
ILboolean ilLoadPcd(const ILstring FileName);
ILboolean ilLoadPcdF(ILHANDLE File);
ILboolean ilLoadPcdL(const ILvoid* Lump, ILuint Size);
ILboolean ilIsValidPcx(const ILstring FileName);
ILboolean ilIsValidPcxF(ILHANDLE File);
ILboolean ilIsValidPcxL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadPcx(const ILstring FileName);
ILboolean ilLoadPcxF(ILHANDLE File);
ILboolean ilLoadPcxL(const ILvoid* Lump, ILuint Size);
ILboolean ilSavePcx(const ILstring FileName);
ILboolean ilSavePcxF(ILHANDLE File);
ILboolean ilSavePcxL(ILvoid* Lump, ILuint Size);
ILboolean ilIsValidPic(const ILstring FileName);
ILboolean ilIsValidPicF(ILHANDLE File);
ILboolean ilIsValidPicL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadPic(const ILstring FileName);
ILboolean ilLoadPicF(ILHANDLE File);
ILboolean ilLoadPicL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadPix(const ILstring FileName);
ILboolean ilLoadPixF(ILHANDLE File);
ILboolean ilLoadPixL(const ILvoid* Lump, ILuint Size);
ILboolean ilIsValidPng(const ILstring FileName);
ILboolean ilIsValidPngF(ILHANDLE File);
ILboolean ilIsValidPngL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadPng(const ILstring FileName);
ILboolean ilLoadPngF(ILHANDLE File);
ILboolean ilLoadPngL(const ILvoid* Lump, ILuint Size);
ILboolean ilSavePng(const ILstring FileName);
ILboolean ilSavePngF(ILHANDLE File);
ILboolean ilSavePngL(ILvoid* Lump, ILuint Size);
ILboolean ilIsValidPnm(const ILstring FileName);
ILboolean ilIsValidPnmF(ILHANDLE File);
ILboolean ilIsValidPnmL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadPnm(const ILstring FileName);
ILboolean ilLoadPnmF(ILHANDLE File);
ILboolean ilLoadPnmL(const ILvoid* Lump, ILuint Size);
ILboolean ilSavePnm(const ILstring FileName);
ILboolean ilSavePnmF(ILHANDLE File);
ILboolean ilSavePnmL(ILvoid* Lump, ILuint Size);
ILboolean ilIsValidPsd(const ILstring FileName);
ILboolean ilIsValidPsdF(ILHANDLE File);
ILboolean ilIsValidPsdL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadPsd(const ILstring FileName);
ILboolean ilLoadPsdF(ILHANDLE File);
ILboolean ilLoadPsdL(const ILvoid* Lump, ILuint Size);
ILboolean ilSavePsd(const ILstring FileName);
ILboolean ilSavePsdF(ILHANDLE File);
ILboolean ilSavePsdL(ILvoid* Lump, ILuint Size);
ILboolean ilIsValidPsp(const ILstring FileName);
ILboolean ilIsValidPspF(ILHANDLE File);
ILboolean ilIsValidPspL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadPsp(const ILstring FileName);
ILboolean ilLoadPspF(ILHANDLE File);
ILboolean ilLoadPspL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadPxr(const ILstring FileName);
ILboolean ilLoadPxrF(ILHANDLE File);
ILboolean ilLoadPxrL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadRaw(const ILstring FileName);
ILboolean ilLoadRawF(ILHANDLE File);
ILboolean ilLoadRawL(const ILvoid* Lump, ILuint Size);
ILboolean ilSaveRaw(const ILstring FileName);
ILboolean ilSaveRawF(ILHANDLE File);
ILboolean ilSaveRawL(ILvoid* Lump, ILuint Size);
ILboolean ilIsValidSgi(const ILstring FileName);
ILboolean ilIsValidSgiF(ILHANDLE File);
ILboolean ilIsValidSgiL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadSgi(const ILstring FileName);
ILboolean ilLoadSgiF(ILHANDLE File);
ILboolean ilLoadSgiL(const ILvoid* Lump, ILuint Size);
ILboolean ilSaveSgi(const ILstring FileName);
ILboolean ilSaveSgiF(ILHANDLE File);
ILboolean ilSaveSgiL(ILvoid* Lump, ILuint Size);
ILboolean ilIsValidTga(const ILstring FileName);
ILboolean ilIsValidTgaF(ILHANDLE File);
ILboolean ilIsValidTgaL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadTarga(const ILstring FileName);
ILboolean ilLoadTargaF(ILHANDLE File);
ILboolean ilLoadTargaL(const ILvoid* Lump, ILuint Size);
ILboolean ilSaveTarga(const ILstring FileName);
ILboolean ilSaveTargaF(ILHANDLE File);
ILboolean ilSaveTargaL(ILvoid* Lump, ILuint Size);
ILboolean ilIsValidTiff(const ILstring FileName);
ILboolean ilIsValidTiffF(ILHANDLE File);
ILboolean ilIsValidTiffL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadTiff(const ILstring FileName);
ILboolean ilLoadTiffF(ILHANDLE File);
ILboolean ilLoadTiffL(const ILvoid* Lump, ILuint Size);
ILboolean ilSaveTiff(const ILstring FileName);
ILboolean ilSaveTiffF(ILHANDLE File);
ILboolean ilSaveTiffL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadWal(const ILstring FileName);
ILboolean ilLoadWalF(ILHANDLE File);
ILboolean ilLoadWalL(const ILvoid* Lump, ILuint Size);
ILboolean ilLoadXpm(const ILstring FileName);
ILboolean ilLoadXpmF(ILHANDLE File);
ILboolean ilLoadXpmL(const ILvoid* Lump, ILuint Size);
#endif //INTERNAL_H