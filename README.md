# A* Algorithm Implementation

Implementazione Algoritmo A* a delle entità mosse in automatico dal programma, al fine
di spostarle da un punto A a un punto B seguendo il percorso elaborato dall'Algoritmo A*
per trovare il percorso minimo. 

Per fare questo implemento un grafo connesso, tramite il quale il mio programma saprà 
trovare il cammino minimo. 

L'algoritmo A* trova il percorso più vicino tramite un numero finito di iterazioni.
Ci fornisce il costo per arrivare dal nodo in cui siamo a quello che intendiamo visitare
usando la somma tra il peso dell'arco tra questi due nodi e il costo EURISTICO per 
raggiungere il nodo dal punto di partenza. Quando avremo iterato abbastanza volte
(cioè avremo trovato il nodo di destinazione), il percorso trovato iterando tutte quelle
somme sarà il percorso più veloce tra il Nodo di partenza A e il nodo di Destinazione B.

Oltre a implementare il grafo e l'algoritmo, il mio scopo è quello di usare la 
libreria Google Test, prepadisponendo delle funzioni di TEST, e un main per l'esecuzione
di della funzione RUN_ALL_TEST().  

E' previsto anche il REFACTORING del codice sorgente.