#!/bin/bash
eval "make"
eval "make clean"
eval "./MyProg"
eval "gnuplot plot_x.plot plot_y.plot plot_z.plot plot_xyz.plot plot_x_y.plot"
exit 0
