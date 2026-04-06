# Classi4 - Spiegazione del codice live coding

Questo file documenta il contenuto di `Classi1.cpp`.

## Obiettivo dell'esempio

Il programma mostra:
- definizione di una classe (`Foo`)
- costruttore e distruttore
- uso di un puntatore come attributo privato
- creazione di oggetti globali, locali e array di oggetti

## Struttura della classe `Foo`

La classe contiene:
- `int *x;` come attributo privato
- metodi pubblici:
  - `Foo();` costruttore
  - `~Foo();` distruttore
  - `void print();` stampa `x`
  - `void setX(int a);` assegna un valore a `*x`

## Comportamento dei metodi

### Costruttore `Foo::Foo()`

Nel costruttore:
- viene allocata memoria dinamica con `new int`
- il valore puntato viene inizializzato a `0`
- viene stampato un messaggio di debug

### Distruttore `Foo::~Foo()`

Nel distruttore attuale:
- viene solo stampato il valore del puntatore `x`
- **non** viene liberata la memoria con `delete x`

Questa scelta e utile per mostrare il flusso del programma, ma in un caso reale puo causare memory leak.

### Metodo `setX(int a)`

Assegna il valore passato al contenuto puntato:
- `*x = a;`

### Metodo `print()`

Stampa il valore di `x` (cioe l'indirizzo in memoria), non `*x`.

## Oggetto globale

`Foo globale;` e dichiarato fuori da `main`.

Quindi:
- il suo costruttore viene chiamato prima dell'ingresso in `main`
- il suo distruttore viene chiamato alla fine del programma

## Funzione `main()`

In `main` vengono stampati messaggi di inizio/fine.

Nel codice attuale viene creato:
- `Foo myv1[10];`

Questo provoca 10 chiamate al costruttore e, a fine scope, 10 chiamate al distruttore.

Sono presenti anche blocchi commentati che mostrano:
- uso di due oggetti locali separati
- uso di un oggetto su heap con puntatore (`Foo* pf = new Foo;`)
- accesso ai membri con `->`
- `delete pf`

## Nota didattica importante

Per rendere la classe corretta dal punto di vista della gestione memoria, nel distruttore sarebbe meglio fare:

```cpp
Foo::~Foo() {
    delete x;
    x = nullptr;
}
```

Inoltre, se vuoi stampare il valore intero memorizzato, in `print()` dovresti usare `*x` invece di `x`.

## Compilazione ed esecuzione (esempio)

```bash
g++ Classi1.cpp -std=c++17 -Wall -Wextra -o Classi1
./Classi1
```
