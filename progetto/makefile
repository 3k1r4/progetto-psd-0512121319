OBJS = objectFiles/main.o objectFiles/list.o objectFiles/planner.o objectFiles/pQueue.o objectFiles/task.o objectFiles/char.o

# Regola principale: compila l'intero progetto
run: $(OBJS)
	gcc $(OBJS) -o progetto.exe

# Regola per creare la cartella objectFiles se non esiste
objectFiles:
	if not exist objectFiles mkdir objectFiles

# Ogni file .o dipende dalla cartella objectFiles (pattern "order-only dependency")
objectFiles/main.o: main.c | objectFiles
	gcc -c main.c -o objectFiles/main.o

objectFiles/list.o: list/list.c | objectFiles
	gcc -c list/list.c -o objectFiles/list.o

objectFiles/planner.o: planner/planner.c | objectFiles
	gcc -c planner/planner.c -o objectFiles/planner.o

objectFiles/pQueue.o: pQueue/pQueue.c | objectFiles
	gcc -c pQueue/pQueue.c -o objectFiles/pQueue.o

objectFiles/task.o: task/task.c | objectFiles
	gcc -c task/task.c -o objectFiles/task.o

objectFiles/char.o: char/char.c | objectFiles
	gcc -c char/char.c -o objectFiles/char.o

# La regola clean utilizza il backslash per riferirsi alla cartella
clean:
	-del objectFiles\*.o progetto.exe

# La regola recompile per pulire e ricompilare
recompile: clean run