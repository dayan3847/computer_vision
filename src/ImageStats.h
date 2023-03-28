//
// Created by dayan3847 on 3/21/23.
//

#ifndef CASCADECLASSIFICATIONKMEANS_IMAGESTATS_H
#define CASCADECLASSIFICATIONKMEANS_IMAGESTATS_H


struct ImageStats {
    // vector promedio
    struct {
        float l = 0;
        float a = 0;
        float b = 0;
    } mean;
    // matrix de covarianza
    struct {
        float s1 = 1;
        float s2 = 1;
        float s3 = 0;
    } covariance;
    // cantidad de pixeles
    int count = 0;
    // label
    int label = 0;
};


#endif //CASCADECLASSIFICATIONKMEANS_IMAGESTATS_H
