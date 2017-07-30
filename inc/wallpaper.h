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
 * This file declares wallpaper renderer for inventory and title menu
 */

/**
 * @addtogroup WALLPAPER
 *
 * @{
 */

#ifndef WALLPAPER_H_INCLUDED
#define WALLPAPER_H_INCLUDED

#include "generalDraw.h"

/**
 * Draws static pattern wallpaper to the game screen (TR2 PC inventory style)
 * @param[in] ctx Pointer to the Tomb Raider 2 Context structure
 * @param[in] txr Pointer to the Texture structure
 * @param[in] rowCount Number of vertical rows of the wallpaper pattern
 */
void drawStaticPattern(TR2CONTEXT *ctx, TEXTURE *txr, int rowCount);

/**
 * Draws animated pattern wallpaper (TR2 PlayStation inventory style)
 * @param[in] ctx Pointer to the Tomb Raider 2 Context structure
 * @param[in] txr Pointer to the Texture structure
 * @param[in] halfRowCount Half number of vertical rows of the wallpaper pattern
 * @param[in] amplitude Percent value of the deformation amplitude (vertex rotation radius)
 * @param[in] deformWavePhase Deformation wave phase in Integer representation
 * @param[in] shortWavePhase Lighting short wave phase in Integer representation
 * @param[in] longWavePhase Lighting long wave phase in Integer representation
 */
void drawAnimatedPattern(TR2CONTEXT *ctx, TEXTURE *txr, int halfRowCount, unsigned char amplitude,
						 short deformWavePhase, short shortWavePhase, short longWavePhase);

/**
 * Draws animated undeformed pure red sheet wallpaper (requires DEBUG_WP_PURERED define)
 * @param[in] ctx Pointer to the Tomb Raider 2 Context structure
 * @param[in] halfRowCount Half number of vertical rows of the wallpaper pattern
 * @param[in] shortWavePhase Lighting short wave phase in Integer representation
 * @param[in] longWavePhase Lighting long wave phase in Integer representation
 */
void drawAnimatedPureRed(TR2CONTEXT *ctx, int halfRowCount,
						 short shortWavePhase, short longWavePhase);

/**
 * Draws animated wave interference chart wallpaper (requires DEBUG_WP_CHART define)
 * @param[in] ctx Pointer to the Tomb Raider 2 Context structure
 * @param[in] halfRowCount Half number of vertical rows of the wallpaper pattern
 * @param[in] shortWavePhase Lighting short wave phase in Integer representation
 * @param[in] longWavePhase Lighting long wave phase in Integer representation
 */
void drawAnimatedChart(TR2CONTEXT *ctx, int halfRowCount,
					   short shortWavePhase, short longWavePhase);

#endif // WALLPAPER_H_INCLUDED

/** @} */
