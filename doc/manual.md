---
title: "Ćwiczenie 7: Uśrednianie danych pomiarowych"
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

> If you can't describe what you are doing as a process, you don't know what you're doing.
>
> — _W. Edwards Deming_

# Cel ćwiczenia

Celem ćwiczenia jest zapoznanie się z:

* algorytmem średniej kroczącej,
* rozmiarem danych typu zmiennoprzecinkowego,
* wpływem obliczeń zmiennoprzecinkowych na rozmiar kodu wykonywalnego.

# Uruchomienie programu wyjściowego

1. Podłącz płytkę _WPSH209_ do _Arduino Uno_.
1. Podłącz termometr LM35DZ do linii _A5_.
1. Wyświetlacz wskazuje bieżącą temperaturę aktualizowaną mniej więcej co sekundę.

# Zadanie podstawowe

Celem zadania podstawowego jest uśrednienie temperatury za pomocą prostej średniej kroczącej $SMA_k$ (ang. _Simple Moving Average_), która dla pomiarów $p_1, p_2, \dots, p_n$, jest średnią liczoną z ostatnich $k$ pomiarów:

\begin{equation}
SMA_k = \frac{1}{k} \sum^n_{i=n-k+1} p_i = \frac{p_{n-k+1} + p_{n-k+2} + \cdots + p_{n}}{k}
\end{equation}

Średnia krocząca, stosowana powszechnie w analizie danych finansowych, pozwala także na proste &bdquo;wygładzenie&rdquo; danych pomiarowych. W przypadku pomiaru temperatury zmniejsza to wrażliwość na krótkie wahania temperatury spowodowane np. podmuchem powietrza.

\awesomebox[purple]{2pt}{\faMicrochip}{purple}{W programie wyjściowym pomiary są odczytywane w przerwaniu \lstinline{ADC_vect}, a więc dokładnie wtedy, gdy przetwornik analogowo-cyfrowy zakończy dany pomiar.}

![Średnia krocząca (kolor czerwony) z danych pomiarowych (kolor niebieski)](sma.svg){width=9cm}

## Wymagania funkcjonalne

1. Na wyświetlaczu prezentowana jest uśredniona temperatura z ostatnich 20 pomiarów.

Pierwsze 19 wyników będzie zafałszowane ze względu na to, że tablica używana do uśredniania początkowo wypełniona jest zerami.

## Modyfikacja programu

Implementacja algorytmu wymaga zadeklarowania statycznej tablicy o rozmiarze, który najlepiej określić stałą, używaną dalej w algorytmie:

```cpp
constexpr uint8_t SIZE = 20;
static double measures[SIZE];
```

\awesomebox[teal]{2pt}{\faCode}{teal}{Zmienne statyczne i globalne domyślnie inicijalizowane są zerami.}

\begin{algorithm}
\caption{Średnia krocząca $SMA_{size}$}
\begin{algorithmic}[1]
    \State $measures_{index}\gets \Call{adc.temperature}$
    \Comment{zapis bieżącego pomiaru}
    \State $sum \gets 0$
    \For{$i \gets 0$ to $size$}
    \Comment{sumowanie wszystkich $size$ ostatnich pomiarów}
        \State $sum \gets sum + measures_i$
    \EndFor
    \State $index\gets index + 1$
    \Comment{obliczamy kolejny indeks w tablicy $measures$}
    \If{$index \geq size$}
    \Comment{pilnujemy, by nie przekroczyć rozmiaru tablicy}
        \State $index\gets 0$
    \EndIf
    \State \Return {$\frac{sum}{size}$}
    \Comment{zwracamy średnią}
\end{algorithmic}
\end{algorithm}

# Zadanie rozszerzone

Celem zadania rozszerzonego jest wstępne inicjalizacja średniej pierwszym pomiarem.

## Wymagania funkcjonalne

1. Urządzenie od razu po uruchomieniu wskazuje bieżącą temperaturę.

## Modyfikacja programu

Po uruchomieniu urządzenia tablica pomiarów powinna zostać wypełniona wartością pierwszego pomiaru.
