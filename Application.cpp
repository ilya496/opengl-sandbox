#include "Application.h"
#include <iostream>
#include "Input.h"
#include "Shader.h"
#include "Buffer.h"
#include "opengl.h"
#include <fstream>
#include <unordered_map>
#include "font.h"

#undef max;

Application::Application()
{
	Init();
}

Application::~Application()
{
	ShutDown();
}

void Application::Init()
{
	m_Window = Window::Create(600, 800, "My Engine");
	if (!m_Window)
	{
		std::cerr << "Failed to create window.\n";
		return;
	}

	m_Context = GLContext::Create(m_Window->GetHandle());	
	if (!m_Context)
	{
		std::cerr << "Failed to initiliaze OpenGL context.\n";
		return;
	}
}

void Application::Run()
{
	std::ifstream file("Roboto-Regular.ttf", std::ios::in | std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "Failed to open font file.\n";
		return;
	}

	uint32_t scalarType = ReadUInt32(file);
	uint16_t numTables = ReadUInt16(file);
	uint16_t searchRange = ReadUInt16(file);
	uint16_t entrySelector = ReadUInt16(file);
	uint16_t rangeShift = ReadUInt16(file);

	std::unordered_map<std::string, TableDirectory> tables;
	for (int i = 0; i < numTables; ++i)
	{
		char tag[5] = { 0 };
		file.read(tag, 4);
		uint32_t checkSum = ReadUInt32(file);
		uint32_t offset = ReadUInt32(file);
		uint32_t length = ReadUInt32(file);

		tables[tag] = { offset, length };
		std::cout << "Table: " << tag << '\n';
	}

	auto maxpIt = tables.find("maxp");
	file.seekg(maxpIt->second.offset, std::ios::beg);
	uint32_t maxpVersion = ReadUInt32(file);
	uint16_t numGlyphs = ReadUInt16(file);
	uint16_t maxPoints = ReadUInt16(file);
	uint16_t maxContours = ReadUInt16(file);
	uint16_t maxComponentPoints = ReadUInt16(file);
	uint16_t maxComponentContours = ReadUInt16(file);
	uint16_t maxZones = ReadUInt16(file);
	uint16_t maxTwilightPoints = ReadUInt16(file);
	uint16_t maxStorage = ReadUInt16(file);
	uint16_t maxFunctionDefs = ReadUInt16(file);
	uint16_t maxInstructionDefs = ReadUInt16(file);
	uint16_t maxStackElements = ReadUInt16(file);
	uint16_t maxSizeOfInstructions = ReadUInt16(file);
	uint16_t maxComponentElements = ReadUInt16(file);
	uint16_t maxComponentDepth = ReadUInt16(file);

	std::cout << "=== 'maxp' Table ===\n";
	std::cout << "Version: 0x" << std::hex << maxpVersion << std::dec << '\n';
	std::cout << "Number of Glyphs:      " << numGlyphs << '\n';
	std::cout << "Max Points:            " << maxPoints << '\n';
	std::cout << "Max Contours:          " << maxContours << '\n';
	std::cout << "Max Component Points:  " << maxComponentPoints << '\n';
	std::cout << "Max Component Contours:" << maxComponentContours << '\n';
	std::cout << "Max Zones:             " << maxZones << '\n';
	std::cout << "Max Twilight Points:   " << maxTwilightPoints << '\n';
	std::cout << "Max Storage:           " << maxStorage << '\n';
	std::cout << "Max Function Defs:     " << maxFunctionDefs << '\n';
	std::cout << "Max Instruction Defs:  " << maxInstructionDefs << '\n';
	std::cout << "Max Stack Elements:    " << maxStackElements << '\n';
	std::cout << "Max Size of Instrs:    " << maxSizeOfInstructions << '\n';
	std::cout << "Max Component Elements:" << maxComponentElements << '\n';
	std::cout << "Max Component Depth:   " << maxComponentDepth << '\n';

	auto headIt = tables.find("head");
	file.seekg(headIt->second.offset, std::ios::beg);
	uint32_t headVersion = ReadUInt32(file);
	uint32_t fontRevision = ReadUInt32(file);
	uint32_t checkSumAdjustment = ReadUInt32(file);
	uint32_t magicNumber = ReadUInt32(file);
	uint16_t headFlags = ReadUInt16(file);
	uint16_t unitsPerEm = ReadUInt16(file);
	int64_t created = ReadInt64(file);
	int64_t modified = ReadInt64(file);
	int16_t headXMin = ReadInt16(file);
	int16_t headYMin = ReadInt16(file);
	int16_t headXMax = ReadInt16(file);
	int16_t headYMax = ReadInt16(file);
	uint16_t macStyle = ReadUInt16(file);
	uint16_t lowestRecPPEM = ReadUInt16(file);
	int16_t fontDirectionHint = ReadInt16(file);
	int16_t indexToLocFormat = ReadInt16(file);
	int16_t glyphDataFormat = ReadInt16(file);

	std::time_t createdTime = MacToUnixTime(created);
	std::time_t modifiedTime = MacToUnixTime(modified);

	float fontRevisionFixed = fontRevision / 65536.0f;

	std::cout << "=== 'head' Table ===\n";
	std::cout << "Version:               0x" << std::hex << headVersion << std::dec << '\n';
	std::cout << "Font Revision:         0x" << std::hex << fontRevision
		<< std::dec << " (" << fontRevisionFixed << ")\n";
	std::cout << "Checksum Adjustment:   0x" << std::hex << checkSumAdjustment << std::dec << '\n';
	std::cout << "Magic Number:          0x" << std::hex << magicNumber << std::dec << '\n';

	std::cout << "Flags:                 0x" << std::hex << headFlags << std::dec << '\n';
	std::cout << "Units per Em:          " << unitsPerEm << '\n';
	std::cout << "Created:               " << FormatDate(createdTime) << '\n';
	std::cout << "Modified:              " << FormatDate(modifiedTime) << '\n';

	std::cout << "xMin:                  " << headXMin << '\n';
	std::cout << "yMin:                  " << headYMin << '\n';
	std::cout << "xMax:                  " << headXMax << '\n';
	std::cout << "yMax:                  " << headYMax << '\n';

	std::cout << "Mac Style:             0x" << std::hex << macStyle << std::dec << '\n';
	std::cout << "Lowest Rec PPEM:       " << lowestRecPPEM << '\n';
	std::cout << "Font Direction Hint:   " << fontDirectionHint << '\n';
	std::cout << "IndexToLocFormat:      " << indexToLocFormat << " (" << (indexToLocFormat == 0 ? "short (offsets divided by 2)" : "long (offsets in full)") << ")\n";
	std::cout << "Glyph Data Format:     " << glyphDataFormat << '\n';

	auto locaIt = tables.find("loca");
	file.seekg(locaIt->second.offset, std::ios::beg);

	std::vector<uint32_t> glyphOffsets(numGlyphs + 1);

	if (indexToLocFormat == 1) {
		for (int i = 0; i <= numGlyphs; ++i) {
			glyphOffsets[i] = ReadUInt32(file);
		}
	}
	else {
		for (int i = 0; i <= numGlyphs; ++i) {
			glyphOffsets[i] = ReadUInt16(file) * 2;
		}
	}

	std::cout << "=== 'loca' Table ===\n";
	std::cout << "Number of offsets: " << glyphOffsets.size() << '\n';

	auto hheaIt = tables.find("hhea");
	file.seekg(hheaIt->second.offset, std::ios::beg);

	float hheaVersion = ReadFixed(file);
	int16_t ascent = ReadInt16(file);
	int16_t descent = ReadInt16(file);
	int16_t lineGap = ReadInt16(file);
	uint16_t advanceWidthMax = ReadUInt16(file);
	int16_t minLeftSideBearing = ReadInt16(file);
	int16_t minRightSideBearing = ReadInt16(file);
	int16_t xMaxExtent = ReadInt16(file);
	int16_t caretSlopeRise = ReadInt16(file);
	int16_t caretSlopeRun = ReadInt16(file);
	int16_t caretOffset = ReadInt16(file);
	int16_t reserved1 = ReadInt16(file);
	int16_t reserved2 = ReadInt16(file);
	int16_t reserved3 = ReadInt16(file);
	int16_t reserved4 = ReadInt16(file);
	int16_t metricDataFormat = ReadInt16(file);
	uint16_t numOfLongHorMetrics = ReadUInt16(file);

	std::cout << "=== 'hhea' Table ===\n";
	std::cout << "Version: " << hheaVersion << '\n';
	std::cout << "Ascent: " << ascent << '\n';
	std::cout << "Descent: " << descent << '\n';
	std::cout << "Advance width max: " << advanceWidthMax << '\n';
	std::cout << "Min left side bearing: " << minLeftSideBearing << '\n';
	std::cout << "Min right side bearing: " << minRightSideBearing << '\n';
	std::cout << "X maximum extent: " << xMaxExtent << '\n';
	std::cout << "Caret slope rise: " << caretSlopeRise << '\n';
	std::cout << "Caret slope run: " << caretSlopeRun << '\n';
	std::cout << "Caret offset: " << caretOffset << '\n';
	std::cout << "Reserved 1: " << reserved1 << '\n';
	std::cout << "Reserved 2: " << reserved2 << '\n';
	std::cout << "Reserved 3: " << reserved3 << '\n';
	std::cout << "Reserved 4: " << reserved4 << '\n';
	std::cout << "Number of LongHorMetrics: " << numOfLongHorMetrics << '\n';

	struct LongHorMetric
	{
		uint16_t advanceWidth;
		int16_t leftSideBearing;
	};

	auto hmtxIt = tables.find("hmtx");
	file.seekg(hmtxIt->second.offset, std::ios::beg);

	std::vector<uint16_t> advanceWidths(numGlyphs);
	std::vector<int16_t> leftSideBearings(numGlyphs);

	for (int i = 0; i < numOfLongHorMetrics; ++i) {
		advanceWidths[i] = ReadUInt16(file);
		leftSideBearings[i] = ReadInt16(file);
	}

	for (int i = numOfLongHorMetrics; i < numGlyphs; ++i) {
		advanceWidths[i] = advanceWidths[numOfLongHorMetrics - 1];
		leftSideBearings[i] = ReadInt16(file);
	}

	struct CmapSubtable {
		uint16_t platformId;
		uint16_t platformSpecificId;
		uint32_t offset;
	};

	auto cmapIt = tables.find("cmap");
	file.seekg(cmapIt->second.offset, std::ios::beg);
	uint16_t cmapVersion = ReadUInt16(file);
	uint16_t numberSubtables = ReadUInt16(file);

	std::cout << "=== 'cmap' Table ===\n";
	std::cout << "Version:               0x" << std::hex << cmapVersion << std::dec << '\n';
	std::cout << "Number of subtables:   " << numberSubtables << '\n';

	std::vector<CmapSubtable> subtables;

	for (int i = 0; i < numberSubtables; ++i)
	{
		CmapSubtable subtable;
		subtable.platformId = ReadUInt16(file);
		subtable.platformSpecificId = ReadUInt16(file);
		subtable.offset = ReadUInt32(file);
		subtables.push_back(subtable);
	}

	std::unordered_map<uint32_t, uint16_t> glyphMap;

	for (size_t i = 0; i < subtables.size(); ++i) {
		const auto& entry = subtables[i];

		file.seekg(cmapIt->second.offset + entry.offset, std::ios::beg);

		uint16_t format = ReadUInt16(file);

		std::cout << "Subtable " << (i + 1) << "\n";
		std::cout << "Platform ID: " << entry.platformId << "\n";
		std::cout << "Platform specific ID: " << entry.platformSpecificId << "\n";
		std::cout << "Offset: " << entry.offset << "\n";
		std::cout << "Format: " << format << "\n\n";

		if (format == 4) {
			uint16_t length = ReadUInt16(file);
			uint16_t language = ReadUInt16(file);
			uint16_t segCountX2 = ReadUInt16(file);
			uint16_t segCount = segCountX2 / 2;
			uint16_t searchRange = ReadUInt16(file);
			uint16_t entrySelector = ReadUInt16(file);
			uint16_t rangeShift = ReadUInt16(file);

			std::vector<uint16_t> endCode(segCount);
			std::vector<uint16_t> startCode(segCount);
			std::vector<uint16_t> idDelta(segCount);
			std::vector<uint16_t> idRangeOffset(segCount);

			for (int i = 0; i < segCount; ++i) endCode[i] = ReadUInt16(file);
			uint16_t reservedPad = ReadUInt16(file);
			for (int i = 0; i < segCount; ++i) startCode[i] = ReadUInt16(file);
			for (int i = 0; i < segCount; ++i) idDelta[i] = ReadUInt16(file);
			std::streamoff idRangeOffsetPos = file.tellg();
			for (int i = 0; i < segCount; ++i) idRangeOffset[i] = ReadUInt16(file);

			std::streamoff glyphIdArrayPos = file.tellg();

			// Loop through all codepoints in each segment
			for (int i = 0; i < segCount; ++i) {
				for (uint32_t codepoint = startCode[i]; codepoint <= endCode[i]; ++codepoint) {
					uint16_t glyphIndex = 0;

					if (idRangeOffset[i] == 0) {
						glyphIndex = (codepoint + idDelta[i]) % 65536;
					}
					else {
						uint16_t ro = idRangeOffset[i];
						// Compute position of glyphId in glyphIdArray[]
						std::streamoff glyphIndexPos = idRangeOffsetPos + 2 * i + ro + 2 * (codepoint - startCode[i]);

						file.seekg(glyphIndexPos, std::ios::beg);
						uint16_t glyphId = ReadUInt16(file);

						if (glyphId != 0) {
							glyphIndex = (glyphId + idDelta[i]) % 65536;
						}
						else {
							glyphIndex = 0; // missing glyph
						}
					}

					if (glyphIndex != 0) {
						glyphMap[codepoint] = glyphIndex;
					}
				}
			}
		}
	}

	auto glyfIt = tables.find("glyf");
	file.seekg(glyfIt->second.offset, std::ios::beg);
	file.seekg(glyphOffsets[glyphMap['a']], std::ios::cur);

	int16_t numberOfContours = ReadInt16(file);
	int16_t xMin = ReadInt16(file);
	int16_t yMin = ReadInt16(file);
	int16_t xMax = ReadInt16(file);
	int16_t yMax = ReadInt16(file);

	if (numberOfContours <= 0)
	{
		constexpr uint16_t ARG_1_AND_2_ARE_WORDS = 0x0001;
		constexpr uint16_t ARGS_ARE_XY_VALUES = 0x0002;
		constexpr uint16_t ROUND_XY_TO_GRID = 0x0004;
		constexpr uint16_t WE_HAVE_A_SCALE = 0x0008;
		constexpr uint16_t MORE_COMPONENTS = 0x0020;
		constexpr uint16_t WE_HAVE_AN_X_AND_Y_SCALE = 0x0040;
		constexpr uint16_t WE_HAVE_A_TWO_BY_TWO = 0x0080;

		std::cout << "Compound glyph: \n";
		bool hasMoreComponents = true;
		while (hasMoreComponents)
		{
			uint16_t flags = ReadUInt16(file);
			uint16_t glyphIndex = ReadUInt16(file);

			std::cout << "Flags: 0x" << std::hex << flags << std::dec << '\n';
			std::cout << "Glyph index: " << glyphIndex << '\n';

			int16_t arg1 = 0, arg2 = 0;
			if (flags & ARG_1_AND_2_ARE_WORDS)
			{
				arg1 = ReadInt16(file);
				arg2 = ReadInt16(file);
			}
			else 
			{
				arg1 = file.get();
				arg2 = file.get();
			}

			std::cout << "Arg1 = " << arg1 << ", Arg2 = " << arg2 << '\n';
			
			float a = 1.0f, b = 0.0f, c = 0.0f, d = 1.0f;
			if (flags & WE_HAVE_A_SCALE) {
				float scale = ReadF2Dot14(file);
				a = d = scale;
			}
			else if (flags & WE_HAVE_AN_X_AND_Y_SCALE) {
				a = ReadF2Dot14(file);
				d = ReadF2Dot14(file);
			}
			else if (flags & WE_HAVE_A_TWO_BY_TWO) {
				a = ReadF2Dot14(file);
				b = ReadF2Dot14(file);
				c = ReadF2Dot14(file);
				d = ReadF2Dot14(file);
			}
			 
			float m0 = std::max(std::abs(a), std::abs(b));

			hasMoreComponents = flags & MORE_COMPONENTS;
		}
		return;
	}

	std::cout << "Number of contours: " << numberOfContours << '\n';
	uint16_t* endPtsOfContours = new uint16_t[numberOfContours];
	for (int i = 0; i < numberOfContours; ++i)
	{
		endPtsOfContours[i] = ReadUInt16(file);
	}

	uint16_t instructionLength = ReadUInt16(file);
	for (int i = 0; i < instructionLength; ++i)
	{
		file.get(); // skip instructions;
	}

	int numPoints = endPtsOfContours[numberOfContours - 1] + 1;
	std::vector<uint8_t> flags;
	flags.reserve(numPoints);

	int pointsParsed = 0;
	while (pointsParsed < numPoints)
	{
		uint8_t flag = file.get();
		flags.push_back(flag);
		++pointsParsed;

		if (flag & (1 << GlyphFlags::REPEAT))
		{
			uint8_t repeatCount = file.get();
			for (int i = 0; i < repeatCount; ++i)
			{
				flags.push_back(flag);
			}
			pointsParsed += repeatCount;
		}
	}

	std::vector<int16_t> xCoords(numPoints);
	int16_t x = 0;

	for (int i = 0; i < numPoints; ++i)
	{
		uint8_t flag = flags[i];

		if (flag & (1 << GlyphFlags::X_SHORT))
		{
			uint8_t dx = file.get();
			if (flag & (1 << GlyphFlags::X_SAME))
				x += dx;        // +dx
			else
				x -= dx;        // -dx
		}
		else
		{
			if (flag & (1 << GlyphFlags::X_SAME))
			{
				// No change in x (i.e., dx = 0)
			}
			else
			{
				int16_t dx = ReadInt16(file);
				x += dx;
			}
		}
		xCoords[i] = x;
	}

	std::vector<int16_t> yCoords(numPoints);
	int16_t y = 0;

	for (int i = 0; i < numPoints; ++i)
	{
		uint8_t flag = flags[i];

		if (flag & (1 << GlyphFlags::Y_SHORT))
		{
			uint8_t dy = file.get();
			if (flag & (1 << GlyphFlags::Y_SAME))
				y += dy;
			else
				y -= dy;
		}
		else
		{
			if (flag & (1 << GlyphFlags::Y_SAME))
			{
				// No change in y
			}
			else
			{
				int16_t dy = ReadInt16(file);
				y += dy;
			}
		}
		yCoords[i] = y;
	}

	Shader pointShader = LoadShaderFromFile("point.vert", "point.frag");
	Shader lineShader = LoadShaderFromFile("line.vert", "line.frag");

	std::vector<float> vertices;
	vertices.reserve(xCoords.size() * 3);

	for (size_t i = 0; i < xCoords.size(); ++i)
	{
		float x = ((xCoords[i] - xMin) / float(xMax - xMin)) - 0.5f;
		float y = ((yCoords[i] - yMin) / float(yMax - yMin)) - 0.5f;

		float isOnCurve = IsFlagBitSet(flags[i], GlyphFlags::ON_CURVE) ? 1.0f : 0.0f;

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(isOnCurve);
	}

	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	auto vbo = VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float));
	BufferLayout layout = {
		{ ShaderDataType::Float2, "a_Position" },
		{ ShaderDataType::Float, "a_OnCurve" },
	};
	vbo->SetLayout(layout);

	GLuint bezierVAO;
	glGenVertexArrays(1, &bezierVAO);
	glBindVertexArray(bezierVAO);

	//auto bezierVBO = VertexBuffer::Create(bezierVertices.data(), bezierVertices.size() * sizeof(float));
	//BufferLayout bezierLayout = {
		//{ ShaderDataType::Float2, "a_Position" },
	//};
	//bezierVBO->SetLayout(bezierLayout);

	GLuint bezierVBO;
	glGenBuffers(1, &bezierVBO);

	while (!m_Window->ShouldClose())
	{
		m_Window->ProcessMessages();
		Input::Update();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		pointShader.Bind();
		pointShader.Set1f("u_PointSize", 8.0);
		glBindVertexArray(vao);
		glDrawArrays(GL_POINTS, 0, numPoints);

		//lineShader.Bind();
		//glBindVertexArray(bezierVAO);
		//for (auto& contour : contourVertices)
		//{
		//	glBindBuffer(GL_ARRAY_BUFFER, bezierVBO);
		//	glBufferData(GL_ARRAY_BUFFER, contour.size() * sizeof(float), contour.data(), GL_DYNAMIC_DRAW);

		//	glEnableVertexAttribArray(0); // a_Position
		//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

		//	glDrawArrays(GL_LINE_STRIP, 0, contour.size() / 2);
		//}

		Input::ClearTextBuffer();
		m_Context->SwapBuffers();
	}
}

void Application::ShutDown()
{
	delete m_Window;
}