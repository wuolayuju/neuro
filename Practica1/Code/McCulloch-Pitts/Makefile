CC = gcc  -g -lm
CFLAGS = -Wall
EXE = scales

help : 
	@echo "---------------------------"
	@echo "USO : make <comando>"
	@echo "\nCOMANDOS\n"
	@echo "\thelp : Muestra esta ayuda."
	@echo "\tcompile : Compila y enlaza el programa 'scales'."
	@echo "\tclean : Borra los ficheros objeto y los ejecutables generados."
	@echo "\nPROGRAMA\n"
	@echo "\tUSO: ./scales -input <f_entrada> -output <f_salida>"
	@echo "\nFICHEROS DE PRUEBA\n"
	@echo "\tarriba_abajo.in : Contiene dos secuencias de estímulos que cumplen la clase arriba_abajo."
	@echo "\tabajo_arriba.in : Contiene dos secuencias de estímulos que cumplen la clase abajo_arriba."
	@echo "\tmixto.in : Contiene una serie de estímulos mezclados entre los dos patrones descritos, así como de patrones estáticos."
	@echo "---------------------------"

compile : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o mccullochPitts.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o mccullochPitts.o

%.o : %.c mccullochPitts.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

