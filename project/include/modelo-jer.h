/**
 * Notas del 05/11/20:
 * Las definiciones no son definitivas. Estoy pensando todavía las partes del conjunto
 * Además, estoy bastante perdido. No entiendo bien cómo se deben poner los parámetros
 * Así que mejor no implementar nada hasta repensarlo todo
 */

#ifndef MODELO_JER_H
#define MODELO_JER_H

#include "grafo-escena.h"

//
// ─────────────────────────────────────────────────────────────────── ESCENA ─────
//

    class C: public NodoGrafoEscena {
    private:

    public:
            C ();
            void leerNumParametros ();
            void actualizarEstadoParametro ();
    };

//
// ─────────────────────────────────────────────────────────────── PLACA BASE ─────
//


    class Motherboard: public NodoGrafoEscena {
        public:
            Motherboard();
    };

    class IO_shield: public NodoGrafoEscena {
        public:
            IO_shield();
    };

    class PCIE_port: public NodoGrafoEscena {
        public:
            PCIE_port();
    };

//
// ─────────────────────────────────────────────────────── CONJUNTO DE LA RAM ─────
//


    class RAM: public NodoGrafoEscena {
        public:
            RAM();
    };

    class RAM_pinout: public NodoGrafoEscena {
        public:
            RAM_pinout();
    };

    // ────────────────────────────────────────────────────────────────────────────────

    class DIMM_slots: public NodoGrafoEscena {
        public:
            DIMM_slots();
    };

//
// ─────────────────────────────────────────────────── CONJUNTO DEL DISIPADOR ─────
//


    class CPU_cooler: public NodoGrafoEscena {
        public:
            CPU_cooler();
    };

    // ────────────────────────────────────────────────────────────────────────────────

    class CPU_cooler_body: public NodoGrafoEscena {
        public:
            CPU_cooler_body();
    };

    // ────────────────────────────────────────────────────────────────────────────────

    class CPU_cooler_blade: public NodoGrafoEscena {
        public:
            CPU_cooler_blade();
    };

    // ────────────────────────────────────────────────────────────────────────────────

    class CPU_cooler_stem: public NodoGrafoEscena {
        public:
            CPU_cooler_stem();
    };

    // ────────────────────────────────────────────────────────────────────────────────

//
// ──────────────────────────────────────────────────────────────────── OTROS ─────
//

    Tupla3f RGB_a_tupla(int R, int G, int B);

    Tupla3f Hex_a_tupla (int hexValue);

#endif
