#include "modelo-jer.h"
#include "malla-ind.h"
#include "malla-revol.h"

C::C() {
    //agregar( new RAM() );
    agregar( new CPU_cooler() );
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

// ────────────────────────────────────────────────────────────────────────────────

CPU_cooler::CPU_cooler() {
    agregar( new CPU_cooler_body() );

    agregar (MAT_Escalado(.12, .15, .12));
    agregar( new CPU_cooler_stem() );

    agregar( MAT_Traslacion(1.2, 0, 0.9) );
    agregar( MAT_Rotacion(-35, 1, 0, 0) );

    agregar( new CPU_cooler_blade() );

    agregar( MAT_Traslacion(-2.4, 1, -1.5) );
    agregar( MAT_Rotacion(70, 1, 0, 0) );

    agregar( new CPU_cooler_blade() );

    agregar( MAT_Inversa(MAT_Rotacion(70, 1, 0, 0)) );
    agregar( MAT_Inversa(MAT_Rotacion(-35, 1, 0, 0)) );
    agregar( MAT_Rotacion(90, 0, 1, 0) );
    agregar( MAT_Rotacion(-35, 1, 0, 0) );
    agregar( MAT_Traslacion(0.5, -1, 1.8) );

    agregar( new CPU_cooler_blade() );

    agregar( MAT_Traslacion(-2.5, 1, -1.5) );
    agregar( MAT_Inversa(MAT_Rotacion(-35, 1, 0, 0)) );
    //agregar( MAT_Inversa(MAT_Rotacion(90, 0, 1, 0)) );

    agregar( MAT_Rotacion(35, 1, 0, 0) );

    agregar( new CPU_cooler_blade() );
}


CPU_cooler_stem::CPU_cooler_stem() {
    agregar (new Cilindro(30, 30));
    ponerColor(Hex_a_tupla(0x5D5D5D));
}


CPU_cooler_blade::CPU_cooler_blade() {
    agregar( MAT_Traslacion(0, 1.6, 0));
    agregar( MAT_Escalado(1.7, 1.4, .02) );

    agregar( new Cubo() );
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
