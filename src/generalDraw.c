/*
 * Copyright (c) 2017 Michael Chaban. All rights reserved.
 *
 * This file is part of TR2Draw.
 *
 * TR2Draw is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * TR2Draw is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with TR2Draw.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * @brief General graphic routines
 *
 * This file implements very general functions for rendering 3D primitives.
 */

/**
 * @defgroup GENERAL_DRAW General draw
 * @brief General graphic routines
 *
 * This module contains very general functions for rendering 3D primitives.
 * @{

 */
#include <stdlib.h>
#include "generalDraw.h"

static void setTextureHandle(TR2CONTEXT *ctx, DWORD handle) {
	if( handle != *ctx->pCurrentTextureHandle ) {
		*ctx->pCurrentTextureHandle = handle;
		(**ctx->pDxDevice)->SetRenderState(*ctx->pDxDevice, D3DRENDERSTATE_TEXTUREHANDLE, handle);
	}
}

static void setAlphaState(TR2CONTEXT *ctx, BYTE state) {
	if ( state != *ctx->pCurrentAlphaState ) {
		*ctx->pCurrentAlphaState = state;
		(**ctx->pDxDevice)->SetRenderState(*ctx->pDxDevice, *ctx->pAlphaBlendAvailable ? D3DRENDERSTATE_ALPHABLENDENABLE : D3DRENDERSTATE_COLORKEYENABLE, state);
	}
}

D3DCOLOR grayToRGBA(int gray, int inverted) {
	if( gray < 0x00 ) gray = 0x00;
	if( gray > 0xFF ) gray = 0xFF;

	unsigned char ch = gray;
	if( inverted ) ch = 0xFF-ch;
	return RGBA_MAKE(ch, ch, ch, 0xFFu);
}

void renderColoredQuad(TR2CONTEXT *ctx, VERTEX2D *vtx0, VERTEX2D *vtx1, VERTEX2D *vtx2, VERTEX2D *vtx3, float z) {
	D3DTLVERTEX vtx[4];
	memset(vtx, 0, sizeof(vtx));

	float rhw = *ctx->pRhwFactor / z;
	float zNormal = *ctx->pFarZ_normal - *ctx->pDepthZ_normal * rhw;

	vtx[0].sx = vtx0->x;
	vtx[0].sy = vtx0->y;
	vtx[0].sz = zNormal;
	vtx[0].rhw = rhw;
	vtx[0].color = vtx0->color;

	vtx[1].sx = vtx1->x;
	vtx[1].sy = vtx1->y;
	vtx[1].sz = zNormal;
	vtx[1].rhw = rhw;
	vtx[1].color = vtx1->color;

	vtx[2].sx = vtx2->x;
	vtx[2].sy = vtx2->y;
	vtx[2].sz = zNormal;
	vtx[2].rhw = rhw;
	vtx[2].color = vtx2->color;

	vtx[3].sx = vtx3->x;
	vtx[3].sy = vtx3->y;
	vtx[3].sz = zNormal;
	vtx[3].rhw = rhw;
	vtx[3].color = vtx3->color;

	setTextureHandle(ctx, 0);
	setAlphaState(ctx, FALSE);
	(**ctx->pDxDevice)->DrawPrimitive(*ctx->pDxDevice, D3DPT_TRIANGLESTRIP, D3DVT_TLVERTEX, &vtx, 4, D3DDP_DONOTUPDATEEXTENTS|D3DDP_DONOTCLIP);
}

void renderTexturedFarQuad(TR2CONTEXT *ctx, VERTEX2D *vtx0, VERTEX2D *vtx1, VERTEX2D *vtx2, VERTEX2D *vtx3, TEXTURE *txr) {
	D3DTLVERTEX vtx[4];
	double halfPixel = ((double)*ctx->pTextureMargin) / 65536.0;

	float tu_left	= ((double)(txr->x)					/ 256.0) + halfPixel;
	float tu_right	= ((double)(txr->x + txr->width)	/ 256.0) - halfPixel;
	float tv_top	= ((double)(txr->y)					/ 256.0) + halfPixel;
	float tv_bottom	= ((double)(txr->y + txr->height)	/ 256.0) - halfPixel;

	float rhw = *ctx->pRhwFactor / *ctx->pFarZ;

	vtx[0].sx = vtx0->x;
	vtx[0].sy = vtx0->y;
	vtx[0].sz = 0.995;
	vtx[0].rhw = rhw;
	vtx[0].color = vtx0->color;
	vtx[0].specular = 0;
	vtx[0].tu = tu_left;
	vtx[0].tv = tv_top;

	vtx[1].sx = vtx1->x;
	vtx[1].sy = vtx1->y;
	vtx[1].sz = 0.995;
	vtx[1].rhw = rhw;
	vtx[1].color = vtx1->color;
	vtx[1].specular = 0;
	vtx[1].tu = tu_right;
	vtx[1].tv = tv_top;

	vtx[2].sx = vtx2->x;
	vtx[2].sy = vtx2->y;
	vtx[2].sz = 0.995;
	vtx[2].rhw = rhw;
	vtx[2].color = vtx2->color;
	vtx[2].specular = 0;
	vtx[2].tu = tu_left;
	vtx[2].tv = tv_bottom;

	vtx[3].sx = vtx3->x;
	vtx[3].sy = vtx3->y;
	vtx[3].sz = 0.995;
	vtx[3].rhw = rhw;
	vtx[3].color = vtx3->color;
	vtx[3].specular = 0;
	vtx[3].tu = tu_right;
	vtx[3].tv = tv_bottom;

	setTextureHandle(ctx, txr->handle);
	setAlphaState(ctx, FALSE);
	(**ctx->pDxDevice)->DrawPrimitive(*ctx->pDxDevice, D3DPT_TRIANGLESTRIP, D3DVT_TLVERTEX, &vtx, 4, D3DDP_DONOTUPDATEEXTENTS|D3DDP_DONOTCLIP);
}

/** @} */
