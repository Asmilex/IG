#include "malla-ind.h"
#include "malla-revol.h"
#include "matrices-tr.h"
#include "latapeones.h"
#include "auxiliares.h"

// ────────────────────────────────────────────────────────────────────────────────

Lata::Lata (const std::string & textura) {
    agregar(new Tapa_inferior_lata());
    agregar(new Tapa_superior_lata());
    agregar(new Cuerpo_lata(textura));

    ponerIdentificador(generar_ident_unico());
    ponerNombre("Lata");
}

Tapa_inferior_lata::Tapa_inferior_lata() {
    agregar( new Material(0.2, 0.5, 0.3, 20) );
    agregar( new MallaRevolPLY("../recursos/plys/lata-pinf.ply",50) );

    ponerIdentificador(-1);
    ponerNombre("Tapa inferior lata");

}

Tapa_superior_lata::Tapa_superior_lata() {
    agregar( new Material(0.2, 0.5, 0.3, 20) );
    agregar( new MallaRevolPLY("../recursos/plys/lata-psup.ply",50) );

    ponerIdentificador(-1);
    ponerNombre("Tapa superior lata");

}

Cuerpo_lata::Cuerpo_lata(const std::string & fichero) {
    Textura * texture = new Textura(fichero);

    agregar ( new Material(texture, 0.5, 0.2, 0.3, 22) );
    agregar( new MallaRevolPLY("../recursos/plys/lata-pcue.ply", 50));

    ponerIdentificador(-1);
    ponerNombre("Cuerpo de lata");
}


// ────────────────────────────────────────────────────────────────────────────────


Lata_Pepsi::Lata_Pepsi(){
    agregar(new Lata("../recursos/imgs/lata-pepsi.jpg"));

    ponerIdentificador(generar_ident_unico());
    ponerNombre("Lata de Pepsi");
}

Lata_Cocacola::Lata_Cocacola(){
    agregar(new Lata("../recursos/imgs/lata-coke.jpg"));

    ponerIdentificador(generar_ident_unico());
    ponerNombre("Lata de Coca-Cola");
}

Latazo_UGR::Latazo_UGR(){
    agregar(new Lata("../recursos/imgs/window-icon.jpg"));

    ponerIdentificador(generar_ident_unico());
    ponerNombre("Lata de la UGR");
}


// ────────────────────────────────────────────────────────────────────────────────


Peon_madera::Peon_madera() {
    Textura * tex = new Textura("../recursos/imgs/text-madera.jpg");

    agregar( MAT_Traslacion(0, 1.4, 0));
    agregar( new Material(tex, 0.3, 0.4, 0.4, 20) );
    agregar(new MallaRevolPLY("../recursos/plys/peon.ply",50));

    ponerIdentificador(generar_ident_unico());
    ponerNombre("Peon de Madera");
}


Peon_blanco::Peon_blanco() {
    ponerColor({1.0, 1.0, 1.0});

    agregar( MAT_Traslacion(0, 1.4, 0));
    agregar( new Material(0.1, 0.8, 0.1, 15 ) );
    agregar( new MallaRevolPLY("../recursos/plys/peon.ply", 50));

    ponerIdentificador(generar_ident_unico());
    ponerNombre("Peon blanco");
}


Peon_negro::Peon_negro() {
    ponerColor({0, 0, 0});

    agregar( MAT_Traslacion(0.0, 1.4, 0));
    agregar( new Material(0.1, 0.1, 0.8, 20) );
    agregar(new MallaRevolPLY("../recursos/plys/peon.ply",50));

    ponerIdentificador(generar_ident_unico());
    ponerNombre("Peon negro");
}


// ────────────────────────────────────────────────────────────────────────────────


Latas::Latas() {
    agregar( new Lata_Pepsi());

    agregar( MAT_Traslacion(2.3,0.0,0.0));
    agregar( new Lata_Cocacola());

    agregar( MAT_Traslacion(2.3,0.0,0.0));
    agregar( new Latazo_UGR());

    ponerIdentificador(0);
    ponerNombre("Latas");
}


Peones::Peones(){
    agregar(new Peon_madera());

    agregar(MAT_Traslacion(2.3, 0.0, 0.0));
    agregar(new Peon_blanco());

    agregar(MAT_Traslacion(2.3, 0.0, 0.0));
    agregar(new Peon_negro());

    ponerIdentificador(0);
    ponerNombre("Peones");
}


Varias_latas_peones::Varias_latas_peones() {
    agregar(new Latas());

    agregar(MAT_Traslacion(0.0,0,2.0));
    agregar(new Peones());

    ponerIdentificador(0);
    ponerNombre("Latas y Peones");
}
