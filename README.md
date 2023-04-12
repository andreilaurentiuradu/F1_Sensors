# tema1_iocla
// Radu Andrei-Laurentiu 312CC

Problema consta in citirea datelor senzorilor dintr-un fisier binar
si aplicarea operatiilor print, analyze, clear si exit citite de la tastatura.

print <index>
Operatia print se realizeaza afisand datele senzorului de la indexul dat in
functie de prioritatea lui. Sortam folosind bubble sort elementele vectorului
astfel incat senzorii de acelasi tip sa-si pastreze ordinea in vector, iar cei
de tip PMU sa apara primii.

analyze <index>
Pentru operatia analyze cream un vector de pointeri la functii. In functie de
numarul operatiei apelam o anumita functie pentru senzorul index.

Pentru operatiile analyze si print in cazul unui index negativ sau mai mare
decat nr de senzori vom afisa un mesaj corespunzator.
clear
Pentru operatia clear verificam fiecare senzor daca are datele valide. In
caz contrar, eliberam memoria ocupata de acesta si shiftam la stanga senzorii.

exit
In momentul apelului functiei exit eliberam memoria utilizata si inchidem
programul.

Implementarea functiilor se afla in my_operations.c.
