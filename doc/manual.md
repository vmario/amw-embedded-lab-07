---
title: "Ćwiczenie 6: Obsługa przetwornika analogowo-cyfrowego (ADC)"
subtitle: "Instrukcja laboratorium"
footer-left: "Instrukcja laboratorium"
author: [Mariusz Chilmon <<mariusz.chilmon@ctm.gdynia.pl>>]
lang: "pl"
titlepage: yes
titlepage-logo: "logo.png"
logo-width: "70mm"
colorlinks: yes
header-includes: |
  \usepackage{awesomebox}
  \usepackage{algorithm}
  \usepackage{algpseudocode}
...

> People think that computer science is the art of geniuses but the actual reality is the opposite, just many people doing things that build on eachother, like a wall of mini stones.
>
> — _Donald Knuth_

# Cel ćwiczenia

Celem ćwiczenia jest zapoznanie się z:

* podstawową konfiguracją ADC,
* odczytem pomiaru z ADC,
* zmianą częstotliwości pomiarów,
* przeliczeniem rejestru pomiaru ADC na napięcie,
* przeliczeniem zmierzonego napięcia na temperaturę.

# Uruchomienie programu wyjściowego

1. Podłącz płytkę _WPSH209_ do _Arduino Uno_.
1. Podłącz termometr LM35DZ do linii _A5_.
1. Wynik pomiaru na wyświetlaczu ma wartość `00.00`.

# Zadanie podstawowe

Celem zadania podstawowego jest uruchomienie pomiaru temperatury z wykorzystaniem ADC mikrokontrolera i scalonego termometru analogowego LM35DZ.

\awesomebox[purple]{2pt}{\faMicrochip}{purple}{Przetwornik analogowo-cyfrowy (ADC, ang. \textit{Analog-to-Digital Converter}) zamienia sygnał analogowy, na ogół napięcie, na wartość cyfrową. Może być zewnętrznym układem scalonym lub, jak w tym przypadku, być wbudowany w mikrokontroler.}

## Wymagania funkcjonalne

1. Na wyświetlaczu prezentowana jest temperatura mierzona przez LM35DZ w °C z rozdzielczością do części setnych.

Pomiar, szczególnie na pozycjach mniej znaczących, może zmieniać się bardzo szybko przez co nie zawsze będzie czytelny.

## Modyfikacja programu

### Konfiguracja multiplekserów i preskalera

Zastosowany w mikrokontrolerze przetwornik analogowo-cyfrowy sukcesywnej aproksymacji wymaga doprowadzenia do przetwornika cyfrowo-analogowego (DAC) napięcia referencyjnego, względem którego będzie wykonywany pomiar (obwód zielony). W tym przypadku wykorzystujemy wbudowane w&nbsp;mikrokontroler napięcie odniesienia 1,1&nbsp;V. Wybór źródła napięcia referencyjnego odbywa się za pomocą bitów `REFS0`…`REFS1`.

Mierzone napięcie jest z kolei doprowadzane do komparatora próbkującego (obwód czerwony). Wykorzystujemy wejście _ADC5_, do którego podłączony jest termometr LM35DZ. Wybór mierzonego sygnału odbywa się za pomocą bitów `MUX0`…`MUX3`.

By działanie ADC było w ogóle możliwe, musi on być taktowany odpowiednim sygnałem zegarowym. Z dokumentacji mikrokontrolera można odczytać przedział częstotliwości, w których producent gwarantuje zachowanie optymalnych parametrów pomiaru, w szczególności zachowanie 10-bitowej rozdzielczości. Uzyskanie odpowiedniej częstotliwości jest możliwe przy dowolnej częstotliwości pracy mikrokontrolera dzięki preskalerowi o odpowiednim zakresie (obwód niebieski). Wybór stopnia podziału odbywa się za pomocą bitów `ADPS0`…`ADPS2`.

### Uruchomienie pomiaru

Po skonfigurowaniu multiplekserów i preskalera należy:

1. Włączyć tryb autowyzwalania przez ustawienie bitu `ADATE` (_ADC Auto Trigger Enable_), dzięki czemu pomiar nie będzie wykonany jednorazowo, ale po zakończeniu jednego pomiaru automatycznie będzie uruchamiany następny.
1. Włączyć ADC przez ustawienie bitu `ADEN` (_ADC Enable_).
1. Uruchomić pierwszą konwersję (pomiar) przez ustawienie bitu `ADSC` (_ADC Start Conversion_).

\awesomebox[purple]{2pt}{\faMicrochip}{purple}{Wszystkie trzy powyższe bity można ustawić jednocześnie, także wraz z bitami \lstinline{ADPS0}...\lstinline{ADPS2}.}

\awesomebox[teal]{2pt}{\faCode}{teal}{Konfigurację i uruchomienie przetwornika analogowo-cyfrowego umieść w funkcji \lstinline{adcInitialize()} w~pliku \lstinline{main.cpp}.}

![Schemat blokowy ADC](adc-block.png)

### Odczyt pomiaru

Wynik pomiaru należy odczytać z rejestrów `ADCL` i `ADCH` (pomiar jest 10-bitowy, więc jego wynik mieści się w dwóch rejestrach). Ponieważ mamy do czynienia z mikroprocesorem 8-bitowym, nie jest możliwy odczyt obu rejestrów w czasie jednej instrukcji. Może więc dojść do sytuacji, gdy między odczytem jednej i drugiej części pomiaru, pomiar ulegnie zmianie, w wyniku czego odczytamy część starszego i&nbsp;część nowszego pomiaru. Aby uniknąć takiej sytuacji, producent gwarantuje, że po odczytaniu rejestru `ADCL` zawartość `ADCH` nie ulegnie zmianie, dopóki nie zostanie odczytana. Należy więc zawsze w&nbsp;pierwszej kolejności odczytywać rejestr `ADCL`[^1].

[^1]: Kompilator AVR-GCC ma zdefiniowaną zmienną `ADC`, która umożliwia dostęp do obu rejestrów jako 16-bitowej całości, jednak jego dokumentacja nigdzie nie gwarantuje poprawnej kolejności odczytu.

Odczytaną wartość należy przeliczyć na napięcie, a następnie na temperaturę.

\awesomebox[teal]{2pt}{\faCode}{teal}{Odczyt i przeliczenie pomiaru umieść w funkcji \lstinline{measure()} (plik \lstinline{main.cpp}), która jest wywoływana przy każdym odświeżeniu wyświetlacza, a zwracana przez nią wartość jest na nim umieszczana.}

# Zadanie rozszerzone

Celem zadania rozszerzonego jest ułatwienie odczytu przez ograniczenie szybkości pomiaru.

## Wymagania funkcjonalne

1. Pomiar następuje nie częściej niż kilka razy na sekundę.

## Modyfikacja programu

Ustal odpowiedni dzielnik taktujący _Timer/Counter1_ (bity `CS10`…`CS12`). Flagą `TOIE1` włącz przerwanie od przepełnienia tego timera. Użyj bitów `ADTS0`…`ADTS2`, aby wybrać taktowanie pomiaru tym przerwaniem (_Timer/Counter1 Overflow_).

Częstotliwość przerwania w zależności od wybranego dzielnika $N$ dana jest wzorem:

\begin{equation}
f = \frac{f_{clkI/O}}{2^{16} N}
\end{equation}

