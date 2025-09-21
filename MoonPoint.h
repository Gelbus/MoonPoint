#pragma once

#include <cstdint>
#include <fstream>
#include <string>

namespace mopo
{
	struct constant_map_data
	{
		std::uint32_t LINES = 15360;		// высота изображения в пикселях (строки, широта)
		std::uint32_t LINE_SAMPLES = 30720;	// ширина изображения в пиеселях (столбцы, долгота)
		std::uint32_t SAMPLE_BITS = 16;		// вес одного значения в байтах
		std::uint32_t OFFSET = 1737400;		// [м] смещение относительно центра, если нужен радиус, а не высота относительно референсной сферы

		std::uint16_t MINIMUM_LATITUDE = 0;		// [град] минимальная широта на выбранной карте
		std::uint16_t MAXIMUM_LATITUDE = 15;	// [град] максимальная широта на выбранной карте

		std::uint16_t WESTERNMOST_LONGITUDE = 0;	// [град] самая западная широта на выбранной карте
		std::uint16_t EASTERNMOST_LONGITUDE = 30;	// [град] самая восточная широта на выбранной карте

		std::uint16_t MAP_RESOLUTION = 1024;	// разрешение карты [пиксель/градус]

		float SCALING_FACTOR = 0.5;	// Коэффициент умножения

	};


	class MapTile
	{
	private:

		constant_map_data map_data;

		std::uint8_t buf[2];	// буфер из 2 байт в который будем читать из файла
		std::uint16_t dn;		// Digital Number, height = dn * SCALING_FACTOR

		std::ifstream input;	// создаем поток ввода

	public:

		void load_map_tile(std::string* filename);

		double get_height_cylindrical_projection(std::uint16_t latitude, std::uint16_t longitude);
	};
	
}
