#include "display.hpp"

#include "shifter.hpp"

#include <stdint.h>

const Display display;

namespace {
/**
 * Wzorce cyfr na wyświetlaczu siedmiosegmentowym.
 */
constexpr uint8_t FONT[] = {
	0b00000011, // 0
	0b10011111, // 1
	0b00100101, // 2
	0b00001101, // 3
	0b10011001, // 4
	0b01001001, // 5
	0b01000001, // 6
	0b00011111, // 7
	0b00000001, // 8
	0b00001001, // 9
};

/**
 * Tablica cyfr na wyświetlaczu (od prawej do lewej).
 */
uint8_t DIGITS[DISPLAY_SIZE] = {FONT[0], FONT[0], FONT[0], FONT[0]};


/**
 * Wyświetla pojedynczą cyfrę na wyświetlaczu.
 *
 * @param value Cyfra do wyświetlenia.
 * @param position Numer cyfry na wyświetlaczu (od prawej do lewej).
 */
void showDigit(uint8_t value, uint8_t position)
{
	shifter.shift(value);
	shifter.shift(1 << (position + 4));
	shifter.latch();
}
}

/**
 * Odświeża wyświetlacz, wyświetlając za każdym razem kolejną cyfrę z tablicy DIGITS.
 */
void Display::refresh() const
{
	static uint8_t cursor;

	showDigit(DIGITS[cursor], cursor);

	if (++cursor >= DISPLAY_SIZE) {
		cursor = 0;
	}
}

void Display::print(uint16_t number, uint8_t dot) const
{
	for (uint8_t i = 0; i < DISPLAY_SIZE; ++i) {
		DIGITS[i] = FONT[number % 10] & ~((i == dot) ? 1 : 0);
		number /= 10;
	}
}
