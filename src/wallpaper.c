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
 * @brief Wallpaper renderer
 *
 * This file implements wallpaper renderer for inventory and title menu
 */

/**
 * @defgroup WALLPAPER Wallpaper
 * @brief Wallpaper renderer
 *
 * This module contains wallpaper renderer for inventory and title menu
 * @{
 */

#include <stdlib.h>
#include <math.h>
#include "intMath.h"
#include "wallpaper.h"

/// Short wave horizontal pattern step
#define SHORT_WAVE_X_STEP	(0x3000)
/// Short wave vertical pattern step
#define SHORT_WAVE_Y_STEP	(0x33E7)
/// Short wave horizontal pattern offset
#define SHORT_WAVE_X_OFFSET	(SHORT_WAVE_X_STEP * 2)
/// Short wave vertical pattern offset
#define SHORT_WAVE_Y_OFFSET	(SHORT_WAVE_Y_STEP * 1)
/// Long wave horizontal pattern step
#define LONG_WAVE_X_STEP	(0x1822)
/// Long wave vertical pattern step
#define LONG_WAVE_Y_STEP	(0x1422)
/// Long wave horizontal pattern offset
#define LONG_WAVE_X_OFFSET	(LONG_WAVE_X_STEP * 2)
/// Long wave vertical pattern offset
#define LONG_WAVE_Y_OFFSET	(LONG_WAVE_Y_STEP * 1)

/// Pixel accuracy factor (for more exact integer computations)
#define PIXEL_ACCURACY	(4)
/// Animated chart detail level (Increases the smoothness of the curve)
#define CHART_DETAIL	(3)

// The farther the point from the center of the screen, the darker it is
static D3DCOLOR centerLighting(int x, int y, int width, int height) { // range is calculated for ( x>=0 && x<=width && y>=0 && y<=height )
	int shade;
	double xDist = (double)(x - (width  / 2)) / (double)width;	// xDist range will be: -0.5..0.5
	double yDist = (double)(y - (height / 2)) / (double)height;	// yDist range will be: -0.5..0.5

	shade = (int)(sqrt(xDist*xDist + yDist*yDist) * 300.0);		// shade range will be: 000..212 (0x00..0xD4)
	return grayToRGBA(shade, 1);
}

// fill far plane of the view by color
static void fillScreen(TR2CONTEXT *ctx, D3DCOLOR color) {
	VERTEX2D vtx[4];

	vtx[0].x = 0;
	vtx[0].y = 0;
	vtx[0].color = color;

	vtx[1].x = *ctx->pScreenWidth;
	vtx[1].y = 0;
	vtx[1].color = color;

	vtx[2].x = 0;
	vtx[2].y = *ctx->pScreenHeight;
	vtx[2].color = color;

	vtx[3].x = *ctx->pScreenWidth;
	vtx[3].y = *ctx->pScreenHeight;
	vtx[3].color = color;

	renderColoredQuad(ctx, &vtx[0], &vtx[1], &vtx[2], &vtx[3], *ctx->pFarZ);
}

void drawStaticPattern(TR2CONTEXT *ctx, TEXTURE *txr, int rowCount) {
	int colCount = mulDiv(rowCount, *ctx->pScreenWidth, *ctx->pScreenHeight);
	int countY = rowCount+1;
	int countX = colCount+1;
	VERTEX2D *vertices = malloc(sizeof(VERTEX2D)*countX*countY);

	for( int i=0; i<countX; ++i ) {
		for( int j=0; j<countY; ++j ) {
			VERTEX2D *vtx = &vertices[i*countY+j];
			vtx->x = (float)mulDiv(*ctx->pScreenWidth,  i, colCount);
			vtx->y = (float)mulDiv(*ctx->pScreenHeight, j, rowCount);
			vtx->color = centerLighting(vtx->x, vtx->y, *ctx->pScreenWidth, *ctx->pScreenHeight);
		}
	}

	for( int i=0; i<colCount; ++i ) {
		for( int j=0; j<rowCount; ++j ) {
			VERTEX2D *vtx0 = &vertices[(i+0)*countY+(j+0)];
			VERTEX2D *vtx1 = &vertices[(i+1)*countY+(j+0)];
			VERTEX2D *vtx2 = &vertices[(i+0)*countY+(j+1)];
			VERTEX2D *vtx3 = &vertices[(i+1)*countY+(j+1)];
			renderTexturedFarQuad(ctx, vtx0, vtx1, vtx2, vtx3, txr);
		}
	}
	free(vertices);
}

void drawAnimatedPattern(TR2CONTEXT *ctx, TEXTURE *txr, int halfRowCount, unsigned char amplitude,
						 short deformWavePhase, short shortWavePhase, short longWavePhase)
{
	int halfColCount = mulDiv(halfRowCount, *ctx->pScreenWidth*3, *ctx->pScreenHeight*4)+1;
	int countY = halfRowCount*2+1;
	int countX = halfColCount*2+1;
	int tileSize = mulDiv(*ctx->pScreenHeight, 2*PIXEL_ACCURACY, 3*halfRowCount);
	int tileRadius = mulDiv(tileSize, amplitude, 100);
	int baseY = *ctx->pScreenHeight*PIXEL_ACCURACY/2 - halfRowCount*tileSize;
	int baseX = *ctx->pScreenWidth*PIXEL_ACCURACY/2  - halfColCount*tileSize;
	VERTEX2D *vertices = malloc(sizeof(VERTEX2D)*countX*countY);

	deformWavePhase += SHORT_WAVE_X_OFFSET;
	shortWavePhase  += SHORT_WAVE_X_OFFSET;
	longWavePhase   += LONG_WAVE_X_OFFSET;

	for( int i=0; i<countX; ++i ) {
		short deformWaveRowPhase = deformWavePhase + SHORT_WAVE_Y_OFFSET;
		short shortWaveRowPhase  = shortWavePhase  + SHORT_WAVE_Y_OFFSET;
		short longWaveRowPhase   = longWavePhase   + LONG_WAVE_Y_OFFSET;

		for( int j=0; j<countY; ++j ) {
			VERTEX2D *vtx = &vertices[i*countY+j];
			int shortWave = intSin(shortWaveRowPhase)*32/0x4000;
			int longWave = intSin(longWaveRowPhase)*32/0x4000;

			vtx->color = grayToRGBA(128+shortWave+longWave, 0);
			vtx->y = ((float)(baseY + tileSize*j + intSin(deformWaveRowPhase)*tileRadius/0x4000)) / PIXEL_ACCURACY;
			vtx->x = ((float)(baseX + tileSize*i + intCos(deformWaveRowPhase)*tileRadius/0x4000)) / PIXEL_ACCURACY;

			deformWaveRowPhase += SHORT_WAVE_Y_STEP;
			shortWaveRowPhase  += SHORT_WAVE_Y_STEP;
			longWaveRowPhase   += LONG_WAVE_Y_STEP;
		}
		deformWavePhase += SHORT_WAVE_X_STEP;
		shortWavePhase  += SHORT_WAVE_X_STEP;
		longWavePhase   += LONG_WAVE_X_STEP;
	}

	for( int i=0; i<halfColCount*2; ++i ) {
		for( int j=0; j<halfRowCount*2; ++j ) {
			VERTEX2D *vtx0 = &vertices[(i+0)*countY+(j+0)];
			VERTEX2D *vtx1 = &vertices[(i+1)*countY+(j+0)];
			VERTEX2D *vtx2 = &vertices[(i+0)*countY+(j+1)];
			VERTEX2D *vtx3 = &vertices[(i+1)*countY+(j+1)];
			renderTexturedFarQuad(ctx, vtx0, vtx1, vtx2, vtx3, txr);
		}
	}
	free(vertices);
}

void drawAnimatedPureRed(TR2CONTEXT *ctx, int halfRowCount,
						 short shortWavePhase, short longWavePhase)
{
	int halfColCount = mulDiv(halfRowCount, *ctx->pScreenWidth*3, *ctx->pScreenHeight*4)+1;

	halfRowCount *= CHART_DETAIL;
	halfColCount *= CHART_DETAIL;

	int countY = halfRowCount*2+1;
	int countX = halfColCount*2+1;
	int tileSize = mulDiv(*ctx->pScreenHeight, 2*PIXEL_ACCURACY, 3*halfRowCount);
	int baseY = *ctx->pScreenHeight*PIXEL_ACCURACY/2 - halfRowCount*tileSize;
	int baseX = *ctx->pScreenWidth*PIXEL_ACCURACY/2  - halfColCount*tileSize;
	VERTEX2D *vertices = malloc(sizeof(VERTEX2D)*countX*countY);

	shortWavePhase += SHORT_WAVE_X_OFFSET;
	longWavePhase  += LONG_WAVE_X_OFFSET;

	for( int i=0; i<countX; ++i ) {
		short shortWaveRowPhase = shortWavePhase + SHORT_WAVE_Y_OFFSET;
		short longWaveRowPhase  = longWavePhase  + LONG_WAVE_Y_OFFSET;

		for( int j=0; j<countY; ++j ) {
			VERTEX2D *vtx = &vertices[i*countY+j];
			int light = 128;
			light += intSin(shortWaveRowPhase)*32/0x4000;
			light += intSin(longWaveRowPhase)*32/0x4000;

			vtx->color = RGBA_MAKE(light, 0, 0, 0xFFu);
			vtx->y = ((float)(baseY + tileSize*j)) / PIXEL_ACCURACY;
			vtx->x = ((float)(baseX + tileSize*i)) / PIXEL_ACCURACY;

			shortWaveRowPhase += SHORT_WAVE_Y_STEP / CHART_DETAIL;
			longWaveRowPhase  += LONG_WAVE_Y_STEP  / CHART_DETAIL;
		}
		shortWavePhase += SHORT_WAVE_X_STEP / CHART_DETAIL;
		longWavePhase  += LONG_WAVE_X_STEP  / CHART_DETAIL;
	}

	for( int i=0; i<halfColCount*2; ++i ) {
		for( int j=0; j<halfRowCount*2; ++j ) {
			VERTEX2D *vtx0 = &vertices[(i+0)*countY+(j+0)];
			VERTEX2D *vtx1 = &vertices[(i+1)*countY+(j+0)];
			VERTEX2D *vtx2 = &vertices[(i+0)*countY+(j+1)];
			VERTEX2D *vtx3 = &vertices[(i+1)*countY+(j+1)];
			renderColoredQuad(ctx, vtx0, vtx1, vtx2, vtx3, *ctx->pFarZ);
		}
	}
	free(vertices);
}

void drawAnimatedChart(TR2CONTEXT *ctx, int halfRowCount,
					   short shortWavePhase, short longWavePhase)
{
	int halfColCount = mulDiv(halfRowCount, *ctx->pScreenWidth*3, *ctx->pScreenHeight*4)+1;
	int tileSize = mulDiv(*ctx->pScreenHeight, 2*PIXEL_ACCURACY, 3*halfRowCount);
	int baseX = *ctx->pScreenWidth*PIXEL_ACCURACY/2 - halfColCount*tileSize;

	halfColCount *= CHART_DETAIL;

	int countX = halfColCount*2+1;
	VERTEX2D *vertices = malloc(sizeof(VERTEX2D)*countX*6);

	fillScreen(ctx, 0xFF000000); // set black screen background

	shortWavePhase += SHORT_WAVE_Y_OFFSET + SHORT_WAVE_Y_STEP;
	longWavePhase  += LONG_WAVE_Y_OFFSET  + LONG_WAVE_Y_STEP;

	for( int j=0; j<3; ++j ) {
		short shortWaveRowPhase = shortWavePhase + SHORT_WAVE_X_OFFSET;
		short longWaveRowPhase  = longWavePhase  + LONG_WAVE_X_OFFSET;

		for( int i=0; i<countX; ++i ) {
			VERTEX2D *vtx0 = &vertices[j*countX*2 + i*2+0];
			VERTEX2D *vtx1 = &vertices[j*countX*2 + i*2+1];
			int light = 128;
			light += intSin(shortWaveRowPhase)*32/0x4000;
			light += intSin(longWaveRowPhase)*32/0x4000;

			vtx0->x = ((float)(baseX + tileSize*i/3)) / PIXEL_ACCURACY;
			vtx1->x = ((float)(baseX + tileSize*i/3)) / PIXEL_ACCURACY;

			vtx1->y = (float)(*ctx->pScreenHeight*(j + 1))/3;
			vtx0->y = vtx1->y - (float)(*ctx->pScreenHeight*(light-64)/128)/3;

			vtx0->color = RGBA_MAKE(light, 0, 0, 0xFFu);
			vtx1->color = RGBA_MAKE(light, 0, 0, 0xFFu);

			shortWaveRowPhase += SHORT_WAVE_X_STEP / CHART_DETAIL;
			longWaveRowPhase  += LONG_WAVE_X_STEP  / CHART_DETAIL;
		}
		shortWavePhase += SHORT_WAVE_Y_STEP * (halfRowCount-1);
		longWavePhase  += LONG_WAVE_Y_STEP  * (halfRowCount-1);
	}

	for( int j=0; j<3; ++j ) {
		for( int i=0; i<halfColCount*2; ++i ) {
			VERTEX2D *vtx0 = &vertices[j*countX*2 + (i+0)*2+0];
			VERTEX2D *vtx1 = &vertices[j*countX*2 + (i+1)*2+0];
			VERTEX2D *vtx2 = &vertices[j*countX*2 + (i+0)*2+1];
			VERTEX2D *vtx3 = &vertices[j*countX*2 + (i+1)*2+1];
			renderColoredQuad(ctx, vtx0, vtx1, vtx2, vtx3, *ctx->pFarZ - 32);
		}
	}
	free(vertices);
}

/** @} */
