#!/bin/bash
eval "make"
eval "make clean"
eval "./MyProg"
eval "python3 plot_r.py"
eval "python3 plot_I.py"
eval "gnuplot plot_x.plot plot_xyz.plot"
exit 0
