#pragma once

#include <cstdint>
#include <fstream>
#include <string>

namespace mopo
{
	struct constant_map_data
	{
		std::uint32_t LINES = 15360;		// ������ ����������� � �������� (������, ������)
		std::uint32_t LINE_SAMPLES = 30720;	// ������ ����������� � �������� (�������, �������)
		std::uint32_t SAMPLE_BITS = 16;		// ��� ������ �������� � ������
		std::uint32_t OFFSET = 1737400;		// [�] �������� ������������ ������, ���� ����� ������, � �� ������ ������������ ����������� �����

		std::uint16_t MINIMUM_LATITUDE = 0;		// [����] ����������� ������ �� ��������� �����
		std::uint16_t MAXIMUM_LATITUDE = 15;	// [����] ������������ ������ �� ��������� �����

		std::uint16_t WESTERNMOST_LONGITUDE = 0;	// [����] ����� �������� ������ �� ��������� �����
		std::uint16_t EASTERNMOST_LONGITUDE = 30;	// [����] ����� ��������� ������ �� ��������� �����

		std::uint16_t MAP_RESOLUTION = 1024;	// ���������� ����� [�������/������]

		float SCALING_FACTOR = 0.5;	// ����������� ���������

	};


	class MapTile
	{
	private:

		constant_map_data map_data;

		std::uint8_t buf[2];	// ����� �� 2 ���� � ������� ����� ������ �� �����
		std::uint16_t dn;		// Digital Number, height = dn * SCALING_FACTOR

		std::ifstream input;	// ������� ����� �����

	public:

		void load_map_tile(std::string* filename);

		double get_height_cylindrical_projection(std::uint16_t latitude, std::uint16_t longitude);
	};
	
}
