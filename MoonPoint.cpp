#include "MoonPoint.h"

#include <cmath>


void mopo::MapTile::load_map_tile(std::string* filename)
{
	input = std::ifstream(*filename, std::ios::binary);
}

double mopo::MapTile::get_height_cylindrical_projection(std::uint16_t latitude, std::uint16_t longitude)
{
	// ��������� �� ������������ �����, ����� ������� �� �����
	if (latitude < map_data.MINIMUM_LATITUDE || latitude > map_data.MAXIMUM_LATITUDE ||
		longitude < map_data.WESTERNMOST_LONGITUDE || longitude > map_data.EASTERNMOST_LONGITUDE) exit(404);

	// ������� ������� �� ������
	std::uint32_t row = (std::uint32_t)std::floor((map_data.MAXIMUM_LATITUDE - latitude) * map_data.MAP_RESOLUTION);
	row = row > map_data.LINES - 1 ? map_data.LINES - 1 : row;

	// ������� ������� �� �������
	std::uint32_t col = (std::uint32_t)std::floor((longitude - map_data.WESTERNMOST_LONGITUDE) * map_data.MAP_RESOLUTION);
	col = col > map_data.LINE_SAMPLES - 1 ? map_data.LINE_SAMPLES - 1 : col;

	// ������� �������� �������� � �����
	std::uint32_t file_offset = (row * map_data.LINE_SAMPLES + col) * sizeof(uint16_t);


	input.seekg(file_offset);		// ������� ��������
	input.read((char*)&buf, 2);		// ������ �� ����� � �����
	dn = (buf[1] << 8 | buf[0]);	// ��������������� � Little Endian � ���������� � ���������� ������

	return (double)dn * (double)map_data.SCALING_FACTOR;
}



