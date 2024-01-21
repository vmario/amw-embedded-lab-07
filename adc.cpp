#include "adc.hpp"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

const Adc adc;

/**
 * Obsługa przerwania przepełnienia Timer/Counter1.
 */
ISR(TIMER1_OVF_vect)
{
}

void Adc::initialize() const
{
	TCCR1B = _BV(CS12);
	TIMSK1 = _BV(TOIE1);

	ADMUX = _BV(REFS1) | _BV(REFS0) | _BV(MUX2) | _BV(MUX0);
	ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADATE) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);

	// XXX: Czas na ustabilizowanie źródła napięcia referencyjnego oraz wykonanie pierwszego,
	// mniej precyzyjnego pomiaru.
	_delay_ms(1);

	ADCSRB = _BV(ADTS2) | _BV(ADTS1);
}

double Adc::temperature() const
{
	constexpr auto REFERENCE_VOLTAGE{1.1};
	constexpr auto RESOLUTION{1024};
	constexpr auto SCALE{10000};

	uint16_t value = ADCL;
	value += ADCH << 8;

	return REFERENCE_VOLTAGE / RESOLUTION * SCALE * value;
}
