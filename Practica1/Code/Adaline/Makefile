CC = gcc  -g -lm
CFLAGS = -Wall
EXE = mainAdaline adalineNoClasif

compile : $(EXE)
help : 
	@echo "Ejemplo de fichero (necesario que haya un único 1 en cada fila)\n1 0 0\n0 1 0\n0 0 1\n1 0 0"
	   
.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o perceptron.o adaline.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o perceptron.o adaline.o

%.o : %.c perceptron.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

test_1:
	@echo Ejecutando main
    #@./main -limInf 1 -limSup 5 -numN 10

