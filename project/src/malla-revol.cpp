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
         vertices.push_back( MAT_Rotacion(2*M_PI*i/(num_copias - 1), {0.0, 1.0, 0.0} ) * vertices[j] );
      }
   }

   int k = 0;
   for (int i = 0; i < num_copias - 1; i++) {
      for (int j = 0; j < perfil.size() - 1; j++) {
         k = i*perfil.size() + j;
         triangulos.push_back( {k, k + perfil.size(), k + perfil.size() + 1} );
         triangulos.push_back( {k, k + perfil.size() + 1, k + 1} );
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
   LeerVerticesPLY(nombre_arch, vertices);
   inicializar(vertices, nperfiles);


}
