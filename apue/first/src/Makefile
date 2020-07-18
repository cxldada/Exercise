headdir = ../include
headfile = $(headdir)/error.c $(headdir)/path_alloc.c $(headdir)/wait.c $(headdir)/pr_mask.c \
			$(headdir)/lock_reg.c $(headdir)/set_fl.c $(headdir)/rdn.c $(headdir)/fd_pipe.c
objfile = $(headdir)/error.o $(headdir)/path_alloc.o $(headdir)/wait.o $(headdir)/pr_mask.o \
			$(headdir)/lock_reg.o $(headdir)/set_fl.o $(headdir)/rdn.o $(headdir)/fd_pipe.o
srcfile = $(SR)

outfile : $(objfile) $(srcfile)
	gcc -o outfile -g $(srcfile) $(objfile)

creatObj : $(headfile)
	gcc -c $(headfile)

clear : 
	rm -rf $(objfile) outfile
