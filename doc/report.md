---
title: "Ćwiczenie 6: Obsługa przetwornika analogowo-cyfrowego (ADC)"
author: [Mariusz Chilmon <<mariusz.chilmon@ctm.gdynia.pl>>]
lang: "pl"
titlepage: no
colorlinks: yes
header-right: "\\faEdit"
footer-left: "Sprawozdanie z laboratorium"
header-includes: |
  \usepackage{awesomebox}
  \usepackage{tikz}
  \usetikzlibrary{positioning}
...

_W trosce o Państwa wyniki proszę o czytelne wpisywanie nazwisk._

**Data**: \dotfill

**Autorzy**: \dotfill

# Część praktyczna

## Zadanie podstawowe

**Ocena prowadzącego**: \dotfill

## Zadanie rozszerzone

**Ocena prowadzącego**: \dotfill

# Część teoretyczna

## Zadanie podstawowe

W jakim zakresie częstotliwości taktowania ADC gwarantowane jest zachowanie najlepszych parametrów pomiaru? Jaką konkretnie częstotliwość można uzyskać w naszym przypadku?

\awesomebox[purple]{2pt}{\faMicrochip}{purple}{Częstotliwość taktowania mikrokontrolera wynosi 16~MHz.}

\awesomebox[violet]{2pt}{\faBook}{violet}{Szczegóły odnośnie taktowania ADC można znaleźć w rozdziale \textit{Analog-to-Digital Converter} w sekcji \textit{Prescaling and Conversion Timing} dokumentacji mikrokontrolera.}

\vspace{4.5cm}

Wyznacz wzór na mierzone napięcie w zależności od zawartości rejestrów `ADCL` i `ADCH` (w dokumentacji mikrokontrolera traktowanych łącznie jako `ADC`).

\awesomebox[violet]{2pt}{\faBook}{violet}{Szczegóły odnośnie wyniku pomiaru można znaleźć w rozdziale \textit{Analog-to-Digital Converter} w sekcji \textit{ADC Conversion Result} dokumentacji mikrokontrolera.}

\vspace{2.5cm}

Wyznacz wzór na zmierzoną temperaturę w zależności od napięcia wyjściowego na pinie _OUTPUT_ termometru LM35DZ.

\awesomebox[violet]{2pt}{\faBook}{violet}{Szczegóły odnośnie działania termometru najłatwiej odczytać ze schematu \textit{Basic Centigrade Temperature Sensor} w dokumentacji LM35DZ.}

## Zadanie rozszerzone

Jaką rozdzielczość pomiarową w V uzyskujemy przy napięciu referencyjnym 1,1&nbsp;V i 10-bitowej rozdzielczości ADC?

\vspace{2.5cm}

Jaką rozdzielczość pomiarową w °C uzyskujemy w powyższym przypadku dla termometru LM35DZ?

\vspace{2.5cm}
