#include "shifter.hpp"
#include "display.hpp"
#include "timer.hpp"
#include "adc.hpp"

#include <avr/interrupt.h>

/**
 * Uśrednia pomiar temperatury.
 *
 * @return Uśredniona temperatura.
 */
uint16_t average()
{
	return adc.temperature();
}

/**
 * Obsługa przerwania pomiaru ADC.
 */
ISR(ADC_vect)
{
	display.print(average(), 2);
}

/**
 * Obsługa przerwania komparatora Timer/Counter0.
 */
ISR(TIMER0_OVF_vect)
{
	display.refresh();
}

/**
 * Funkcja główna.
 */
int main()
{
	shifter.initialize();
	timer.initialize();
	adc.initialize();

	sei();

	while (true) {
	}
}
