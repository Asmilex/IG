#ifndef LATAPEONES_H
#define LATAPEONES_H

#include "objeto3d.h"
#include "grafo-escena.h"

//
// ──────────────────────────────────────────────────────────────────── LATAS ─────
//


class Lata: public NodoGrafoEscena {
    public:
        Lata (const std::string & textura);
};

    class Tapa_inferior_lata : public NodoGrafoEscena{
        public:
            Tapa_inferior_lata();
    };

    class Tapa_superior_lata : public NodoGrafoEscena{
        public:
            Tapa_superior_lata();
    };

    class Cuerpo_lata : public NodoGrafoEscena{
        public:
            Cuerpo_lata(const std::string & fichero);
    };

// ────────────────────────────────────────────────────────────────────────────────

class Lata_Pepsi : public NodoGrafoEscena{
    public:
        Lata_Pepsi();
};

class Lata_Cocacola : public NodoGrafoEscena{
    public:
        Lata_Cocacola();
};

class Latazo_UGR : public NodoGrafoEscena{
    public:
        Latazo_UGR();
};

//
// ─────────────────────────────────────────────────────────────────── PEONES ─────
//

class Peon_madera : public NodoGrafoEscena{
    public:
        Peon_madera();
};

class Peon_blanco : public NodoGrafoEscena{
    public:
        Peon_blanco();
};

class Peon_negro : public NodoGrafoEscena{
    public:
        Peon_negro();
};


//
// ──────────────────────────────────────────────────────────────────── OTROS ─────
//


class Varias_latas_peones : public NodoGrafoEscena{
    public:
        Varias_latas_peones();
};


class Peones : public NodoGrafoEscena{
    public:
        Peones();
};


class Latas : public NodoGrafoEscena{
    public:
        Latas();
};


#endif