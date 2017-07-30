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
 * This file declares TR2Draw.DLL exported functions and interfaces
 */

/**
 * @addtogroup TR2DRAW
 *
 * @{
 */

#ifndef TR2DRAW_H_INCLUDED
#define TR2DRAW_H_INCLUDED

#include <windows.h>
#include "generalDraw.h"

/** @cond Doxygen_Suppress */
#ifdef BUILDING_TR2DRAW_DLL
#define TR2DRAW_DLL __declspec(dllexport)
#else
#define TR2DRAW_DLL __declspec(dllimport)
#endif
/** @endcond */

/// Wallpaper types
typedef enum {
	WPT_IMAGE = 0,		///< Wallpaper is bitmap image. Used for title menu, credits and TR1/TR3 styled inventory
	WPT_STATIC = 1,		///< Wallpaper is static pattern. Used for TR2 PC styled inventory
	WPT_ANIMATED = 2,	///< Wallpaper is animated pattern. Used for TR2 PlayStation styled inventory
} WPTYPE;

/**
 * Draws wallpaper to the game screen
 * @param[in] ctx Pointer to the Tomb Raider 2 Context structure
 * @param[in] txr Pointer to the Texture structure. Ignored if
 * wpType == WPT_IMAGE
 * @param[in] wpType Wallpaper type to draw. Available values:
 * WPT_IMAGE, WPT_STATIC, WPT_ANIMATED
 * @param[in] frameSpeed Framerate factor. This option will be useful
 * when the game will support 60 frames per second. In other cases,
 * set it to 1. Used only if wpType == WPT_ANIMATED
 */
TR2DRAW_DLL void DrawWallpaper(TR2CONTEXT *ctx, TEXTURE *txr, WPTYPE wpType, int frameSpeed);

#endif // TR2DRAW_H_INCLUDED

/** @} */
