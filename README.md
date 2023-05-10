## PROI_23L_103_Projekt_BabaIsYou_KC_KK

### Kompilacja projektu
Aby dokonać kompilacji projektu i odpalenie:
```
cd ../proi_23l_103_projekt_babaisyou_kc_kk
cmake -S . -B build/
cd build/
make
./BabaIsYou
```

### Testy
Aby zrobić testy (pominąć dwa pierwsze punkty jeśli wykonano je wczęśniej):
```
cd ../proi_23l_103_projekt_babaisyou_kc_kk
cmake -S . -B build/
cd build/
make test
./test
```