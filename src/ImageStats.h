//
// Created by dayan3847 on 3/21/23.
//

#ifndef CASCADECLASSIFICATIONKMEANS_IMAGESTATS_H
#define CASCADECLASSIFICATIONKMEANS_IMAGESTATS_H


struct ImageStats {
    // vector promedio
    struct {
        float a = 0;
        float b = 0;
    } mean;
    // matrix de covarianza
    struct {
        float s1 = 0;
        float s2 = 0;
        float s3 = 0;
    } covariance;
};


#endif //CASCADECLASSIFICATIONKMEANS_IMAGESTATS_H
