CC = gcc  -g -lm
CFLAGS = -Wall
EXE = perceptronapp

help :
	@echo "---------------------------"
	@echo "USO : make <comando>"
	@echo "\nCOMANDOS\n"
	@echo "\thelp : Muestra esta ayuda."
	@echo "\tcompile : Compila y enlaza el programa 'perceptronapp'."
	@echo "\ttest_AND : Ejecuta el programa de prueba de la función lógica AND."
	@echo "\ttest_NAND : Ejecuta el programa de prueba de la función lógica NAND."
	@echo "\ttest_NOR : Ejecuta el programa de prueba de la función lógica NOR."
	@echo "\ttest_XOR : Ejecuta el programa de prueba de la función lógica XOR."
	@echo "\ttest_XOR_exp : Ejecuta el programa de prueba de la función lógica XOR con atributos expandidos."
	@echo "\ttest_problema_real_1 : Ejecuta el programa de prueba del problema real 1."
	@echo "\ttest_problema_real_2 : Ejecuta el programa de prueba del problema real 2, creando el fichero 'predicciones_perceptron.txt' con las predicciones."
	@echo "\tclean : Borra los ficheros objeto y los ejecutables generados."
	@echo "\nPROGRAMA\n"
	@echo "\tUSO: ./perceptronapp ENTRADA/SALIDA [PARAMETROS]"
	@echo "\nENTRADA/SALIDA"
	@echo "\t-inputLearn FICHERO"
	@echo "\t\tFichero que se usará para el aprendizaje supervisado de la red."
	@echo "\t-output FICHERO"
	@echo "\t\tFichero donde se escribirán los resultados de clasificación en la parte de test."
	@echo "\t[-inputExploit FICHERO]"
	@echo "\t\tFichero de patrones no clasificados para la fase de explotación."
	@echo "\nPARÁMETROS"
	@echo "\t[-part NUM]"
	@echo "\t\tPorcentaje del fichero de entrada que se usará para aprendizaje. Comprendido entre [0,1]"
	@echo "\t[-learnrate NUM]"
	@echo "\t\tTasa de aprendizaje de la red. Debe ser mayor que 0."
	@echo "\t[-threshold NUM]"
	@echo "\t\tValor umbral de cada unidad de la red. Debe ser mayor que 0."
	@echo "\nFICHEROS DE PRUEBA\n"
	@echo "\tand.txt : Contiene 10 patrones correspondientes a la puerta lógica AND."
	@echo "\tnand.txt : Contiene 4 patrones correspondientes a la puerta lógica NAND."
	@echo "\tnor.txt : Contiene 4 patrones correspondientes a la puerta lógica NOR."
	@echo "\txor.txt : Contiene 4 patrones correspondientes a la puerta lógica XOR."
	@echo "\txor.txt : Contiene 4 patrones correspondientes a la puerta lógica XOR con atributos expandidos."
	@echo "\tproblema_real1.txt : Patrones clasificados correspondientes al problema real 1."
	@echo "\tproblema_real2.txt : Patrones clasificados correspondientes al problema real 2."
	@echo "\tproblema_real2_no_etiquetados.txt : Patrones no clasificados correspondientes al problema real 2."
	@echo "---------------------------"	

compile : $(EXE)
	   
.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o perceptron.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o perceptron.o

%.o : %.c perceptron.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

test_AND:
	@echo "Ejecutando AND"
	@./perceptronapp -inputLearn and.txt -output and.out -part 1 -learnrate 0.1 -threshold 0

test_NAND:
	@echo "Ejecutando NAND"
	@./perceptronapp -inputLearn nand.txt -output and.out -part 1 -learnrate 0.1 -threshold 0

test_NOR:
	@echo "Ejecutando NOR"
	@./perceptronapp -inputLearn nor.txt -output and.out -part 1 -learnrate 0.1 -threshold 0

test_XOR:
	@echo "Ejecutando XOR"
	@./perceptronapp -inputLearn xor.txt -output and.out -part 1 -learnrate 0.1 -threshold 0

test_XOR_exp:
	@echo "Ejecutando XOR_exp"
	@./perceptronapp -inputLearn expand_xor.txt -output and.out -part 1 -learnrate 0.1 -threshold 0

test_problema_real_1:
	@echo "Ejecutando problema_real1"
	@./perceptronapp -inputLearn problema_real1.txt -output out.out -part 0.3 -learnrate 0.1 -threshold 0

test_problema_real_2:
	@echo "Ejecutando problema_real_2"
	@./perceptronapp -inputLearn problema_real2.txt -output predicciones_perceptron.txt -inputExploit problema_real2_no_etiquetados.txt -part 0.3 -learnrate 0.1 -threshold 0