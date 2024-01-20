#include "timer.hpp"

#include <avr/io.h>

const Timer timer;

namespace {
/**
 * Preskaler Timer/Counter0.
 */
constexpr uint8_t TIMER_PRESCALER = _BV(CS02);
}

/**
 * Inicjalizuje Timer/Counter0.
 */
void Timer::initialize() const
{
	TCCR0B = TIMER_PRESCALER;
	TIMSK0 = _BV(TOIE0);
}

