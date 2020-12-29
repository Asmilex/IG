#include "modelo-jer.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include "auxiliares.h"

C::C() {
    agregar(MAT_Rotacion(40, 1, 0, 0));

    unsigned ind_rot_mobo = agregar (MAT_Rotacion(0, 0, 1, 0));
    agregar(new Motherboard(traslacion_RAM1, traslacion_RAM2, CPU_fan_rotator));
    mobo_rotator = leerPtrMatriz(ind_rot_mobo);
}

unsigned int C::leerNumParametros() const {
    return 4;
}

void C::fijar_trasl_RAM1 (const float h_nueva) {
    *traslacion_RAM1 = MAT_Traslacion(0, h_nueva, 0);
}

void C::fijar_trasl_RAM2 (const float h_nueva) {
    *traslacion_RAM2 = MAT_Traslacion(0, h_nueva, 0);
}

void C::fijar_CPU_fan_rot (const float alpha) {
    *CPU_fan_rotator = MAT_Rotacion(alpha, 0, 1, 0);
}

void C::fijar_mobo_rot (const float alpha) {
    *mobo_rotator = MAT_Rotacion(alpha, 0, 1, 0);
}

void C::actualizarEstadoParametro (const unsigned iParam, const float t_sec) {
    assert (iParam < leerNumParametros());

    switch (iParam) {
        case 0:
            fijar_trasl_RAM1 (-(cos(M_PI * t_sec) - 1) / 2 + 0.4);
            break;
        case 1:
            fijar_trasl_RAM2 ((cos(M_PI * t_sec) - 0.5) / 2 + 0.4 + 0.5 * sin(3*t_sec) + 0.85);
            break;
        case 2:
            fijar_CPU_fan_rot (500 * t_sec);
            break;
        case 3:
            fijar_mobo_rot (5 * t_sec);
            break;

    }
}

// ────────────────────────────────────────────────────────────────────────────────

Motherboard::Motherboard(Matriz4f * &traslacion_RAM1, Matriz4f * &traslacion_RAM2, Matriz4f * &CPU_fan_rotator) {
//
// ─── RAM Y SLOTS ────────────────────────────────────────────────────────────────
//

    Matriz4f traslacion_slot1 = MAT_Traslacion(1, 0, -.1);
    Matriz4f escala_slot      = MAT_Escalado(.8, .8, .8);

    agregar(traslacion_slot1 * escala_slot);

    agregar( new DIMM_slot() );

    agregar( new RAM_animator(traslacion_RAM1, traslacion_RAM2) );

    Matriz4f traslacion_slot2 = MAT_Traslacion(.2, 0, 0);
    agregar(traslacion_slot2);

    agregar( new DIMM_slot() );


    // Deshacer este posicionamiento para mayor comodidad
    agregar(  MAT_Inversa(traslacion_slot2)
            * MAT_Inversa(escala_slot)
            * MAT_Inversa(traslacion_slot1)
    );

//
// ─── DISIPADOR ──────────────────────────────────────────────────────────────────
//


    Matriz4f escala_cooler = MAT_Escalado(1.3, 1.3, 1.3);
    agregar(escala_cooler);

    agregar(new CPU_cooler(CPU_fan_rotator));

    agregar(MAT_Inversa(escala_cooler));


//
// ─── RESTO ──────────────────────────────────────────────────────────────────────
//


    Matriz4f traslacion_PCIe_port = MAT_Traslacion(0, 0, 1);
    agregar(traslacion_PCIe_port);

    agregar(new PCIE_port());

    agregar (   MAT_Inversa(traslacion_PCIe_port)
              * MAT_Traslacion(0, -0.01, 0)
              * MAT_Escalado(1.4, 0.01, 1.4)
    );

    agregar( new Cubo() );

    // Guardar matrices de movimiento
    ponerColor( Hex_a_tupla(0x636060) );
}

// ────────────────────────────────────────────────────────────────────────────────

RAM::RAM() {
    // Cuerpo
    agregar (MAT_Rotacion(90, 0, 1, 0));

    const float cte = 0.034;
    agregar( MAT_Escalado(cte * 29.5, cte * 11.2, cte * 0.75) );
    agregar( new Cubo() );

    // Pines
    agregar( MAT_Traslacion(0, -1.05, 0));
    agregar( new RAM_pinout() );

    ponerColor(Hex_a_tupla(0x2C2E31));

    ponerIdentificador(generar_ident_unico());
    ponerNombre("Motherboard");


}

RAM_pinout::RAM_pinout() {
    const float cte = 0.065;

    agregar( MAT_Escalado(cte * 15.0, cte * 0.8, cte * 3));
    agregar( new Cubo() );

    ponerColor(Hex_a_tupla(0x040609));

    ponerIdentificador(generar_ident_unico());
    ponerNombre("RAM pinout");


}

DIMM_slot::DIMM_slot() {
    agregar( MAT_Escalado(0.03, 0.01, 1) );
    agregar( new Cubo() );

    Cubo * clip = new Cubo();
    clip->ponerColor(Hex_a_tupla(0x463D3E));

    agregar (  MAT_Traslacion(0, 0.3, 1.02)
             * MAT_Escalado(1, 5, 0.02)
    );

    agregar( clip );

    agregar( MAT_Traslacion(0, 0, -102) );
    agregar(clip);

    ponerColor(Hex_a_tupla(0x1B1515));

    ponerIdentificador(generar_ident_unico());
    ponerNombre("DIMM slot");
}

RAM_animator::RAM_animator(Matriz4f * &traslacion_RAM1, Matriz4f * &traslacion_RAM2) {
    unsigned ind_trasla_RAM1 = agregar(MAT_Traslacion(0, 1, 0));
    traslacion_RAM1 =  leerPtrMatriz(ind_trasla_RAM1);

    agregar( new RAM() );

    agregar (   MAT_Inversa((*traslacion_RAM1))
              * MAT_Traslacion(.2, 0, 0)
    );

    unsigned ind_trasla_RAM2 = agregar(MAT_Traslacion(0, 1, 0));
    traslacion_RAM2 = leerPtrMatriz(ind_trasla_RAM2);

    agregar( new RAM() );
}

// ────────────────────────────────────────────────────────────────────────────────

CPU_cooler::CPU_cooler(Matriz4f * &rotacion) {
    agregar( new CPU_cooler_body() );

    agregar( MAT_Escalado(.12, .15, .12) );

    unsigned ind_rot = agregar (MAT_Rotacion(0, 0, 1, 0));

    agregar( new CPU_cooler_fan_system() );

    rotacion = leerPtrMatriz(ind_rot);

    ponerIdentificador(generar_ident_unico());
    ponerNombre("CPU cooler");
}


CPU_cooler_fan_system::CPU_cooler_fan_system() {
    agregar( new CPU_cooler_stem() );

    agregar (  MAT_Traslacion(1.2, 0, 0.9)
             * MAT_Rotacion(-35, 1, 0, 0)
    );

    agregar( new CPU_cooler_blade() );

    agregar(  MAT_Traslacion(-2.4, 1, -1.5)
            * MAT_Rotacion(70, 1, 0, 0)
    );

    agregar( new CPU_cooler_blade() );

    agregar (  MAT_Inversa(MAT_Rotacion(70, 1, 0, 0))
             * MAT_Inversa(MAT_Rotacion(-35, 1, 0, 0))
             * MAT_Rotacion(90, 0, 1, 0)
             * MAT_Rotacion(-35, 1, 0, 0)
             * MAT_Traslacion(0.5, -1, 1.8)
    );

    agregar( new CPU_cooler_blade() );

    agregar (  MAT_Traslacion(-2.5, 1, -1.5)
             * MAT_Inversa(MAT_Rotacion(-35, 1, 0, 0))
             * MAT_Rotacion(35, 1, 0, 0)
    );

    agregar( new CPU_cooler_blade() );

    ponerIdentificador(generar_ident_unico());
    ponerNombre("CPU fan system");
}


CPU_cooler_stem::CPU_cooler_stem() {
    agregar (new Cilindro(30, 30));
    ponerColor(Hex_a_tupla(0x181516));

    ponerIdentificador(generar_ident_unico());
    ponerNombre("CPU cooler stem");
}


CPU_cooler_blade::CPU_cooler_blade() {
    agregar(  MAT_Traslacion(0, 1.6, 0)
            * MAT_Escalado(1.7, 1.4, .02)
    );

    Cubo * blade = new Cubo();
    blade->ponerColor(Hex_a_tupla(0xE6E6E6));
    agregar( blade );

    ponerIdentificador(generar_ident_unico());
    ponerNombre("CPU cooler blade");
}

// ────────────────────────────────────────────────────────────────────────────────

PCIE_port::PCIE_port() {
    agregar (  MAT_Rotacion(90, 0, 1, 0)
             * MAT_Escalado(0.03, 0.01, 1)
    );

    agregar( new Cubo() );

    Cubo * clip = new Cubo();
    clip->ponerColor(Hex_a_tupla(0x463D3E));

    agregar (  MAT_Traslacion(0, 0.3, 1.02)
             * MAT_Escalado(1, 5, 0.02)
    );
    agregar( clip );

    ponerColor(Hex_a_tupla(0x1B1515));

    ponerIdentificador(generar_ident_unico());
    ponerNombre("PCIe port");

}
//
// ──────────────────────────────────────────────────────────────────── OTROS ─────
//