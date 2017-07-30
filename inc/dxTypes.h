/*==========================================================================;
 *
 *  Copyright (C) 1995-1998 Microsoft Corporation.  All Rights Reserved.
 *
 ***************************************************************************/

/**
 * @file
 * @brief DirectX 7 SDK types
 *
 * This file contains fragments of DirectX 7 SDK adapted for pure C
 *
 * @cond Doxygen_Suppress
 */

#ifndef __DXTYPES_H__
#define __DXTYPES_H__

#include <windows.h>

/*
 * Wait until the device is ready to draw the primitive
 * This will cause DP to not return DDERR_WASSTILLDRAWING
 */
#define D3DDP_WAIT                  0x00000001l

/*
 * Hint that it is acceptable to render the primitive out of order.
 */
#define D3DDP_OUTOFORDER            0x00000002l

/*
 * Hint that the primitives have been clipped by the application.
 */
#define D3DDP_DONOTCLIP             0x00000004l

/*
 * Hint that the extents need not be updated.
 */
#define D3DDP_DONOTUPDATEEXTENTS    0x00000008l

/* D3DVALUE is the fundamental Direct3D fractional data type */

#define D3DVALP(val, prec) ((float)(val))
#define D3DVAL(val) ((float)(val))
typedef float D3DVALUE, *LPD3DVALUE;
#define D3DDivide(a, b)    (float)((double) (a) / (double) (b))
#define D3DMultiply(a, b)    ((a) * (b))

typedef LONG D3DFIXED;

typedef DWORD D3DCOLOR, *LPD3DCOLOR;

#ifndef RGB_MAKE
/*
 * Format of CI colors is
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |    alpha      |         color index           |   fraction    |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
#define CI_GETALPHA(ci)    ((ci) >> 24)
#define CI_GETINDEX(ci)    (((ci) >> 8) & 0xffff)
#define CI_GETFRACTION(ci) ((ci) & 0xff)
#define CI_ROUNDINDEX(ci)  CI_GETINDEX((ci) + 0x80)
#define CI_MASKALPHA(ci)   ((ci) & 0xffffff)
#define CI_MAKE(a, i, f)    (((a) << 24) | ((i) << 8) | (f))

/*
 * Format of RGBA colors is
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |    alpha      |      red      |     green     |     blue      |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
#define RGBA_GETALPHA(rgb)      ((rgb) >> 24)
#define RGBA_GETRED(rgb)        (((rgb) >> 16) & 0xff)
#define RGBA_GETGREEN(rgb)      (((rgb) >> 8) & 0xff)
#define RGBA_GETBLUE(rgb)       ((rgb) & 0xff)
#define RGBA_MAKE(r, g, b, a)   ((D3DCOLOR) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))

/* D3DRGB and D3DRGBA may be used as initializers for D3DCOLORs
 * The float values must be in the range 0..1
 */
#define D3DRGB(r, g, b) \
    (0xff000000L | ( ((long)((r) * 255)) << 16) | (((long)((g) * 255)) << 8) | (long)((b) * 255))
#define D3DRGBA(r, g, b, a) \
    (   (((long)((a) * 255)) << 24) | (((long)((r) * 255)) << 16) \
    |   (((long)((g) * 255)) << 8) | (long)((b) * 255) \
    )

/*
 * Format of RGB colors is
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |    ignored    |      red      |     green     |     blue      |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
#define RGB_GETRED(rgb)         (((rgb) >> 16) & 0xff)
#define RGB_GETGREEN(rgb)       (((rgb) >> 8) & 0xff)
#define RGB_GETBLUE(rgb)        ((rgb) & 0xff)
#define RGBA_SETALPHA(rgba, x)  (((x) << 24) | ((rgba) & 0x00ffffff))
#define RGB_MAKE(r, g, b)       ((D3DCOLOR) (((r) << 16) | ((g) << 8) | (b)))
#define RGBA_TORGB(rgba)        ((D3DCOLOR) ((rgba) & 0xffffff))
#define RGB_TORGBA(rgb)         ((D3DCOLOR) ((rgb) | 0xff000000))

#endif

/*
 * Transformed/lit vertices
 */
typedef struct _D3DTLVERTEX {
	union {
	D3DVALUE	sx;			/* Screen coordinates */
	D3DVALUE	dvSX;
	};
	union {
	D3DVALUE	sy;
	D3DVALUE	dvSY;
	};
	union {
	D3DVALUE	sz;
	D3DVALUE	dvSZ;
	};
	union {
	D3DVALUE	rhw;		/* Reciprocal of homogeneous w */
	D3DVALUE	dvRHW;
	};
	union {
	D3DCOLOR	color;		/* Vertex color */
	D3DCOLOR	dcColor;
	};
	union {
	D3DCOLOR	specular;	/* Specular component of vertex */
	D3DCOLOR	dcSpecular;
	};
	union {
	D3DVALUE	tu;			/* Texture coordinates */
	D3DVALUE	dvTU;
	};
	union {
	D3DVALUE	tv;
	D3DVALUE	dvTV;
	};
} D3DTLVERTEX, *LPD3DTLVERTEX;

typedef enum _D3DPRIMITIVETYPE {
	D3DPT_POINTLIST     = 1,
	D3DPT_LINELIST      = 2,
	D3DPT_LINESTRIP     = 3,
	D3DPT_TRIANGLELIST  = 4,
	D3DPT_TRIANGLESTRIP = 5,
	D3DPT_TRIANGLEFAN   = 6,
	D3DPT_FORCE_DWORD   = 0x7fffffff,
} D3DPRIMITIVETYPE;

typedef enum _D3DVERTEXTYPE {
	D3DVT_VERTEX        = 1,
	D3DVT_LVERTEX       = 2,
	D3DVT_TLVERTEX      = 3,
	D3DVT_FORCE_DWORD   = 0x7fffffff,
} D3DVERTEXTYPE;

typedef enum _D3DRENDERSTATETYPE {
	D3DRENDERSTATE_ANTIALIAS          = 2,    /* D3DANTIALIASMODE */
	D3DRENDERSTATE_TEXTUREPERSPECTIVE = 4,    /* TRUE for perspective correction */
	D3DRENDERSTATE_ZENABLE            = 7,    /* D3DZBUFFERTYPE (or TRUE/FALSE for legacy) */
	D3DRENDERSTATE_FILLMODE           = 8,    /* D3DFILL_MODE        */
	D3DRENDERSTATE_SHADEMODE          = 9,    /* D3DSHADEMODE */
	D3DRENDERSTATE_LINEPATTERN        = 10,   /* D3DLINEPATTERN */
	D3DRENDERSTATE_ZWRITEENABLE       = 14,   /* TRUE to enable z writes */
	D3DRENDERSTATE_ALPHATESTENABLE    = 15,   /* TRUE to enable alpha tests */
	D3DRENDERSTATE_LASTPIXEL          = 16,   /* TRUE for last-pixel on lines */
	D3DRENDERSTATE_SRCBLEND           = 19,   /* D3DBLEND */
	D3DRENDERSTATE_DESTBLEND          = 20,   /* D3DBLEND */
	D3DRENDERSTATE_CULLMODE           = 22,   /* D3DCULL */
	D3DRENDERSTATE_ZFUNC              = 23,   /* D3DCMPFUNC */
	D3DRENDERSTATE_ALPHAREF           = 24,   /* D3DFIXED */
	D3DRENDERSTATE_ALPHAFUNC          = 25,   /* D3DCMPFUNC */
	D3DRENDERSTATE_DITHERENABLE       = 26,   /* TRUE to enable dithering */
	D3DRENDERSTATE_ALPHABLENDENABLE   = 27,   /* TRUE to enable alpha blending */
	D3DRENDERSTATE_FOGENABLE          = 28,   /* TRUE to enable fog blending */
	D3DRENDERSTATE_SPECULARENABLE     = 29,   /* TRUE to enable specular */
	D3DRENDERSTATE_ZVISIBLE           = 30,   /* TRUE to enable z checking */
	D3DRENDERSTATE_STIPPLEDALPHA      = 33,   /* TRUE to enable stippled alpha (RGB device only) */
	D3DRENDERSTATE_FOGCOLOR           = 34,   /* D3DCOLOR */
	D3DRENDERSTATE_FOGTABLEMODE       = 35,   /* D3DFOGMODE */
	D3DRENDERSTATE_FOGSTART           = 36,   /* Fog start (for both vertex and pixel fog) */
	D3DRENDERSTATE_FOGEND             = 37,   /* Fog end      */
	D3DRENDERSTATE_FOGDENSITY         = 38,   /* Fog density  */
	D3DRENDERSTATE_EDGEANTIALIAS      = 40,   /* TRUE to enable edge antialiasing */
	D3DRENDERSTATE_COLORKEYENABLE     = 41,   /* TRUE to enable source colorkeyed textures */
	D3DRENDERSTATE_ZBIAS              = 47,   /* LONG Z bias */
	D3DRENDERSTATE_RANGEFOGENABLE     = 48,   /* Enables range-based fog */
	D3DRENDERSTATE_STENCILENABLE      = 52,   /* BOOL enable/disable stenciling */
	D3DRENDERSTATE_STENCILFAIL        = 53,   /* D3DSTENCILOP to do if stencil test fails */
	D3DRENDERSTATE_STENCILZFAIL       = 54,   /* D3DSTENCILOP to do if stencil test passes and Z test fails */
	D3DRENDERSTATE_STENCILPASS        = 55,   /* D3DSTENCILOP to do if both stencil and Z tests pass */
	D3DRENDERSTATE_STENCILFUNC        = 56,   /* D3DCMPFUNC fn.  Stencil Test passes if ((ref & mask) stencilfn (stencil & mask)) is true */
	D3DRENDERSTATE_STENCILREF         = 57,   /* Reference value used in stencil test */
	D3DRENDERSTATE_STENCILMASK        = 58,   /* Mask value used in stencil test */
	D3DRENDERSTATE_STENCILWRITEMASK   = 59,   /* Write mask applied to values written to stencil buffer */
	D3DRENDERSTATE_TEXTUREFACTOR      = 60,   /* D3DCOLOR used for multi-texture blend */
	/*
	 * 128 values [128, 255] are reserved for texture coordinate wrap flags.
	 * These are constructed with the D3DWRAP_U and D3DWRAP_V macros. Using
	 * a flags word preserves forward compatibility with texture coordinates
	 * that are >2D.
	 */
	D3DRENDERSTATE_WRAP0              = 128,  /* wrap for 1st texture coord. set */
	D3DRENDERSTATE_WRAP1              = 129,  /* wrap for 2nd texture coord. set */
	D3DRENDERSTATE_WRAP2              = 130,  /* wrap for 3rd texture coord. set */
	D3DRENDERSTATE_WRAP3              = 131,  /* wrap for 4th texture coord. set */
	D3DRENDERSTATE_WRAP4              = 132,  /* wrap for 5th texture coord. set */
	D3DRENDERSTATE_WRAP5              = 133,  /* wrap for 6th texture coord. set */
	D3DRENDERSTATE_WRAP6              = 134,  /* wrap for 7th texture coord. set */
	D3DRENDERSTATE_WRAP7              = 135,  /* wrap for 8th texture coord. set */
	D3DRENDERSTATE_CLIPPING            = 136,
	D3DRENDERSTATE_LIGHTING            = 137,
	D3DRENDERSTATE_EXTENTS             = 138,
	D3DRENDERSTATE_AMBIENT             = 139,
	D3DRENDERSTATE_FOGVERTEXMODE       = 140,
	D3DRENDERSTATE_COLORVERTEX         = 141,
	D3DRENDERSTATE_LOCALVIEWER         = 142,
	D3DRENDERSTATE_NORMALIZENORMALS    = 143,
	D3DRENDERSTATE_COLORKEYBLENDENABLE = 144,
	D3DRENDERSTATE_DIFFUSEMATERIALSOURCE    = 145,
	D3DRENDERSTATE_SPECULARMATERIALSOURCE   = 146,
	D3DRENDERSTATE_AMBIENTMATERIALSOURCE    = 147,
	D3DRENDERSTATE_EMISSIVEMATERIALSOURCE   = 148,
	D3DRENDERSTATE_VERTEXBLEND              = 151,
	D3DRENDERSTATE_CLIPPLANEENABLE          = 152,
//
// retired renderstates - not supported for DX7 interfaces
//
	D3DRENDERSTATE_TEXTUREHANDLE      = 1,    /* Texture handle for legacy interfaces (Texture,Texture2) */
	D3DRENDERSTATE_TEXTUREADDRESS     = 3,    /* D3DTEXTUREADDRESS  */
	D3DRENDERSTATE_WRAPU              = 5,    /* TRUE for wrapping in u */
	D3DRENDERSTATE_WRAPV              = 6,    /* TRUE for wrapping in v */
	D3DRENDERSTATE_MONOENABLE         = 11,   /* TRUE to enable mono rasterization */
	D3DRENDERSTATE_ROP2               = 12,   /* ROP2 */
	D3DRENDERSTATE_PLANEMASK          = 13,   /* DWORD physical plane mask */
	D3DRENDERSTATE_TEXTUREMAG         = 17,   /* D3DTEXTUREFILTER */
	D3DRENDERSTATE_TEXTUREMIN         = 18,   /* D3DTEXTUREFILTER */
	D3DRENDERSTATE_TEXTUREMAPBLEND    = 21,   /* D3DTEXTUREBLEND */
	D3DRENDERSTATE_SUBPIXEL           = 31,   /* TRUE to enable subpixel correction */
	D3DRENDERSTATE_SUBPIXELX          = 32,   /* TRUE to enable correction in X only */
	D3DRENDERSTATE_STIPPLEENABLE      = 39,   /* TRUE to enable stippling */
	D3DRENDERSTATE_BORDERCOLOR        = 43,   /* Border color for texturing w/border */
	D3DRENDERSTATE_TEXTUREADDRESSU    = 44,   /* Texture addressing mode for U coordinate */
	D3DRENDERSTATE_TEXTUREADDRESSV    = 45,   /* Texture addressing mode for V coordinate */
	D3DRENDERSTATE_MIPMAPLODBIAS      = 46,   /* D3DVALUE Mipmap LOD bias */
	D3DRENDERSTATE_ANISOTROPY         = 49,   /* Max. anisotropy. 1 = no anisotropy */
	D3DRENDERSTATE_FLUSHBATCH         = 50,   /* Explicit flush for DP batching (DX5 Only) */
	D3DRENDERSTATE_TRANSLUCENTSORTINDEPENDENT=51, /* BOOL enable sort-independent transparency */
	D3DRENDERSTATE_STIPPLEPATTERN00   = 64,   /* Stipple pattern 01...  */
	D3DRENDERSTATE_STIPPLEPATTERN01   = 65,
	D3DRENDERSTATE_STIPPLEPATTERN02   = 66,
	D3DRENDERSTATE_STIPPLEPATTERN03   = 67,
	D3DRENDERSTATE_STIPPLEPATTERN04   = 68,
	D3DRENDERSTATE_STIPPLEPATTERN05   = 69,
	D3DRENDERSTATE_STIPPLEPATTERN06   = 70,
	D3DRENDERSTATE_STIPPLEPATTERN07   = 71,
	D3DRENDERSTATE_STIPPLEPATTERN08   = 72,
	D3DRENDERSTATE_STIPPLEPATTERN09   = 73,
	D3DRENDERSTATE_STIPPLEPATTERN10   = 74,
	D3DRENDERSTATE_STIPPLEPATTERN11   = 75,
	D3DRENDERSTATE_STIPPLEPATTERN12   = 76,
	D3DRENDERSTATE_STIPPLEPATTERN13   = 77,
	D3DRENDERSTATE_STIPPLEPATTERN14   = 78,
	D3DRENDERSTATE_STIPPLEPATTERN15   = 79,
	D3DRENDERSTATE_STIPPLEPATTERN16   = 80,
	D3DRENDERSTATE_STIPPLEPATTERN17   = 81,
	D3DRENDERSTATE_STIPPLEPATTERN18   = 82,
	D3DRENDERSTATE_STIPPLEPATTERN19   = 83,
	D3DRENDERSTATE_STIPPLEPATTERN20   = 84,
	D3DRENDERSTATE_STIPPLEPATTERN21   = 85,
	D3DRENDERSTATE_STIPPLEPATTERN22   = 86,
	D3DRENDERSTATE_STIPPLEPATTERN23   = 87,
	D3DRENDERSTATE_STIPPLEPATTERN24   = 88,
	D3DRENDERSTATE_STIPPLEPATTERN25   = 89,
	D3DRENDERSTATE_STIPPLEPATTERN26   = 90,
	D3DRENDERSTATE_STIPPLEPATTERN27   = 91,
	D3DRENDERSTATE_STIPPLEPATTERN28   = 92,
	D3DRENDERSTATE_STIPPLEPATTERN29   = 93,
	D3DRENDERSTATE_STIPPLEPATTERN30   = 94,
	D3DRENDERSTATE_STIPPLEPATTERN31   = 95,
//
// retired renderstate names - the values are still used under new naming conventions
//
	D3DRENDERSTATE_FOGTABLESTART      = 36,   /* Fog table start    */
	D3DRENDERSTATE_FOGTABLEEND        = 37,   /* Fog table end      */
	D3DRENDERSTATE_FOGTABLEDENSITY    = 38,   /* Fog table density  */
} D3DRENDERSTATETYPE;

typedef HRESULT __stdcall (*SET_RENDER_STATE)(struct IDirect3DDevice2**, D3DRENDERSTATETYPE, DWORD);
typedef HRESULT __stdcall (*DRAW_PRIMITIVE)(struct IDirect3DDevice2**, D3DPRIMITIVETYPE, D3DVERTEXTYPE, LPVOID, DWORD, DWORD);

typedef struct IDirect3DDevice2 {
	LPVOID QueryInterface;
	LPVOID AddRef;
	LPVOID Release;
	LPVOID GetCaps;
	LPVOID SwapTextureHandles;
	LPVOID GetStats;
	LPVOID AddViewport;
	LPVOID DeleteViewport;
	LPVOID NextViewport;
	LPVOID EnumTextureFormats;
	LPVOID BeginScene;
	LPVOID EndScene;
	LPVOID GetDirect3D;
	LPVOID SetCurrentViewport;
	LPVOID GetCurrentViewport;
	LPVOID SetRenderTarget;
	LPVOID GetRenderTarget;
	LPVOID Begin;
	LPVOID BeginIndexed;
	LPVOID Vertex;
	LPVOID Index;
	LPVOID End;
	LPVOID GetRenderState;
	SET_RENDER_STATE SetRenderState;
	LPVOID GetLightState;
	LPVOID SetLightState;
	LPVOID SetTransform;
	LPVOID GetTransform;
	LPVOID MultiplyTransform;
	DRAW_PRIMITIVE DrawPrimitive;
	LPVOID DrawIndexedPrimitive;
	LPVOID SetClipStatus;
	LPVOID GetClipStatus;
} *LPDIRECT3DDEVICE2;

#endif // __DXTYPES_H__

/** @endcond */