
#incrementos Neuronas

inicio=1
final=8
incr=1


for i in $(seq $inicio $incr $final)
do
	./backpropagationapp -inputLearn nand.txt -numNeurons $i -part 1 -learnrate 0.1 -tolerance 0.05 > outputs/neuron_nand$i.out
	./backpropagationapp -inputLearn nor.txt -numNeurons $i -part 1 -learnrate 0.1 -tolerance 0.05 > outputs/neuron_nor$i.out
	./backpropagationapp -inputLearn xor.txt -numNeurons $i -part 1 -learnrate 0.1 -tolerance 0.05 > outputs/neuron_xor$i.out

done


#incrementos Tasa aprendizaje

inicio=0.1
final=0.5
incr=0.1
for i in $(seq $inicio $incr $final)
do
	./backpropagationapp -inputLearn nand.txt -numNeurons 2 -part 1 -learnrate $i -tolerance 0.05 > outputs/learn_nand$i.out
	./backpropagationapp -inputLearn nor.txt -numNeurons 2 -part 1 -learnrate $i -tolerance 0.05 > outputs/learn_nor$i.out
	./backpropagationapp -inputLearn xor.txt -numNeurons 2 -part 1 -learnrate $i -tolerance 0.05 > outputs/learn_xor$i.out

done