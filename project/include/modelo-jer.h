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
    protected:
        Matriz4f * traslacion_RAM1 = nullptr;
        Matriz4f * traslacion_RAM2 = nullptr;
        Matriz4f * CPU_fan_rotator = nullptr;
        Matriz4f * mobo_rotator    = nullptr;
        void actualizarEstadoParametro (const unsigned iParam, const float t_sec);

    public:
        C ();
        unsigned int leerNumParametros () const;
        void fijar_trasl_RAM1 (const float h_nueva);
        void fijar_trasl_RAM2 (const float h_nueva);
        void fijar_CPU_fan_rot (const float alpha);
        void fijar_mobo_rot (const float alpha);
    };

//
// ─────────────────────────────────────────────────────────────── PLACA BASE ─────
//


    class Motherboard: public NodoGrafoEscena {
        public:
            Motherboard(Matriz4f * &traslacion_RAM1, Matriz4f * &traslacion_RAM2, Matriz4f * &CPU_fan_rotator);
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

    class RAM_animator: public NodoGrafoEscena {
        public:
            RAM_animator(Matriz4f * &traslacion_RAM1, Matriz4f * &traslacion_RAM2);
    };

    class RAM_pinout: public NodoGrafoEscena {
        public:
            RAM_pinout();
    };


    class DIMM_slot: public NodoGrafoEscena {
        public:
            DIMM_slot();
    };

//
// ─────────────────────────────────────────────────── CONJUNTO DEL DISIPADOR ─────
//


    class CPU_cooler: public NodoGrafoEscena {
        public:
            CPU_cooler (Matriz4f * &rotacion);
    };


    class CPU_cooler_fan_system: public NodoGrafoEscena {
        public:
            CPU_cooler_fan_system();
    };


    class CPU_cooler_blade: public NodoGrafoEscena {
        public:
            CPU_cooler_blade();
    };


    class CPU_cooler_stem: public NodoGrafoEscena {
        public:
            CPU_cooler_stem();
    };


//
// ──────────────────────────────────────────────────────────────────── OTROS ─────
//

    Tupla3f RGB_a_tupla(int R, int G, int B);

    Tupla3f Hex_a_tupla (int hexValue);


// ────────────────────────────────────────────────────────────────────────────────

    class Sistema_cilindros : public NodoGrafoEscena {
        float radio;
        public:
            Sistema_cilindros(float radio, int copias);
    };
    class Cilindro_alt: public NodoGrafoEscena {
        public:
            Cilindro_alt(int n = 10);
    };

    class Cilindro_escena: public NodoGrafoEscena {
        public:
            Cilindro_escena();
    };
#endif
