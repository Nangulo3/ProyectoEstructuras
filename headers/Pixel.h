#ifndef PIXEL_H
#define PIXEL_H
#include <stdexcept>

class Pixel {
private:
    int intensidad ;
    int maxIntensidad;  

public:
    Pixel(int intensidad, int maxIntensidad);
    Pixel(int intensidad);


    int getIntensidad() const;  
    int getMaxIntensidad() const; 


    void setIntensidad(int nuevaIntensidad);
    void setMaxIntensidad(int nuevaIntensidad);
};

#endif // PIXEL_H

