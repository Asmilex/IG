// *********************************************************************
// **
// ** Informática Gráfica, curso 2019-20
// ** Implementación de la clase 'MallaRevol'
// **
// *********************************************************************

#include "ig-aux.h"
#include "tuplasg.h"
#include "lector-ply.h"
#include "matrices-tr.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar (   const std::vector<Tupla3f> & perfil,      // tabla de vértices del perfil original
                                 const unsigned               num_copias  )// número de copias del perfil

{
   // COMPLETAR: Práctica 2: completar: creación de la malla....

   for (int i = 0; i < num_copias; i++) {
      for (int j = 0; j < perfil.size(); j++) {
         //                               Rotamos sobre el eje Y
         //                  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
         double angulo_grados = ((2*M_PI*i)/(num_copias - 1))*(180/M_PI);
         vertices.push_back( MAT_Rotacion(angulo_grados, {0.0, 1.0, 0.0} ) * perfil[j] );

      }
   }

   size_t k = 0;
   for (int i = 0; i < num_copias - 1; i++) {
      for (int j = 0; j < perfil.size() - 1; j++) {
         k = i*perfil.size() + j;

         Tupla3i nueva_tupla_1 = Tupla3i(k, k + perfil.size(),     k + perfil.size() + 1);
         Tupla3i nueva_tupla_2 = Tupla3i(k, k + perfil.size() + 1, k + 1);

         triangulos.push_back( nueva_tupla_1 );
         triangulos.push_back( nueva_tupla_2 );
      }
   }
}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................
   vector<Tupla3f> perfil;
   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil, nperfiles);
}


//
// ─────────────────────────────────────────────────────────────── PRACTICA 2 ─────
//

Cilindro::Cilindro (const int num_verts_per, const unsigned nperfiles) {
   if (num_verts_per < 4) {
      cout << "Cilindro::Cilindro: se necesitan al menos 4 vértices para generar un cilindro";
   }

   string nombre = "Cilindro de altura " + to_string(altura) + " y radio " + to_string(radio) + "con "
                     + to_string(num_verts_per) + " vértices y " + to_string(nperfiles) + "perfiles";
   ponerNombre(nombre);


   vector<Tupla3f> perfil = {
      {0,     0,      0},     // Vértice de la base
   };

   // Interpolar desde el extremo de la base hasta el extremo superior
   // Extremo inf + i/(nvp-3) * altura
   for (int i = 0; i < num_verts_per - 2; i++) {
      perfil.push_back(
         {radio, ((float)i/(float)(num_verts_per - 3)) * altura, 0}
      );
   }

   perfil.push_back({0, altura, 0});      // Vértice superior de la base)

   inicializar(perfil, nperfiles);
}

// ────────────────────────────────────────────────────────────────────────────────

Cono::Cono (const int num_verts_per, const unsigned nperfiles) {
   if (num_verts_per < 3) {
      cout << "Se necesitan al menos 3 vértices para generar un cono";
   }

   string nombre = "Cono de altura " + to_string(altura) + " y radio " + to_string(radio) + "con "
                     + to_string(num_verts_per) + " vértices y " + to_string(nperfiles) + "perfiles";
   ponerNombre(nombre);

   vector<Tupla3f> perfil = {
      {0, 0, 0}
   };

   for (int i = 0; i < num_verts_per - 1; i++) {
      perfil.push_back(
         {radio - ((float)i/(float)(num_verts_per-2)) * radio, 0 + ((float)i/(float)(num_verts_per-2)) * altura, 0}
      );
   }

   perfil.push_back({0, altura, 0});

   inicializar(perfil, nperfiles);
}

// ────────────────────────────────────────────────────────────────────────────────

Esfera::Esfera (const int num_verts_per, const unsigned nperfiles) {
   string nombre = "Esfera de radio " + to_string(radio) + "con "
                  + to_string(num_verts_per) + " vértices y " + to_string(nperfiles) + "perfiles";

   ponerNombre(nombre);

   vector<Tupla3f> perfil = {
      {0, -radio, 0}
   };

   for (int i = 1; i < num_verts_per; i++) {
      perfil.push_back(
         MAT_Rotacion((180 * i)/(num_verts_per - 1), {0, 0, radio}) * perfil[0]
      );
   }

   inicializar(perfil, nperfiles);
}