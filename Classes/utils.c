//
//  utils.c
//  Grow1
//
//  Created by Mikel on 09/06/13.
//
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>



float rand_u() {
    float r=rand()*1.0/RAND_MAX;
    return r;
}

float rand_range(float a, float b) {
    float r=a+rand_u()*(b-a);
    return r;
}

float rand_exp(float lambda) {
    float r=-logf(rand_u())/lambda;
    return r;
}

float rand_exp_limited(float lambda,float max) {
    float r=-logf(rand_u())/lambda;
    r=r>max?max:r;
    return r;
}



