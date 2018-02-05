// what? this is a perfectly valid C header file.

#ifndef __SBDRAW_PRESETS_H__
#define __SBDRAW_PRESETS_H__


// outside padding
#define IMAGE_PADDING 15

// base glyph size
#define GLYPH_SIZE 100 //must be a multiple of 20

// decoration sizes
#define THIN_DECO_SIZE 40
#define BOLD_DECO_SIZE 20

// space between glyphs and decos
#define SPACER 10
#define DECO_SPACER 5
#define WORD_SPACER (SPACER*2)

// internal glyph multipliers
#define MINI_GLYPH_SIZE_MULT 0.5
#define MINI_GLYPH_OFFSET_MULT 0.15

// cast to an int or it starts complaining about loss of percision
#define MINI_GLYPH_OFFSET (int)(GLYPH_SIZE*MINI_GLYPH_OFFSET_MULT)
#define MINI_GLYPH_SIZE (int)(GLYPH_SIZE*MINI_GLYPH_SIZE_MULT)

#endif
