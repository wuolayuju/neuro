
#incrementos Neuronas

inicio=1
final=8
incr=1


for i in $(seq $inicio $incr $final)
do
	./backpropagationapp -inputLearn problema-real-3clases.txt -numNeurons $i -part 0.3 -learnrate 0.1 -tolerance 0.05 -outputDebug outputs/neuron_p3$i.out>  outputs/hits_neuron_p3$i.out
done


#incrementos Tasa aprendizaje

inicio=0.1
final=1
incr=0.1
for i in $(seq $inicio $incr $final)
do
	./backpropagationapp -inputLearn problema-real-3clases.txt -numNeurons 2 -part 0.3 -learnrate $i -outputDebug outputs/learn_p3$i.out > outputs/hits_learn_p3$i.out

done