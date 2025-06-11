# Documentazione Sistema di Pianificazione e Monitoraggio delle Attività di Studio

## Architettura del Modulo Planner

### 1. Motivazione della Scelta dell’ADT

Per questo progetto sono stati scelti tre tipi principali di Abstract Data Type (ADT):

- **Coda con priorità (Priority Queue)**: utilizzata per gestire le attività in corso (`inProgress`), consentendo un accesso rapido alle attività con priorità più alta. Questa scelta è giustificata dal fatto che le attività urgenti o più rilevanti devono poter essere identificate e gestite rapidamente.

- **Lista collegata (Linked List)**: impiegata per le attività completate (`completed`) e quelle scadute (`expired`), poiché non richiedono un ordinamento dinamico per priorità ma solo operazioni di inserimento in testa e scorrimento sequenziale.

- **Struttura `Planner`**: una struttura aggregata che racchiude le tre componenti fondamentali del sistema (attività in corso, completate e scadute), permettendo una gestione centralizzata e modulare del piano di studio.

### 2. Progettazione

Il sistema è strutturato nei seguenti moduli:

- **`task`**: definisce le operazioni e le informazioni associate a una singola attività di studio (titolo, corso, descrizione, deadline, priorità, tempo stimato, progresso).

- **`pQueue`**: gestisce la coda di priorità, usata per ordinare le attività in base all’urgenza.

- **`list`**: gestisce le attività terminate e scadute.

- **`planner`**: contiene tutte le attività raggruppate per stato (in corso, completate, scadute).

- **`char`**: gestisce l'input/output e il formato delle date.

- **`main`** (o modulo interfaccia): offre un’interfaccia testuale semplificata per interagire con il sistema.

Ogni componente comunica attraverso interfacce ben definite, con funzioni specifiche che rispettano il principio della separazione delle responsabilità.

## Documentazione delle funzioni fornite 

### `checkExpired`
```c
bool checkExpired(Planner p);
```
**Semantic**: Checks for tasks whose deadline has passed, moves them from the in-progress queue to the expired list, and prints their titles.

**Preconditions**:
- `p` must be initialized.
- `p->inProgress` must not be `NULL`.

**Postconditions**:
- Tasks past their deadline are moved to the expired list.
- Returns `true` if any expired tasks were found.

**Side Effects**:
- Modifies the planner queues.
- Prints status messages.

---

### `openPlanner`
```c
Planner openPlanner();
```
**Semantic**: Allocates and initializes a Planner structure, loads data from files, checks for expired tasks, and conditionally generates the weekly report.

**Preconditions**:
- The file paths "./Data/progress.txt", "./Data/completed.txt", and "./Data/expired.txt" must be accessible.
- The global variable 'today' must be initialized.

**Postconditions**:
- Returns a valid Planner object with its queues populated, or NULL in case of memory errors.

**Side Effects**:
- Reads from files.
- Allocates memory.
- Outputs error messages.
- May trigger report generation and task reorganization.

---

### `closePlanner`
```c
int closePlanner(Planner p);
```
**Semantic**: Saves planner state to disk and deallocates all memory.

**Preconditions**:
- `p` must be valid.

**Postconditions**:
- Data is saved and memory is freed.

**Side Effects**:
- File writing, memory release.

---

### `setCompleted`
```c
int setCompleted(Task t, Planner p);
```
**Semantic**: Marks a task as completed, updates its completion date, and moves it to the completed list.

**Preconditions**:
- `t` must not be `NULL`.

**Postconditions**:
- Task is updated and relocated to `completed`.

**Side Effects**:
- Task fields are modified.

---

### `restoreExpiredTask`
```c
int restoreExpiredTask(Planner p);
```
**Semantic**: Restores an expired task by allowing the user to modify deadline and priority, then moves it back into the in-progress queue.

**Preconditions**:
- `p->expired` must contain at least one task.

**Postconditions**:
- Task is updated and moved to `inProgress`.

**Side Effects**:
- User interaction, queue modification.

---

### `printPlanner`
```c
void printPlanner(Planner p);
```
**Semantic**: Displays all tasks grouped by their state (completed, in-progress, expired).

**Preconditions**:
- `p` must be initialized.

**Postconditions**:
- Task details are printed.

**Side Effects**:
- Terminal output.

---

### `insert`
```c
int insert(Planner p);
```
**Semantic**: Creates and inserts a new task into the in-progress queue.

**Preconditions**:
- `p` must be initialized.

**Postconditions**:
- New task is added or an error is returned.

**Side Effects**:
- Memory allocation, queue editing.

---

### `modifyTask`
```c
Planner modifyTask(Planner p);
```
**Semantic**: Edits an existing task’s attributes. If set to 100%, marks the task completed.

**Preconditions**:
- `p` and in-progress queue must be valid.

**Postconditions**:
- Task attributes are updated.

**Side Effects**:
- Task editing, input reading.

---

### `showTaskProgress`
```c
int showTaskProgress(Planner p);
```
**Semantic**: Calculates and displays progress and elapsed time for each task.

**Preconditions**:
- Planner and queue must be initialized.

**Postconditions**:
- Displays progress information.

**Side Effects**:
- Terminal output.

---

### `weeklyReport`
```c
int weeklyReport(Planner p);
```
**Semantic**: Attempts to locate and print a weekly report if available, then waits for user input.

**Preconditions**:
- `p` must be a valid Planner object.

**Postconditions**:
- Returns 1 if the report is shown, 0 otherwise.

**Side Effects**:
- Interacts with the terminal.
- May call other functions that perform file and terminal I/O.

---

### `deleteHistory`
```c
int deleteHistory(Planner p);
```
**Semantic**: Deletes all historical tasks from completed and expired lists.

**Preconditions**:
- Planner must be valid.

**Postconditions**:
- Lists are emptied.

**Side Effects**:
- Frees memory.

---

### `deleteTask`
```c
int deleteTask(Planner p);
```
**Semantic**: Removes a task from the in-progress queue by title.

**Preconditions**:
- Planner and in-progress queue must be valid.

**Postconditions**:
- Task is deallocated.

**Side Effects**:
- Memory release, user input.

---

```
Per compilare ed eseguire usare:

- clean : elimina tutti i file oggetto e l'eseguibile
- run : compila e genera l'eseguibile
- recompile : esegue clean e poi run

l' eseguibile è denominato: progetto.exe.
```
