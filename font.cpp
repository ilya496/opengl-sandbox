#include "font.h"

int64_t ReadInt64(std::ifstream& file) {
	uint8_t bytes[8];
	file.read(reinterpret_cast<char*>(bytes), 8);
	return (int64_t(
		(uint64_t(bytes[0]) << 56) |
		(uint64_t(bytes[1]) << 48) |
		(uint64_t(bytes[2]) << 40) |
		(uint64_t(bytes[3]) << 32) |
		(uint64_t(bytes[4]) << 24) |
		(uint64_t(bytes[5]) << 16) |
		(uint64_t(bytes[6]) << 8) |
		uint64_t(bytes[7])
	));
}

uint32_t ReadUInt32(std::ifstream& file)
{
	uint8_t bytes[4];
	file.read(reinterpret_cast<char*>(bytes), 4);
	return (static_cast<uint32_t>(bytes[0]) << 24) |
		(static_cast<uint32_t>(bytes[1]) << 16) |
		(static_cast<uint32_t>(bytes[2]) << 8) |
		static_cast<uint32_t>(bytes[3]);
}

int32_t ReadInt32(std::ifstream& file)
{
	uint32_t val = ReadUInt32(file);
	return static_cast<int32_t>(val);
}

uint16_t ReadUInt16(std::ifstream& file)
{
	uint8_t bytes[2];
	file.read(reinterpret_cast<char*>(bytes), 2);
	return (static_cast<uint16_t>(bytes[0]) << 8) |
		static_cast<uint16_t>(bytes[1]);
}

int16_t ReadInt16(std::ifstream& file)
{
	uint16_t val = ReadUInt16(file);
	return static_cast<int16_t>(val);
}

float ReadFixed(std::ifstream& file) {
	int32_t raw = ReadInt32(file);
	return static_cast<float>(raw) / 65536.0f;
}

bool IsFlagBitSet(uint8_t flag, int bitIndex)
{
	return ((flag >> bitIndex) & 1) == 1;
}

std::time_t MacToUnixTime(int64_t macTime) {
	return static_cast<std::time_t>(macTime - 2082844800);
}

std::string FormatDate(std::time_t t) {
	std::tm timeinfo;
	gmtime_s(&timeinfo, &t);
	char buffer[32];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S UTC", &timeinfo);
	return std::string(buffer);
}

math::vec2 QuadraticBezier(const math::vec2& p0, const math::vec2& p1, const math::vec2& p2, float t)
{
	return (1 - t) * (1 - t) * p0 +
		2 * (1 - t) * t * p1 +
		t * t * p2;
}

float ReadF2Dot14(std::ifstream& file)
{
	int16_t raw = ReadInt16(file); // Read signed 16-bit integer
	return raw / 16384.0f;         // 2^14 = 16384
}