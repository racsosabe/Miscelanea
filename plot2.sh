#!/usr/bin/env gnuplot
#set size (221.0/72.27)/5.0, (221.0/72.27)/3.0
#plot "zeta3" with points pointtype 6 pointsize 0.5
#!/usr/bin/env gnuplot
#set size (221.0/72.27)/5.0, (221.0/72.27)/3.0
#plot "zeta3" with points pointtype 6 pointsize 0.5

set terminal postscript eps color
set title "Problema 2"
set xlabel "x"
set ylabel "y"
set zlabel "u(x,y)"
set dgrid3d
set output "p2.eps"
splot "in2" u 1:2:3 with lines
