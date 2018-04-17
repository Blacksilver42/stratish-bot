#pragma once
#include <vector>
#include <string>
#include "cmdParser.hpp"

enum GlyphType {
	Square,
	Auxillary,
	Pronoun,
	Article,
	Ditto,
};
enum Placement {
	TopRight,
	TopLeft,
	BottomRight,
	BottomLeft,
	Center,
};

struct GlyphInfo {
	std::string subfolder;
	std::string name;
	GlyphType type;
};
struct AZGlyph : GlyphInfo { //maybe not needed
	bool vowel;
};
struct SquareGlyph : AZGlyph {
	Placement place;
	SquareGlyph* innerGlyph;
};

struct AuxillaryGylphs {
	std::vector<GlyphInfo*> top;
	std::vector<GlyphInfo*> right;
	std::vector<GlyphInfo*> bottom;
	std::vector<GlyphInfo*> left;
};

struct GlyphSet {
	GlyphInfo* base;
	AuxillaryGylphs auxGlyphs;
};
typedef std::vector<GlyphSet> GlyphSets;
int getGlyphSets (Info &info,GlyphSets &glyphSets);
