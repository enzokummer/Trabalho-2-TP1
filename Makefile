all:
	g++ main_teste.cpp dominios.cpp comandos.cpp controladoras.cpp "./includes/sqlite3.o" -o teste
	./teste