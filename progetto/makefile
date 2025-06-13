OBJS = objectFiles/main.o objectFiles/list.o objectFiles/planner.o objectFiles/pQueue.o objectFiles/task.o objectFiles/char.o
OBJS_test = objectFiles/test.o objectFiles/list.o objectFiles/planner.o objectFiles/pQueue.o objectFiles/task.o objectFiles/char.o
path=\"Data\"
# Regola principale: compila l'intero progetto

run: $(OBJS)
	gcc $(OBJS) -o progetto.exe

link_test:$(OBJS_test)
	gcc $(OBJS_test) -o test_progetto.exe

# Regola per creare la cartella objectFiles se non esiste
objectFiles:
	if not exist objectFiles mkdir objectFiles

# Ogni file .o dipende dalla cartella objectFiles (pattern "order-only dependency")
objectFiles/test.o: 
	gcc -DDEFAULT_TXT_FOLDER=\"test\" -c test.c -o objectFiles/test.o

objectFiles/main.o:
	gcc -c main.c -o objectFiles/main.o

objectFiles/list.o:
	gcc -c list/list.c -o objectFiles/list.o

objectFiles/planner.o:
	gcc -DDEFAULT_TXT_FOLDER=$(path) -c planner/planner.c -o objectFiles/planner.o

objectFiles/pQueue.o:
	gcc -c pQueue/pQueue.c -o objectFiles/pQueue.o

objectFiles/task.o:
	gcc -c task/task.c -o objectFiles/task.o

objectFiles/char.o:
	gcc -c char/char.c -o objectFiles/char.o

# La regola clean utilizza il backslash per riferirsi alla cartella
clean:
	del objectFiles\*.o *.exe

# La regola recompile per pulire e ricompilare
recompile: objectFiles clean | run

recompile_test: path =\"test\"
recompile_test: objectFiles clean | link_test
