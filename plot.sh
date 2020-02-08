#!/usr/bin/env gnuplot
#set size (221.0/72.27)/5.0, (221.0/72.27)/3.0
#plot "zeta3" with points pointtype 6 pointsize 0.5
#!/usr/bin/env gnuplot
#set size (221.0/72.27)/5.0, (221.0/72.27)/3.0
#plot "zeta3" with points pointtype 6 pointsize 0.5

set terminal postscript eps color
set title "Problema 1"
set xlabel "x"
set ylabel "u(x)"
set grid
set output "p1.eps"
plot "in1" title ""
