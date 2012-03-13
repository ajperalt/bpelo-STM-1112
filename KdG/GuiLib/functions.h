/*
 * functions.h
 *
 *  Created on: May 7, 2011
 *      Author: philip
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_


/**
 * \file functions.h
 *
 * \brief Has some functions
 */

/**
 * \brief Convert a 24-bit color to a 16-bit color (5bits red, 6bits green, 5 bits blue).
 *
 * @param rgb24 The 24-bit color. Only the lowest 3 bytes are used (0x00FFFFFF = white).
 */
short convertRGB24to5R6G5B(int rgb24);

/**
 * \brief Calculate the height of the thext.
 *
 * @param text The text of which you want to calculate the height. In monospace it is the same as the character height.
 * @param font The font size.
 * @return The height in pixels
 */
int calculateTextHeight(const char* text, char font);
/**
 * \brief Calculate the width of the thext.
 *
 * @param text The text of which you want to calculate the width.
 * @param font The font size.
 * @return The width in pixels
 */
int calculateTextWidth(const char* text, char font);
/**
 * \brief Calculate the width of a character.
 *
 * @param font The font size.
 * @return The width in pixels
 */
int calculateCharacterWidth(char font);
/**
 * \brief Calculate the height of a character.
 *
 * @param font The font size.
 * @return The height in pixels
 */
int calculateCharacterHeight(char font);

/**
 * \brief Calculate the height of a button.
 *
 * @param font The font size.
 * @return The height in pixels
 */
int calculateButtonHeight(char font);

/**
 * \brief Calculate the width of a button.
 *
 * @param text The text in the button
 * @param font The font size.
 * @return The width in pixels
 */
int calculateButtonWidth(const char* text, char font);

/**
 * \brief Translate row indexes to pixels
 *
 * If you want to use row-indexes you can use these functions to convert them to pixels, so you can use it with the components as they use pixel offsets.
 * Be aware that the row is calculated on the font size. If you use multiple font sizes, you can't use this function to calculate the pixel offset.
 * You should use calculateCharacterHeight instead.
 *
 * @param row The row index you want to translate to pixels
 * @param font The font size used
 * @return The row-index converted to pixels using the specified font size
 */
int convertRowToPixels(char row, char font);
/**
 * \brief Translate column indexes to pixels
 *
 * If you want to use column-indexes you can use these functions to convert them to pixels, so you can use it with the components as they use pixel offsets.
 * Be aware that the column is calculated on the font size. If you use multiple font sizes, you can't use this function to calculate the pixel offset.
 * You should use calculateCharacterWidth instead.
 *
 * @param column The column index you want to translate to pixels
 * @param font The font size used
 * @return The column-index converted to pixels using the specified font size
 */
int convertColumnToPixels(char column, char font);

/**
 * \brief Send the draw text command trough the serial communication.
 *
 * @param x The x-offset in pixels
 * @param y The y-offset in pixels
 * @param str The text you want to draw
 * @param font The font size
 * @param color The color the text has
 */
int serialDrawText(short x, short y, const char* str, char font, int color);

/**
 * \brief Send the draw textbutton command trough the serial communication.
 *
 * @param x The x-offset in pixels
 * @param y The y-offset in pixels
 * @param str The text you want to draw
 * @param font The font size
 * @param color The color the text has
 * @param rgbBtn The color of the background of the button
 * @param state The state of the button (pressed or released)
 */
int serialDrawTextButton(short x, short y, const char* str, char font, int color, int rgbBtn, char state);

/**
 * \brief Send the draw circle command trough the serial communication.
 *
 * @param x The x-offset in pixels of the centre of the circle
 * @param y The y-offset in pixels of the centre of the circle
 * @param radius The radius of the circle
 * @param rgb The color the circle has
 */
int serialDrawCircle(short x, short y, short radius, int rgb);

/**
 * \brief Send the draw elipse command trough the serial communication.
 *
 * @param x The x-offset in pixels of the centre of the ellipse
 * @param y The y-offset in pixels of the centre of the ellipse
 * @param xRadius The horizontal radius of the ellipse
 * @param yRadius The vertical radius of the ellipse
 * @param rgb The color the ellipse has
 */
int serialDrawElipse(short x, short y, short xRadius, short yRadius, int rgb);

/**
 * \brief Send the draw triangle command trough the serial communication.
 *
 * @param x1 The x-offset in pixels of the first point of the triangle
 * @param y1 The y-offset in pixels of the first point of the triangle
 * @param x2 The x-offset in pixels of the second point of the triangle
 * @param y2 The y-offset in pixels of the second point of the triangle
 * @param x3 The x-offset in pixels of the third point of the triangle
 * @param y3 The y-offset in pixels of the third point of the triangle
 * @param rgb The color the triangle has
 *
 * @warning The points should be given in counter-clokwise
 */
int serialDrawTriangle(short x1, short y1, short x2, short y2, short x3, short y3, int rgb);

/**
 * \brief Send the draw line command trough the serial communication.
 *
 * @param x1 The x-offset in pixels of the first point of the line
 * @param y1 The y-offset in pixels of the first point of the line
 * @param x2 The x-offset in pixels of the second point of the line
 * @param y2 The y-offset in pixels of the second point of the line
 * @param rgb The color the line has
 */
int serialDrawLine(short x1, short y1, short x2, short y2, int rgb);

/**
 * \brief Send the draw rectangle command trough the serial communication.
 *
 * @param x The x-offset in pixels
 * @param y The y-offset in pixels
 * @param width The width of the rectangle
 * @param height The height of the rectangle
 * @param rgb The color the rectangle has
 */
int serialDrawRectangle(short x, short y, short width, short height, int rgb);

#endif /* FUNCTIONS_H_ */
