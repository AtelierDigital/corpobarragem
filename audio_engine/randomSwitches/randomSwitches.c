/* Copyright (c) 1997-1999 Miller Puckette.
* For information on usage and redistribution, and for a DISCLAIMER OF ALL
* WARRANTIES, see the file, "LICENSE.txt," in this distribution.  */

/* connective objects */

#include "m_pd.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static t_class *randomSwitches_class;

//  NOTE: if I used u_outlet* directly, instead of this struct, I couldn't malloc. Maybe there's an elegant way...
typedef struct triggeroutlet
{
    t_outlet *u_outlet;
} t_triggeroutlet;

typedef struct _trigger
{
    t_object x_obj;
    t_triggeroutlet *x_vec;

    int i_maxOuts;
} t_randomSwitches;

void init(t_randomSwitches *x, t_floatarg maxOuts)
{
    x->i_maxOuts = (int)maxOuts;

    t_triggeroutlet *u;

    x->x_vec = (t_triggeroutlet *)getbytes(x->i_maxOuts * sizeof(*x->x_vec));

    int i;
    for (i = 0, u = x->x_vec; i < x->i_maxOuts; u++, i++)
    {
        u->u_outlet = outlet_new(&x->x_obj, &s_float);
    }
}

void *randomSwitches_new(t_floatarg maxOuts)
{
    t_randomSwitches *x = (t_randomSwitches *)pd_new(randomSwitches_class);

    init(x, maxOuts);

    return (x);
}

void randomSwitches_bang(t_randomSwitches *x)
{
    time_t t;
    srand((unsigned) time(&t)); // Intializes random number generator

    //  Calculating how many outlets will output a 1.
    //  We want this to be normally distributed, i.e., we want the amount of outlets to output
    //a 1 to be most of the time the amount x->i_maxOuts/2 

    //  We sum i_maxOuts random numbers between [0,i_maxOuts-1], and divide this sum by i_maxOuts
    t_float n_outONs_f = 0;
    for(int i=0; i<x->i_maxOuts; i++) {
        n_outONs_f += rand() % x->i_maxOuts;
    }
    n_outONs_f += 1.;
    n_outONs_f /= x->i_maxOuts;
    if(n_outONs_f == x->i_maxOuts) {
        n_outONs_f--;
    }
    int n_outONs = (int)n_outONs_f + 1;

    //  Now we build a list correspondending to the i_maxOuts outlets, and initialize with 0's.
    //We fill it with 1's in random positions until we have n_outONs elements with 1.
    //  We'll use it to define which outlets will output a 1
    t_int *outlets_states = (t_int *) malloc(sizeof(t_int)*x->i_maxOuts);
    memset(outlets_states, 0, sizeof(t_int)*x->i_maxOuts);
    int outlet = -1;
    int outs_set = 0;
    while(outs_set < n_outONs) {
        outlet = rand() % x->i_maxOuts;
        if(outlets_states[outlet] == 0){
            outlets_states[outlet] = 1;
            outs_set++;
        }
    }

    t_triggeroutlet *u = x->x_vec;

    int count = 0;
    for(int i=0; i<x->i_maxOuts; i++) {
        outlet_float(u->u_outlet, outlets_states[i]);
        u++;
    }


    free(outlets_states);
}

void randomSwitches_float(t_randomSwitches *x, t_float f)
{
    init(x, f);
}

void randomSwitches_free(t_randomSwitches *x)
{
    freebytes(x->x_vec, x->i_maxOuts * sizeof(*x->x_vec));
}

void randomSwitches_setup(void)
{
    randomSwitches_class = class_new(gensym("randomSwitches"), (t_newmethod)randomSwitches_new,
        (t_method)randomSwitches_free, sizeof(t_randomSwitches), CLASS_DEFAULT, A_DEFFLOAT, 0);
    class_addbang(randomSwitches_class, randomSwitches_bang);
    class_addfloat(randomSwitches_class, randomSwitches_float);
}
