set terminal pngcairo enhanced font 'Verdana,12'

set output 'ex_1_time_vs_samples.png'
set title 'Time Taken vs Number of Samples'
set xlabel 'Number of Samples'
set ylabel 'Time Taken (seconds)'
plot 'data1.dat' using 1:2 with linespoints title 'Time Taken'

set output 'ex_1_error_vs_samples.png'
set title 'Error in Estimation of π vs Number of Samples'
set xlabel 'Number of Samples'
set ylabel 'Error'
plot 'data1.dat' using 1:3 with linespoints title 'Error'