#pragma once

#include <stdint.h>

/**
 * Liczba cyfr na wyświetlaczu.
 */
constexpr uint8_t DISPLAY_SIZE{4};

/**
 * Sterownik wyświetlacza siedmiosegmentowego.
 */
struct Display {
	/**
	 * Odświeża wyświetlacz.
	 */
	void refresh() const;

	/**
	 * Drukuje liczbę do bufora wyświetlacza.
	 *
	 * @param number Liczba do wyświetlenia.
	 * @param dot Pozycja kropki dziesiętnej.
	 */
	void print(uint16_t number, uint8_t dot=DISPLAY_SIZE) const;
};

/**
 * Globalna instancja sterownika wyświetlacza.
 */
extern const Display display;
