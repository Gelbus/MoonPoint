#include <cstdint>
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

/*
ƒл€ функции, котора€ получает высоту в цилиндрической проекции
нужно использвать карты формата: 

	"ldem_1024_{lat_range}_{lon_range}.img",

где:
	lat_range - диапазон широт формата {XXp_YYq}
		¬место XX и YY подставл€ютс€ величины широт
		¬место p и q подставл€ютс€:
			s - южна€ широта,
			n - северна€ широта

		90s - 90∞ ю.ш. (ёжный полюс)
		75s, 60s, 45s, 30s, 15s - соответствующие широты в южном полушарии.
		00s или 00n - экватор.
		15n, 30n, 45n, 60n, 75n - широты в северном полушарии.
		90n - 90∞ с.ш. (—еверный полюс)

		ѕример: 
			15s_00s Ч покрывает широты от 15∞ ю.ш. до 0∞ (экватор)
			45n_60n Ч покрывает широты от 45∞ с.ш. до 60∞ с.ш.


	lon_range - диапазон долгот формата {XXX_YYY}
		Ћежит в диапазоне от 0 до 360 градусов
		ѕример: 
			000_030 Ч покрывает долготы от 0∞ до 30∞. 
			330_360 Ч покрывает долготы от 330∞ до 360∞.


ѕример: 
	ldem_1024_15s_00s_120_150.img Ч это тайл карты высот с разрешением ~30 м,
	покрывающий область от 15∞ ю.ш. до экватора и от 120∞ до 150∞ долготы.
*/

unsigned long long int LINES = 15360;	// высота изображени€ в пиксел€х (строки, широта)
unsigned long long int LINE_SAMPLES = 30720;	// ширина изображени€ в пиесел€х (столбцы, долгота)
unsigned long long int SAMPLE_BITS = 16;		// вес одного значени€ в байтах
unsigned long long int OFFSET = 1737400;  // [м] смещение относительно центра, если нужен радиус, а не высота относительно референсной сферы

std::int64_t MINIMUM_LATITUDE = 0;		// [град]
std::int64_t MAXIMUM_LATITUDE = 15;		// [град]

std::int64_t WESTERNMOST_LONGITUDE = 0;		// [град]
std::int64_t EASTERNMOST_LONGITUDE = 30;	// [град]

std::uint16_t MAP_RESOLUTION = 1024;

double SCALING_FACTOR = 0.5;
double pixel_size = 1.0 / 1024.0;

double get_height_cylindrical_projection(int latitude, int longitude)
{
	std::uint8_t buf[2];	// буфер из 2 байт в который будем читать из файла
	std::uint16_t height;	// конечна€ переменна€ высоты

	std::string filename = "ldem_1024_00n_15n_000_030.img";	// им€ файла, позже нужно будет перенести это в класс

	std::ifstream input(filename, std::ios::binary);		// создаем поток ввода

	if (
		latitude < MINIMUM_LATITUDE || latitude > MAXIMUM_LATITUDE ||
		longitude < WESTERNMOST_LONGITUDE || longitude > EASTERNMOST_LONGITUDE
		) exit(404);	// провер€ем на корректность ввода, иначе выходим из файла

	int i = (int)std::floor((MAXIMUM_LATITUDE - latitude) * MAP_RESOLUTION);	// считаем позицию по строке
	i = i > LINES - 1 ? LINES - 1 : i;

	int j = (int)std::floor((longitude - WESTERNMOST_LONGITUDE) * MAP_RESOLUTION);	// считаем позицию по столбцу
	j = j > LINE_SAMPLES - 1 ? LINE_SAMPLES - 1 : j;


	int file_offset = (i * LINE_SAMPLES + j) * sizeof(int16_t);		// считаем смещение корретки в файле


	input.seekg(file_offset);	// смещаем корретку
	input.read((char*)&buf, 2);	// читаем из файла в буфер
	height = (buf[1] << 8 | buf[0]); // преобразовываем в Little Endian и записываем в переменную высоты

	return height * SCALING_FACTOR;
}



//std::int64_t LINES;	



int main()
{

	// пока сделан дл€ файла LDEM_1024_00N_15N_000_030.IMG по заданию 3 вариант
	int latitude, longitude;
	std::cin >> latitude >> longitude;

	std::cout << get_height_cylindrical_projection(latitude, longitude);

}