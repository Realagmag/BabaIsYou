# Dokumentacja wstępna

## Projekt i planowana funkcjonalność
Przedmiotem projektu jest stworzenie klona gry BabaIsYou. Planujemy przenieść główne funkcjonalności: wyświetlanie planszy, kilkanaście lub kilkadziesiąt możliwych obiektów, możliwość zmiany zasad poprzez przesuwanie odpowiednich bloków. Sterowanie będzie odbywać się strzałkami. Planujemy stworzyć kilka przykładowych leveli.
Główną biblioteka, której będziemy używać do tworzenia gry jest biblioteka SFML.

## Struktura projektu
Program będzie składał się z głównego pliku main.cpp oraz plików z klasami:
* Klasa **Game**: główna klasa, która odpowiada za start i trwanie gry.
* Klasa **Board**: Klasa przechowujaca planszę z aktualnym stanem gry. Planszę planujemy przechowywać w 3 wymiarowym wektorze składającym się ze sprytnych wskaźników do instancji klasy ObjectOnField (3 wymiary, ponieważ są w grze sytuacje kiedy na jednym polu znajduje się więcej niż jeden obiekt).
Klasa posiadać będzie również odpowiednie metody do wygodnej zmiany stanu planszy oraz do uzyskiwania informacji o aktualnym stanie gry.
* Klasa **ObjectOnField**: klasa reprezentującą każdy możliwy obiekt w grze, po niej dziedziczą klasy obiektów określonych typów.
Można wyróżnić 4 typy obiektów w grze:
* Klasa **ObjectOnField : SolidObject** : reprezentuje obiekty w grze takie jak Baba, Pilar czy Door. Innymi słowy wszystkie rzeczy na planszy poza słowami. Klasy dziedziczące po tej klasie przechowuja obrazek oraz flagi określające ich obecne zachowanie (isYou, isPush itd.).
* Klasa **ObjectOnField : ObjectWord**: reprezentuje słowa określające obiekty z klasy SolidObject, czyli może to być np. słowo BABA.
* Klasa **ObjectOnField : Operator** : reprezentuje operatory logiczne w grze jak IS, AND.
* Klasa **ObjectOnField : Keyword**: słowa określające obecne atrybuty SolidObjects, określające zasady gry. Są to np. słowa PUSH, WIN czy SHUT.

## Działanie programu
Zarys działania programu:
1. Gracz naciska jakąś strzałkę.
2. Wyszukujemy obiekty z flagą isYou i dla każdego wykonujemy akcje.
3. Sprawdzamy, co jest po tej stronie obiektów, w którą gracz chce się ruszyć.
4. Sprawdzamy cechy tego obiektu (czy PUSH, czy STOP itd.). Dalsze działanie jest zależne od cech obiektu, np. gdy STOP - kończymy ruch. Jeśli można nim poruszyć wykonujemy punkt 4 dla obiektu sąsiedniego dla tego obiektu itd. aż sprawdzimy wpływ ruchu na odpowiedni obszar planszy.
5. Jeśli możemy wykonujemy ruch w odpowiednią stronę. Jeśli YOU jest więcej niż jedno, wracamy do punktu 3 dla następnego "you".
6. Sprawdzamy nowe zasady (wzajemne ustawienie obiektów z klas ObjectWord, Operator i Keyword), odpowiednio przestawiamy flagi obiektów.
7. Renderujemy nową planszę.
8. Sprawdzamy czy gra zakończyła się zwycięstwem, jeśli nie - wracamy do punktu 1.

## Podział pracy
* Kamil Cisek - logika gry, projekt klas
* Konrad Karpiuk - kwestie związane z grafiką gry i biblioteką SFML
(tak planujemy, może się to trochę zmienić)
