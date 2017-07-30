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
 * @brief TR2Draw interface
 *
 * This file implements TR2Draw.DLL exported functions and interfaces
 */

/**
 * @defgroup TR2DRAW TR2Draw
 * @brief TR2Draw interface
 *
 * This module contains TR2Draw.DLL exported functions and interfaces
 *
 * @{
 */
#include "wallpaper.h"
#include "TR2Draw.h"

TR2DRAW_DLL void DrawWallpaper(TR2CONTEXT *ctx, TEXTURE *txr, WPTYPE wpType, int frameSpeed) {
	static const int shortWaveStep = -0x0267; // minus 3.92 degrees
	static const int longWaveStep  = -0x0200; // minus 2.81 degrees

	static unsigned short deformWavePhase = 0x0000; // 0 degrees
	static unsigned short shortWavePhase = 0x4000; // 90 degrees
	static unsigned short longWavePhase = 0xA000; // 225 degrees

	switch( wpType ) {
		case WPT_IMAGE :
//			drawBitmapImage(ctx);
			break;

		case WPT_STATIC :
			drawStaticPattern(ctx, txr, 6);
			break;

		case WPT_ANIMATED :
#if defined DEBUG_WP_CHART
			drawAnimatedChart(ctx, 3, shortWavePhase, longWavePhase);
#elif defined DEBUG_WP_PURERED
			drawAnimatedPureRed(ctx, 3, shortWavePhase, longWavePhase);
#else
			drawAnimatedPattern(ctx, txr, 3, 10, deformWavePhase, shortWavePhase, longWavePhase);
#endif
			if ( frameSpeed ) {
				deformWavePhase += shortWaveStep / frameSpeed;
				shortWavePhase  += shortWaveStep / frameSpeed;
				longWavePhase   += longWaveStep  / frameSpeed;
			}
			break;

		default :
			break;
	}
}

/**
 * An optional entry point into a dynamic-link library (DLL)
 * @param[in] hinstDLL A handle to the DLL module
 * @param[in] fdwReason The reason code that indicates why the DLL
 * entry-point function is being called
 * @param[in] lpvReserved used if fdwReason is DLL_PROCESS_ATTACH or DLL_PROCESS_DETACH
 * @return TRUE if it succeeds or FALSE if it fails
 * @note See the MSDN for more information
 */
extern TR2DRAW_DLL BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch( fdwReason ) {
		case DLL_PROCESS_ATTACH :
			// attach to process
			// return FALSE to fail DLL load
			break;

		case DLL_PROCESS_DETACH :
			// detach from process
			break;

		case DLL_THREAD_ATTACH :
			// attach to thread
			break;

		case DLL_THREAD_DETACH :
			// detach from thread
			break;
	}
	return TRUE; // successful
}

/** @} */
