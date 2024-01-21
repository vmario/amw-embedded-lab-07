#pragma once

#include <stdint.h>

/**
 * Sterownik ADC.
 */
struct Adc {
	/**
	 * Konfiguruje i uruchamia ADC.
	 */
	void initialize() const;

	/**
	 * Odczytuje wynik pomiaru napięcia z ADC i przelicza go na temperaturę.
	 *
	 * @return Temperatura w °C.
	 */
	double temperature() const;
};

/**
 * Globalna instancja sterownika ADC.
 */
extern const Adc adc;
