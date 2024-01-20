#pragma once

#include <stdint.h>

/**
 * Częstotliwość przerwania przepełnienia Timer/Counter1. [Hz]
 */
constexpr uint32_t TIMER_FREQUENCY{1000};

/**
 * Timer taktujący system.
 */
struct Timer {
	/**
	 * Inicjalizacja timera.
	 */
	void initialize() const;
};

/**
 * Globalna instancja timera.
 */
extern const Timer timer;
