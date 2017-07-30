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
 * This file declares very general functions for rendering 3D primitives.
 */

/**
 * @addtogroup GENERAL_DRAW
 *
 * @{
 */

#ifndef GENERALDRAW_H_INCLUDED
#define GENERALDRAW_H_INCLUDED

#include "dxTypes.h"

/// Tomb Raider 2 Context structure
typedef struct {
	int *pScreenWidth;	///< Pointer to screen width (pixels)
	int *pScreenHeight;	///< Pointer to screen height (pixels)
	LPDIRECT3DDEVICE2 **pDxDevice;	///< Pointer to DX5 Device object
	DWORD *pCurrentTextureHandle;	///< Pointer to current texture handle (0 means no texture)
	BYTE *pCurrentAlphaState;		///< Pointer to current alpha state (FALSE/TRUE)
	BYTE *pAlphaBlendAvailable;		///< Pointer to alphaBlend usage indicator
	int *pTextureMargin;	///< Pointer to texture margin factor
	float *pRhwFactor;		///< Pointer to rhw factor
	float *pFarZ;			///< Pointer to far Z coordinate
	float *pFarZ_normal;	///< Pointer to normalized far Z coordinate
	float *pDepthZ_normal;	///< Pointer to normalized Z depth
} TR2CONTEXT;

/// 2D vertex (no Z coordinate) structure
typedef struct {
	D3DVALUE x; ///< Vertex X coordinate (pixels)
	D3DVALUE y; ///< Vertex Y coordinate (pixels)
	D3DCOLOR color; ///< Vertex color (RGBA)
} VERTEX2D;

/// Texture data structure
typedef struct {
	DWORD handle; ///< Handle of texture tile
	int x; ///< Texture X coordinate (pixels) within texture tile
	int y; ///< Texture Y coordinate (pixels) within texture tile
	int width;	///< Texture width (pixels)
	int height;	///< Texture height (pixels)
} TEXTURE;

/**
 * Converts gray value to full opaque RGBA gray color
 * @param[in] gray Gray value (0..255)
 * @param[in] inverted The flag indicates if gray need to be inverted
 * @return RGBA gray color
 */
D3DCOLOR grayToRGBA(int gray, int inverted);

/**
 * Draws flat colored untextured quad polygon (two triangles)
 * @param[in] ctx Pointer to the Tomb Raider 2 Context structure
 * @param[in] vtx0,vtx1,vtx2,vtx3 Pointers to the Vertex structures
 * @param[in] z Z coordinate for the polygon vertices
 */
void renderColoredQuad(TR2CONTEXT *ctx, VERTEX2D *vtx0, VERTEX2D *vtx1, VERTEX2D *vtx2, VERTEX2D *vtx3, float z);

/**
 * Draws flat textured quad polygon (two triangles) at far Z coordinate
 * @param[in] ctx Pointer to the Tomb Raider 2 Context structure
 * @param[in] vtx0,vtx1,vtx2,vtx3 Pointers to the Vertex structures
 * @param[in] txr Pointer to the Texture structure
 */
void renderTexturedFarQuad(TR2CONTEXT *ctx, VERTEX2D *vtx0, VERTEX2D *vtx1, VERTEX2D *vtx2, VERTEX2D *vtx3, TEXTURE *txr);

#endif // GENERALDRAW_H_INCLUDED

/** @} */
