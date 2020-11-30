// *********************************************************************
// **
// ** Informática Gráfica, curso 2020-21
// ** Declaraciones de la clase Objeto3D.hpp
// **
// *********************************************************************

//#include <set>   // std::set
#include "ig-aux.h"
#include "tuplasg.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"
#include <random>


// *****************************************************************************
// funciones auxiliares

float RNG (double minimo, double maximo) {
   std::random_device rd;
   std::mt19937 gen(rd());
   static std::uniform_real_distribution<double> distribucion(minimo,maximo); // distribution in range [1, 6]

   return distribucion(gen);
}


// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() )
   {
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....

}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......


}




// ----------------------------------------------------------------------------


void MallaInd::visualizarGL( ContextoVis & cv )
{

   using namespace std ;
   assert( cv.cauce_act != nullptr );

   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // guardar el color previamente fijado
   const Tupla4f color_previo = leerFijarColVertsCauce( cv );

   // COMPLETAR: práctica 1: si el puntero 'array_verts' es nulo, crear el objeto ArrayVerts
   //   * en el constructor se dan los datos de la tabla de coordenadas de vértices (tabla 'vertices')
   //   * después hay que invocar a 'fijarIndices', usando el formato y datos de la tabla de triángulos ('triangulos')
   //   * si las tablas 'col_ver', 'cc_tt_ver' o 'nor_ver' no están vacías, hay que invocar los métodos
   //     'fijarColores', 'fijarCoordText' y 'fijarNormales', como corresponda.

   if (array_verts == nullptr) {
      array_verts = new ArrayVertices(GL_FLOAT, 3, vertices.size(), vertices.data());
      array_verts->fijarIndices(GL_UNSIGNED_INT, 3*triangulos.size(), triangulos.data());

      if (!col_ver.empty()) {
         array_verts->fijarColores(GL_FLOAT, 3, col_ver.data());
      }
      if (!cc_tt_ver.empty()) {
         array_verts->fijarCoordText(GL_FLOAT, 2, cc_tt_ver.data());
      }
      if (!nor_ver.empty()) {
         array_verts->fijarNormales(GL_FLOAT, nor_ver.data());
      }
   }


   // COMPLETAR: práctica 1: visualizar según el modo (en 'cv.modo_envio')
   //   ** inmediato begin/end       : usar método 'visualizarGL_MI_BVE' de 'ArrayVerts'
   //   ** inmediato con una llamada : usar método 'visualizarGL_MI_DAE' de 'ArrayVerts'
   //   ** diferido (con un VAO)     : usar método 'visualizarGL_MD_VAO' de 'ArrayVerts'
   // (en cualquier caso hay que pasar como parámetro el tipo de primitiva adecuada a una malla de triángulos).
   // .....

   if (cv.modo_envio == ModosEnvio::inmediato_begin_end) {
      array_verts->visualizarGL_MI_BVE(GL_TRIANGLES);
   }
   else if (cv.modo_envio == ModosEnvio::inmediato_drawelements) {
      array_verts->visualizarGL_MI_DAE(GL_TRIANGLES);
   }
   else if (cv.modo_envio == ModosEnvio::diferido_vao) {
      array_verts->visualizarGL_MD_VAO(GL_TRIANGLES);
   }

   // restaurar el color previamente fijado
   glColor4fv( color_previo );
}


// *****************************************************************************


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // ..........................
   LeerPLY(nombre_arch, vertices, triangulos);


   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   // .................

}

// ****************************************************************************
// Clase 'Cubo

Cubo::Cubo()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;
}

//
// ──────────────────────────────────────────────────────────────── TETRAEDRO ─────
//


   Tetraedro::Tetraedro() : MallaInd("Tetraedro aleatorio")
   {
      vertices = {
         { 0,            RNG(0.1, 2),  0          },
         {-RNG(0.1, 2), -RNG(0.1, 2),  RNG(0.1, 2)},
         { RNG(0.1, 2), -RNG(0.1, 2),  RNG(0.1, 2)},
         { 0,           -RNG(0.1, 2), -RNG(0.1, 2)}
      };


      triangulos = {
         {0, 1, 2},  // Frontal
         {3, 1, 0},  // Lateral izquierda
         {3, 0, 2},  // Lateral derecha
         {1, 3, 2}   // Parte de abajo
      };

      ponerColor({ RNG(0, 1), RNG(0, 1), RNG(0, 1) });
   }

//
// ────────────────────────────────────────────────────────────── CUBOCOLORES ─────
//

   CuboColores::CuboColores() : MallaInd("Cubo de colores y tamaño aleatorio")
   {
      float size = RNG(0, 1);

      vertices =
      {  { -size, -size, -size }, // 0
         { -size, -size, +size }, // 1
         { -size, +size, -size }, // 2
         { -size, +size, +size }, // 3
         { +size, -size, -size }, // 4
         { +size, -size, +size }, // 5
         { +size, +size, -size }, // 6
         { +size, +size, +size }, // 7
      } ;



      triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

      for (int i = 0; i < vertices.size(); i++) {
         col_ver.push_back(   { RNG(0, 1), RNG(0, 1), RNG(0, 1) } );
      }
   }

   CPU_cooler_body::CPU_cooler_body() : MallaInd("CPU cooler body")
   {
      float border_width = 0.1;
      float length = 0.5;
      float heigth = 0.5;

      vertices = {
         // Parte superior externa
         {-length, heigth ,-length},
         { length, heigth, -length},
         {-length, heigth, length},
         { length, heigth, length},

         // Parte inferior externa
         {-length, 0, -length},
         { length, 0, -length},
         {-length, 0,length},
         { length, 0, length},

         // Parte superior interna
         {-length + border_width, heigth ,-length + border_width},
         { length - border_width, heigth, -length + border_width},
         {-length + border_width, heigth, length - border_width},
         { length - border_width, heigth, length - border_width},

         // Parte inferior interna
         {-length + border_width, 0, -length + border_width},
         { length - border_width, 0, -length + border_width},
         {-length + border_width, 0, length - border_width},
         { length - border_width, 0, length - border_width},
      };

      triangulos = {
         // Parte trasera exterior
         {4, 1, 0},
         {5, 1, 4},

         // Parte derecha exterior
         {5, 7, 3},
         {5, 3, 1},

         // Parte frontal exterior
         {7, 2, 6},
         {7, 3, 2},

         // Parte izquierda exterior
         {6, 4, 2},
         {4, 0, 2},


         // Uniones de la parte superior
         {8, 1, 0},
         {8, 9, 1},

         {3, 1, 9},
         {3, 9, 11},

         {2, 3, 11},
         {2, 11, 10},

         {2, 10, 8},
         {2, 8, 0},

         // Uniones de la parte inferior
         {12, 5, 4},
         {12, 13, 5},

         {15, 5, 13},
         {15, 7, 5},

         {6, 7, 15},
         {15, 14, 6},

         {6, 14, 12},
         {12, 4, 6},
      };

      // Parte interior: exterior + 8
      for (int i = 0; i < 8; i++) {
         triangulos.push_back(
            {triangulos[i](0) + 8, triangulos[i](1) + 8, triangulos[i](2) + 8}
         );
      }

      ponerColor({24.0/255.0, 21.0/255.0, 22.0/255.0});
   };


EstrellaY::EstrellaY(unsigned int n) : MallaInd("Estrella") {
   // inicializar tabla de vértices (2n), triángulos (2n + 1) y colores.
   // Plano perpendicular al eje Y.
   // Vértices tienen coordenadas en [0, 1]. Centro en 0.5, 0.5, 0.5. Radios de 0.5.
   // Vértice central de color blanco. Resto de vértices coinciden con su componente en el mundo (entre 0 y 1).

   vertices.push_back(Tupla3f(0.5, 0, 0.5));
   col_ver.push_back({1.0, 1.0, 1.0});
   for (int i = 0; i < n; i++) {
      float angulo = 360 * (float)i/(float)n;
      vertices.push_back(
         {vertices[0] + MAT_Rotacion(angulo, 0, 1, 0) * Tupla3f(0.5, 0, 0)}
      );

      col_ver.push_back(Tupla3f(vertices[i+1](0), vertices[i+1](1), vertices[i+1](2)));
   }

   for (int i = 0; i < n; i++) {
      float angulo = 360 * (float)i/(float)n + 360/(2.0 * n);
      vertices.push_back(
         {vertices[0] + MAT_Rotacion(angulo, 0, 1, 0) * Tupla3f(0.25, 0, 0)}
      );
      col_ver.push_back(Tupla3f(vertices[n+i+1](0), vertices[n+i+1](1), vertices[n+i+1](2)));

   }

   for (int i = 1; i <= n; i++) {
      triangulos.push_back(Tupla3i(0, n+i, i));
   }

   for (int i = 1; i < n; i++){
      triangulos.push_back(Tupla3i(0, (i+1), n+i));
   }
   triangulos.push_back(Tupla3i(0, 2*n, 1));
}





PiramideEstrellaY::PiramideEstrellaY(unsigned int n) : MallaInd("Piramide") {

   vertices.push_back(Tupla3f(0.5, 0, 0.5));
   col_ver.push_back({1.0, 1.0, 1.0});
   for (int i = 0; i < n; i++) {
      float angulo = 360 * (float)i/(float)n;
      vertices.push_back(
         {vertices[0] + MAT_Rotacion(angulo, 0, 1, 0) * Tupla3f(0.5, 0, 0)}
      );

      col_ver.push_back(Tupla3f(vertices[i+1](0), vertices[i+1](1), vertices[i+1](2)));
   }


   for (int i = 0; i < n; i++) {
      float angulo = 360 * (float)i/(float)n + 360/(2.0 * n);
      vertices.push_back(
         {vertices[0] + MAT_Rotacion(angulo, 0, 1, 0) * Tupla3f(0.25, 0, 0)}
      );
      col_ver.push_back(Tupla3f(vertices[n+i+1](0), vertices[n+i+1](1), vertices[n+i+1](2)));

   }

   vertices.push_back(Tupla3f(0.5, 0.5, 0.5));
   col_ver.push_back({1.0, 1.0, 1.0});

   for (int i = 1; i <= n; i++) {
      triangulos.push_back(Tupla3i(0, n+i, i));
   }

   for (int i = 1; i < n; i++){
      triangulos.push_back(Tupla3i(0, (i+1), n+i));
   }
   triangulos.push_back(Tupla3i(0, 2*n, 1));

   for (int i = 1; i <= n; i++) {
      triangulos.push_back(Tupla3i(vertices.size() - 1, n+i, i));
   }

   for (int i = 1; i < n; i++){
      triangulos.push_back(Tupla3i(vertices.size() - 1, (i+1), n+i));
   }
   triangulos.push_back(Tupla3i(vertices.size() - 1, 2*n, 1));

}