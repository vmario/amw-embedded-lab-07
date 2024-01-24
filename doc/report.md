---
title: "Ćwiczenie 7: Uśrednianie danych pomiarowych"
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

Pomiar wykonywany jest z częstotliwością 0,95&nbsp;Hz. Uśredniamy 20 ostatnich pomiarów. Z jakiego przedziału czasu uwzględniane są pomiary?

\vspace{3cm}

## Zadanie rozszerzone

Odczytaj z procesu kompilacji rozmiar programu (segment `.text`) oraz rozmiar danych globalnych i&nbsp;statycznych w pamięci RAM (segment `.bss`) dla Twojego programu. Zwiększ liczbę uśrednianych próbek z 20 do 32 i powtórnie odczytaj rozmiary segmentów. Oblicz różnicę tych rozmiarów między dwoma wersjami programu.

\begin{center}
\begin{tabular}{ |c|c|c|c| } 
\hline
 & $k = 20$ & $k = 32$ & Różnica \\
\hline
\texttt{.text} & & & \\ 
\hline
\texttt{.bss} & & & \\ 
\hline
\end{tabular}
\end{center}

Jaki rozmiar ma typ `double` lub inny użyty przez Ciebie do przechowywania poprzednich próbek? Jaki rozmiar ma zazwyczaj typ `double` na komputerach PC (zgodnie z IEEE 754)?

\vspace{3cm}

## \faCertificate&nbsp; Zadanie specjalne

_+1 pkt dla osoby, która jako pierwsza poda poprawną odpowiedź._

Dlaczego po zwiększeniu rozmiaru tablicy zmniejszył się rozmiar kodu programu, a więc liczba instrukcji?
