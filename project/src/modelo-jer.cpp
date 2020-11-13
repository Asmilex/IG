#include "modelo-jer.h"
#include "malla-ind.h"
#include "malla-revol.h"

C::C() {
    agregar(new Motherboard());
}

Motherboard::Motherboard() {
    //Posicionar DIMM slots
    Matriz4f traslacion_slot1 = MAT_Traslacion(1, 0, -.1);
    Matriz4f escala_slot = MAT_Escalado(.8, .8, .8);

    agregar(traslacion_slot1);
    agregar(escala_slot);
    agregar( new DIMM_slot() );


    Matriz4f traslacion_slot2 = MAT_Traslacion(.2, 0, 0);
    agregar(traslacion_slot2);

    agregar( new DIMM_slot() );

    agregar( MAT_Inversa(traslacion_slot2));
    agregar( MAT_Inversa(escala_slot));
    agregar( MAT_Inversa(traslacion_slot1));

    // Posicionar disipador
    Matriz4f escala_cooler = MAT_Escalado(1.3, 1.3, 1.3);
    agregar(escala_cooler);
    agregar(new CPU_cooler());
    agregar(MAT_Inversa(escala_cooler));


    // Posicionar puerto PCIe
    Matriz4f traslacion_PCIe_port = MAT_Traslacion(0, 0, 1);
    agregar(traslacion_PCIe_port);
    agregar(new PCIE_port());
    agregar(MAT_Inversa(traslacion_PCIe_port));

    // Colocar base
    agregar( MAT_Traslacion(0, -0.01, 0) );
    agregar( MAT_Escalado(1.4, 0.01, 1.4) );
    agregar( new Cubo() );

    ponerColor( Hex_a_tupla(0x636060) );
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

DIMM_slot::DIMM_slot() {
    agregar( MAT_Escalado(0.03, 0.01, 1) );
    agregar( new Cubo() );

    Cubo * clip = new Cubo();
    clip->ponerColor(Hex_a_tupla(0x463D3E));

    agregar(MAT_Traslacion(0, 0.3, 1.02));
    agregar(MAT_Escalado(1, 5, 0.02));
    agregar( clip );

    agregar( MAT_Traslacion(0, 0, -102) );
    agregar(clip);

    ponerColor(Hex_a_tupla(0x1B1515));
}

// ────────────────────────────────────────────────────────────────────────────────

CPU_cooler::CPU_cooler() {
    agregar( new CPU_cooler_body() );

    agregar( MAT_Escalado(.12, .15, .12) );
    agregar( new CPU_cooler_fan_system() );
}


CPU_cooler_fan_system::CPU_cooler_fan_system() {
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
    ponerColor(Hex_a_tupla(0x181516));
}


CPU_cooler_blade::CPU_cooler_blade() {
    agregar( MAT_Traslacion(0, 1.6, 0));
    agregar( MAT_Escalado(1.7, 1.4, .02) );

    Cubo * blade = new Cubo();
    blade->ponerColor(Hex_a_tupla(0xE6E6E6));
    agregar( blade );
}
// ────────────────────────────────────────────────────────────────────────────────

PCIE_port::PCIE_port() {
    agregar(MAT_Rotacion(90, 0, 1, 0));
    agregar( MAT_Escalado(0.03, 0.01, 1) );
    agregar( new Cubo() );

    Cubo * clip = new Cubo();
    clip->ponerColor(Hex_a_tupla(0x463D3E));

    agregar(MAT_Traslacion(0, 0.3, 1.02));
    agregar(MAT_Escalado(1, 5, 0.02));
    agregar( clip );


    ponerColor(Hex_a_tupla(0x1B1515));

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
