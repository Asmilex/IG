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

    };

    class IO_shield: public NodoGrafoEscena {

    };

    class PCIE_port: public NodoGrafoEscena {

    };

//
// ─────────────────────────────────────────────────────── CONJUNTO DE LA RAM ─────
//


    class RAM: public NodoGrafoEscena {

    };

    // ────────────────────────────────────────────────────────────────────────────────

    class DIMM_slots: public NodoGrafoEscena {

    };

//
// ─────────────────────────────────────────────────── CONJUNTO DEL DISIPADOR ─────
//


    class CPU_cooler: public NodoGrafoEscena {

    };

    // ────────────────────────────────────────────────────────────────────────────────

    class CPU_cooler_body: public NodoGrafoEscena {

    };

    // ────────────────────────────────────────────────────────────────────────────────

    class CPU_cooler_blade: public NodoGrafoEscena {

    };

    // ────────────────────────────────────────────────────────────────────────────────

    class CPU_cooler_stem: public NodoGrafoEscena {

    };

    // ────────────────────────────────────────────────────────────────────────────────
