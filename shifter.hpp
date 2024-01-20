#pragma once

#include <stdint.h>

/**
 * Sterownik rejestru przesuwnego.
 */
struct Shifter {
	/**
	 * Inicjalizacja GPIO sterującego rejestrem przesuwnym.
	 */
	void initialize() const;

	/**
	 * Wprowadza bajt do rejestru.
	 *
	 * @param byte Bajt wprowadzany do rejestru.
	 */
	void shift(uint8_t byte) const;

	/**
	 * Zatrzaskuje dane wprowadzone do rejestru na jego wyjściu.
	 */
	void latch() const;
};

/**
 * Globalna instancja sterownika rejestru przesuwnego.
 */
extern const Shifter shifter;
