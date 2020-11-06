#include "modelo-jer.h"
#include "malla-ind.h"

C::C() {
    agregar( new RAM() );
}

// ────────────────────────────────────────────────────────────────────────────────

RAM::RAM() {
    // Cuerpo
    const float cte = 0.01;
    agregar( MAT_Escalado(cte * 29.5, cte * 11.2, cte * 0.75) );
    agregar( new Cubo() );


    // Pines
    agregar( MAT_Traslacion(0, -1.05, 0));
    agregar( new RAM_pinout() );

    ponerColor(Hex_a_tupla(0x2C2E31));
}

RAM_pinout::RAM_pinout() {
    const float cte = 0.065;

    agregar (MAT_Traslacion(0, 0, 0));
    agregar( MAT_Escalado(cte * 15.0, cte * 0.8, cte * 3));
    agregar( new Cubo() );

    ponerColor(Hex_a_tupla(0x040609));

    //agregar( MAT_Traslacion(2, 0, 0));
    //agregar( MAT_Escalado(cte * 12.6, cte * 0.5, cte * 0.3));
    //agregar( new Cubo());
}

//
// ──────────────────────────────────────────────────────────────────── OTROS ─────
//

Tupla3f RGB_a_tupla(int R, int G, int B) {
    Tupla3f colores (R/255, G/255, B/255);
    return colores;
}

Tupla3f Hex_a_tupla (int hexValue) {
    Tupla3f rgbColor;

    rgbColor(R) = ((hexValue >> 16) & 0xFF) / 255.0;  // Extract the RR byte
    rgbColor(G) = ((hexValue >> 8) & 0xFF) / 255.0;   // Extract the GG byte
    rgbColor(B) = ((hexValue) & 0xFF) / 255.0;        // Extract the BB byte

    return rgbColor;
}
