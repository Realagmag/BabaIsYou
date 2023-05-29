# PROI_23L_103_Projekt_BabaIsYou_KC_KK

## Autorzy
Kamil Cisek i Konrad Karpiuk. Pomysł
## Struktura projektu
Program będzie składał się z głównego pliku main.cpp oraz plików z klasami:
* Klasa **Game**:
* Klasa **Window**:
* Klasa **AudioManager**:
* Klasa **Board**: Klasa przechowujaca planszę z aktualnym stanem gry. Planszę planujemy przechowywać w 3 wymiarowym wektorze składającym się ze sprytnych wskaźników do instancji klasy ObjectOnField (3 wymiary, ponieważ są w grze sytuacje kiedy na jednym polu znajduje się więcej niż jeden obiekt).
Klasa posiadać będzie również odpowiednie metody do wygodnej zmiany stanu planszy oraz do uzyskiwania informacji o aktualnym stanie gry.
* Klasa **ObjectOnField**: klasa reprezentującą każdy możliwy obiekt w grze, po niej dziedziczą klasy obiektów określonych typów.

Można wyróżnić 4 typy obiektów w grze:
* Klasa **ObjectOnField : SolidObject** : reprezentuje obiekty w grze takie jak Baba, Pilar czy Door. Innymi słowy wszystkie rzeczy na planszy poza słowami. Klasy dziedziczące po tej klasie przechowuja obrazek oraz flagi określające ich obecne zachowanie (isYou, isPush itd.).
* Klasa **ObjectOnField : Noun**: reprezentuje słowa określające obiekty z klasy SolidObject, czyli może to być np. słowo BABA.
* Klasa **ObjectOnField : Operator** : reprezentuje operatory logiczne w grze jak IS, AND.
* Klasa **ObjectOnField : Property**: słowa określające obecne atrybuty SolidObjects, określające zasady gry. Są to np. słowa PUSH, WIN czy SHUT.


## Instalacja
Na systemach Linuxowych typu Debian:
```
sudo apt-get install libsfml-dev
```

### Kompilacja
Aby dokonać kompilacji projektu i odpalenia:
```
cd ../proi_23l_103_projekt_babaisyou_kc_kk
cmake -S . -B build/
cd build/
make
./BabaIsYou
```

### Testy
Aby zrobić testy (pominąć dwa pierwsze punkty jeśli wykonano je wcześniej):
```
cd ../proi_23l_103_projekt_babaisyou_kc_kk
cmake -S . -B build/
cd build/
make test
./test
```

## Sterowanie
**Strzałki** do wyboru levelu. W trakcie rozgrywki:
* **Strzałka w górę** - obiekty "You" idą w górę
* **Strzałka w dół** - obiekty "You" idą w dół
* **Strzałka w lewo** - obiekty "You" idą w lewo
* **Strzałka w prawo** - obiekty "You" idą w prawo
* **R** - reset levelu
* **Q** - cofanie ruchu