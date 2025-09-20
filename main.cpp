#include <cstdint>
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

/*
��� �������, ������� �������� ������ � �������������� ��������
����� ����������� ����� �������: 

	"ldem_1024_{lat_range}_{lon_range}.img",

���:
	lat_range - �������� ����� ������� {XXp_YYq}
		������ XX � YY ������������� �������� �����
		������ p � q �������������:
			s - ����� ������,
			n - �������� ������

		90s - 90� �.�. (����� �����)
		75s, 60s, 45s, 30s, 15s - ��������������� ������ � ����� ���������.
		00s ��� 00n - �������.
		15n, 30n, 45n, 60n, 75n - ������ � �������� ���������.
		90n - 90� �.�. (�������� �����)

		������: 
			15s_00s � ��������� ������ �� 15� �.�. �� 0� (�������)
			45n_60n � ��������� ������ �� 45� �.�. �� 60� �.�.


	lon_range - �������� ������ ������� {XXX_YYY}
		����� � ��������� �� 0 �� 360 ��������
		������: 
			000_030 � ��������� ������� �� 0� �� 30�. 
			330_360 � ��������� ������� �� 330� �� 360�.


������: 
	ldem_1024_15s_00s_120_150.img � ��� ���� ����� ����� � ����������� ~30 �,
	����������� ������� �� 15� �.�. �� �������� � �� 120� �� 150� �������.
*/

unsigned long long int LINES = 15360;	// ������ ����������� � �������� (������, ������)
unsigned long long int LINE_SAMPLES = 30720;	// ������ ����������� � �������� (�������, �������)
unsigned long long int SAMPLE_BITS = 16;		// ��� ������ �������� � ������
unsigned long long int OFFSET = 1737400;  // [�] �������� ������������ ������, ���� ����� ������, � �� ������ ������������ ����������� �����

std::int64_t MINIMUM_LATITUDE = 0;		// [����]
std::int64_t MAXIMUM_LATITUDE = 15;		// [����]

std::int64_t WESTERNMOST_LONGITUDE = 0;		// [����]
std::int64_t EASTERNMOST_LONGITUDE = 30;	// [����]

std::uint16_t MAP_RESOLUTION = 1024;

double SCALING_FACTOR = 0.5;
double pixel_size = 1.0 / 1024.0;

double get_height_cylindrical_projection(int latitude, int longitude)
{
	std::uint8_t buf[2];	// ����� �� 2 ���� � ������� ����� ������ �� �����
	std::uint16_t height;	// �������� ���������� ������

	std::string filename = "ldem_1024_00n_15n_000_030.img";	// ��� �����, ����� ����� ����� ��������� ��� � �����

	std::ifstream input(filename, std::ios::binary);		// ������� ����� �����

	if (
		latitude < MINIMUM_LATITUDE || latitude > MAXIMUM_LATITUDE ||
		longitude < WESTERNMOST_LONGITUDE || longitude > EASTERNMOST_LONGITUDE
		) exit(404);	// ��������� �� ������������ �����, ����� ������� �� �����

	int i = (int)std::floor((MAXIMUM_LATITUDE - latitude) * MAP_RESOLUTION);	// ������� ������� �� ������
	i = i > LINES - 1 ? LINES - 1 : i;

	int j = (int)std::floor((longitude - WESTERNMOST_LONGITUDE) * MAP_RESOLUTION);	// ������� ������� �� �������
	j = j > LINE_SAMPLES - 1 ? LINE_SAMPLES - 1 : j;


	int file_offset = (i * LINE_SAMPLES + j) * sizeof(int16_t);		// ������� �������� �������� � �����


	input.seekg(file_offset);	// ������� ��������
	input.read((char*)&buf, 2);	// ������ �� ����� � �����
	height = (buf[1] << 8 | buf[0]); // ��������������� � Little Endian � ���������� � ���������� ������

	return height * SCALING_FACTOR;
}



//std::int64_t LINES;	



int main()
{

	// ���� ������ ��� ����� LDEM_1024_00N_15N_000_030.IMG �� ������� 3 �������
	int latitude, longitude;
	std::cin >> latitude >> longitude;

	std::cout << get_height_cylindrical_projection(latitude, longitude);

}