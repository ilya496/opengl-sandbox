#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <fstream>

#include "math/math.h"

struct HeadTable
{
	uint16_t unitsPerEm;
	int16_t xMin, yMin, xMax, yMax;
};

struct MaxpTable
{
	uint16_t numGlyphs;
};

struct HheaTable
{
	int16_t ascent;
	int16_t descent;
	uint16_t numberOfHMetrics;
};

struct HmtxTable
{
	std::vector<uint16_t> advanceWidths;
	std::vector<int16_t> leftSideBearings;
};

struct CmapTable
{
	std::unordered_map<uint32_t, uint16_t> unicodeToGlyphIndex;
};

struct LocaTable
{
	std::vector<uint32_t> offsets;
};

struct TableDirectory
{
	uint32_t offset;
	uint32_t length;
};

enum GlyphFlags
{
	ON_CURVE = 0,
	X_SHORT,
	Y_SHORT,
	REPEAT,
	X_SAME,
	Y_SAME
};

struct CmapFormat4
{
	uint16_t length;
	uint16_t language;
	uint16_t segCount;
	uint16_t searchRange;
	uint16_t entrySelector;
	uint16_t rangeShift;
	std::vector<uint16_t> endCodes;
	std::vector<uint16_t> startCodes;
	std::vector<uint16_t> idDeltas;
	std::vector<uint16_t> idRangeOffsets;
	std::vector<uint16_t> glyphIndexArray;
};

struct Font
{
	HeadTable head;
	MaxpTable maxp;
	HheaTable hhea;
	HmtxTable hmtx;
	CmapTable cmap;
	LocaTable loca;

	const uint8_t* glyfData;
	size_t glyfLength;
};

struct Glyph
{
	int16_t numberOfContours;	
	int16_t xMin, yMin, xMax, yMax;

	std::vector<uint16_t> endPtsOfContours;
	std::vector<uint8_t> flags;
	std::vector<int16_t> xCoords;
	std::vector<int16_t> yCoords;

	uint16_t advanceWidth;
	int16_t leftSideBearing;
};

struct GlyfTable
{
	int16_t numberOfContours;
	int16_t xMin;
	int16_t yMin;
	int16_t xMax;
	int16_t yMax;

	std::vector<Glyph> glyphs;
};

uint16_t ReadUInt16(std::ifstream& file);
int16_t ReadInt16(std::ifstream& file);
uint32_t ReadUInt32(std::ifstream& file);
int32_t ReadInt32(std::ifstream& file);
float ReadFixed(std::ifstream& file);
int64_t ReadInt64(std::ifstream& file);

bool IsFlagBitSet(uint8_t flag, int bitIndex);

std::time_t MacToUnixTime(int64_t macTime);
std::string FormatDate(std::time_t t);

math::vec2 QuadraticBezier(const math::vec2& p0, const math::vec2& p1, const math::vec2& p2, float t);

HeadTable parse_head(std::ifstream& stream, size_t offset);
MaxpTable parse_maxp(std::ifstream& stream, size_t offset);
HheaTable parse_hhea(std::ifstream& stream, size_t offset);

float ReadF2Dot14(std::ifstream& file);