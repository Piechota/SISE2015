Tasklist:

Milestone 10, 00011000.0100:
	Lukasz Spierewka
		- uzupelnianie statystyk
		
	Filip Wrobel
		- integracja modulow, aka fixowanie wszystkiego
		
	Lukasz Nizik
		- komunikaty dla GameControllera na konsoli
		
	Konrad Piechota
		- sterowanie mata taneczna i myszka
	
	Mateusz Lewandowski
		- postawienie gry dla wielu graczy
		- sudden death po 100 turach
		
	Filip Wiechowski
		- skalowanie grafu do okna, okna, okna i romiaru okna
		
Milestone 00, 00010001.0100:
	Lukasz Spierewka
		- generacja grafu
		- struktury nodeów

	Filip Wrobel
		- klasa pawn
		- komendy do sterowania

	Lukasz Nizik
		- silnik tur
		- abstrakcja miedzy grafem, a graczami

	Konrad Piechota
		- generyczne wyswietlanie

	Mateusz Lewandowski
		- player manualny

	Filip Wiechowski
		- system statystyk
		- wyswietlanie danych gry

	Co mielismy zrobic:

GDD:

- 0010 do 0110 graczy na grafie, gra turowa
- zliczamy statystyki kills/deaths/survival
Kills +1 za kazde trafienie w przeciwnika
Deaths +1 za kazda smierc
Survival +1 za kazda smierc przeciwnika

- gracze wydaja polecenia jednoczesnie
- w kazdej turze gracz moze sie zabic, wykonac ruch do przylegajacego wezla na grafie, wykonac strzal w przylegajacy wezel,
	albo nie podjac dzialania

- najpierw rozstrzygane sa samobójstwa, nastepnie, ruchy, na koncu strzaly

- jak kilku graczy zabije tego samego gracza w tej samej turze, to wszyscy dostaja punkt
- 0010 graczy nie moze stanac na tym samym polu
- jesli kilku graczy w tej samej turze ruszy sie na to samo pole to zostaja odbici

- gdy gracz stoi na polu, w które ktos strzeli, umiera (znika z grafu)
- gra konczy sie jesli na grafie zostanie 1 gracz lub minie maksymalna ilosc tur
