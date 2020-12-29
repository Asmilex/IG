#ifndef AUXILIARES_H
#define AUXILIARES_H


int generar_ident_unico () {
    static int identificador = -1;

    return ++identificador;
}


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
#endif