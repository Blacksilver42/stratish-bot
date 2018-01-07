// what? this is a perfectly valid C header file.

#ifndef __SBDRAW_PRESETS_H__
#define __SBDRAW_PRESETS_H__

#define IMAGE_PADDING 15

#define GLYPH_SIZE 100 //must be a multiple of 20

#define SPACER 10
#define DECO_SPACER 5

#define THIN_DECO_SIZE 40
#define BOLD_DECO_SIZE 20

#define MINI_GLYPH_SIZE_MULT 0.5
#define MINI_GLYPH_OFFSET_MULT 0.15

#define MINI_GLYPH_OFFSET (int)(GLYPH_SIZE*MINI_GLYPH_OFFSET_MULT)
#define MINI_GLYPH_SIZE (int)(GLYPH_SIZE*MINI_GLYPH_SIZE_MULT)

#endif
