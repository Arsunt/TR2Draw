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
 * @brief Integer maths instead of floating point
 *
 * This file declares some integer functions that replace floating
 * point operations
 */

/**
 * @addtogroup INTEGER_MATHS
 *
 * @{
 */

#ifndef INTMATH_H_INCLUDED
#define INTMATH_H_INCLUDED

/**
 * Multiplies two 32-bit values and then divides the 64-bit result by a third
 * 32-bit value. The final result is rounded to the nearest integer.
 * @param[in] number The multiplicand
 * @param[in] numerator The multiplier
 * @param[in] denominator The number by which the result of the multiplication operation is to be divided
 * @return The result of the multiplication and division, rounded to the nearest integer
 * @note The function always rounds the result as unsigned, it was done on purpose
 */
int mulDiv(int number, int numerator, int denominator);

/**
 * Calculates sines of the angle integer representation
 * @param[in] angle Angle integer representation. It may be got from degrees with formula: (signed short)((float)D / 90.0 * (float)0x4000)
 * @return Integer representation of sines. It may be converted to float with formula: ((float)X / (float)0x4000)
 */
short intSin(unsigned short angle);

/**
 * Calculates cosines of the angle integer representation
 * @param[in] angle Angle integer representation. It may be got from degrees with formula: (signed short)((float)D / 90.0 * (float)0x4000)
 * @return Integer representation of cosines. It may be converted to float with formula: ((float)X / (float)0x4000)
 */
short intCos(unsigned short angle);

#endif // INTMATH_H_INCLUDED

/** @} */
