1) This program is written to read the comma-separated list of floating-point values from a text file. The text file is expected to contain only the angle-value. At present distance (because 2D polar contains angle and distance) is ignored. It outputs the centroid.

2) I am using tensorflow and opencv

3) You need to make sure you have installed tensorflow and opencv and other python dependencies and g++ compiler

4) Make sure you activated tensorflow and you are inside the tensorflow

5) You should see the following files

(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$ pwd
/home/user/Nasa/TensorFlow/KMEANS
(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$ ls
design.txt Input  kmeans.cpp  kmeans.hpp  kmeans.py  main.cpp  Makefile  readme.txt  utils.cpp  utils.hpp
(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$

(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$ cat Input/input0.txt
70.9,71.9,72.3,73.2,73.9,77.2,77.2,79.4,79.8,82.3,83.3,85.8,87.3,152.3,169.6,170.7,176.3,176.9,177.2,179.4,180.1,181.2,181.9,182.0,182.6,185.5,188.5,338.1,338.7,339.8,340.0,340.2,344.1,344.2,344.8,347.3,348.5,350.4,351.3,351.8
(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$ cat Input/input1.txt
36.9,39.4,40.7,45.9,48.4,49.3,50.4,51.1,51.6,55.2,57.8,142.0,181.6,205.9,209.6,214.7,216.0,220.5,221.1,221.9,222.0,222.5,224.2,224.5,226.1,280.9,287.4,288.3,290.0,290.1,293.3,294.5,295.5,296.0,297.0,298.7
(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$ cat Input/input2.txt
0.2,1.2,3.1,3.2,4.1,5.9,51.8,56.1,56.5,57.8,59.3,59.5,60.9,61.1,61.6,61.7,62.9,63.0,65.1,66.9,68.0,142.4,169.2,182.0,183.4,185.4,186.5,189.2,189.4,189.8,190.2,192.9,193.4,194.3,198.2,266.1,278.6,279.9,281.1,285.2,285.4,285.4,285.5,285.6,287.1,290.5,350.3,353.5,359.5,359.8
(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$ cat Input/input3.txt
2.1,4.2,4.7,5.3,5.7,6.8,7.9,9.4,11.1,57.5,88.7,92.6,94.7,95.0,95.0,95.0,96.0,98.4,99.3,99.4,101.9,104.7,105.3,157.7,160.1,160.8,163.4,165.1,165.9,167.5,168.9,169.5,170.5,170.8,230.7,348.5,354.2,355.5,359.1
(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$ cat Input/input4.txt
23.7,112.5,113.3,114.1,115.4,116.7,118.3,118.6,119.7,120.7,122.4,123.0,175.3,179.9,183.8,185.4,188.9,188.9,190.1,191.0,192.4,192.8,192.9,193.2,194.2,196.8,243.2,243.7,248.9,250.2,250.4,251.5,252.8,253.6,253.8,254.1,254.5,257.1,260.5,312.9,317.0,318.5,318.7,321.1,322.7,323.4,325.4,326.1,326.2,326.3,326.3,327.4

6) How to compile the file?

(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$ make
g++ -c main.cpp
g++ -c utils.cpp
g++ -c kmeans.cpp
g++ -o kmeans_app main.o utils.o kmeans.o
(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$ ls
Input  kmeans_app  kmeans.cpp  kmeans.hpp  kmeans.o  kmeans.py  main.cpp  main.o  Makefile  readme.txt  utils.cpp  utils.hpp  utils.o
(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$

7) How to run the executable?

(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$ ./kmeans_app ./Input/input0.txt
[78.03846][344.55383][177.44286]
(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$ ./kmeans_app ./Input/input1.txt
[47.88182][291.97272][210.90001]
(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$ ./kmeans_app ./Input/input2.txt
[44.280956][184.73573][302.23334]
(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$ ./kmeans_app ./Input/input3.txt
[11.47][132.676][354.32498]
(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$ ./kmeans_app ./Input/input4.txt
[322.46155][109.86667][219.25555]

8) How to cleanup?

(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$ make clean
rm kmeans_app main.o utils.o kmeans.o output.txt
(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$
(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$ ls
design.txt Input  kmeans.cpp  kmeans.hpp  kmeans.py  main.cpp  Makefile  readme.txt  utils.cpp  utils.hpp
(tensorflow-dev) user@SAMJ-PC:~/Nasa/TensorFlow/KMEANS$

9) If you want to copy these files to your local computer, you need to do the following things

   a) create a brand new dir
   b) copy all the files
   c) most important thing is that you need to modify the function "bool Kmeans :: execute_kmeans_algorithm(std::string fname)" in
      kmeans.cpp module and change the line number 6 according to the new directory that you created

