#include <math.h>

double dMahalanobisN (double a, double b, double am, double bm, double s1,
                      double s2, double s3)
{
   /*
      (a,b) vector a calcular su distancia.
      (am, bm) Vector promedio de la clase;
      [s1,s3
      s3,s2] Matriz de covarianza de la clase.
    */
   double det, idet, da, db, D;

   det = s1 * s2 - s3 * s3;
   idet = 1 / det;
   da = a - bm;
   db = b - bm;
   D = log (det) + idet * (da * (da * s2 - db * s3) +
                           db * (db * s1 - da * s3));
   return D;
}
