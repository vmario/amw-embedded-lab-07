#include "shifter.hpp"

#include <avr/io.h>

#define DDR_SDI DDRB ///< Rejestr kierunku pinu danych.
#define DDR_CLOCK DDRD ///< Rejestr kierunku zegarów.

#define PORT_SDI PORTB ///< Wyjście pinu danych.
#define PORT_CLOCK PORTD ///< Wyjście zegarów.

const Shifter shifter;

namespace {
/**
 * Numery pinów sterujących rejestrem przesuwnym.
 */
enum PIN {
	PIN_SDI = 0, ///< Dane wejściowe.
	PIN_CLOCK_SHIFT = 7, ///< Taktowanie danych.
	PIN_CLOCK_LATCH = 4, ///< Zatrzask.
};
}

/**
 * Inicjalizuje porty GPIO.
 */
void Shifter::initialize() const
{
	DDR_SDI = _BV(PIN_SDI);
	DDR_CLOCK = _BV(PIN_CLOCK_SHIFT) | _BV(PIN_CLOCK_LATCH);
}

/**
 * Umieszcza pojedynczy bajt w rejestrze przesuwnym.
 *
 * @param byte Bajt umieszczany w rejestrze.
 */
void Shifter::shift(uint8_t byte) const
{
	for (uint8_t i = 0; i < 8; ++i) {
		if (byte & 0x01) {
			PORT_SDI |= _BV(PIN_SDI);
		} else {
			PORT_SDI &= ~_BV(PIN_SDI);
		}

		byte >>= 1;

		PORT_CLOCK |= _BV(PIN_CLOCK_SHIFT);
		PORT_CLOCK &= ~_BV(PIN_CLOCK_SHIFT);
	}
}

/**
 * Zatrzaskuje dane (przepisuje je na wyjście).
 */
void Shifter::latch() const
{
	PORT_CLOCK |= _BV(PIN_CLOCK_LATCH);
	PORT_CLOCK &= ~_BV(PIN_CLOCK_LATCH);
}
