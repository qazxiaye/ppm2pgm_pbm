This tool supports converting a batch of ASCII ppm images (RAW ppm not supported) to pgm and pbm ones.

Generated image will be found in the same folder as its original ppm image, generated file's extension will be changed to ".pgm" or ".pbm". 

Threshold used to convert to pbm and weights of red, green and blue colors used to convert to pgm can be found in the head of main.c file as global variables.

<br>
Usage :

 - cd build
 - cmake ../src
 - make
 - ./2pgm {list of ppm files}
 - ./2pbm {list of ppm files}

<br>
 - original ppm image

 ![](build/NetTopology.ppm)

 - generated pgm image

 ![](build/NetTopology.pgm)

 - generated pbm image

 ![](build/NetTopology.pbm)

 license: Apache License 2.0

