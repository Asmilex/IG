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

double RNG (double minimo, double maximo) {
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
      for (int i = 0; i < 4; i++) {
            vertices.push_back({(float)RNG(-1, 1), (float)RNG(-1, 1), (float)RNG(-1, 1)});
      }

      triangulos = {
         {0, 1, 2}, {1, 2, 3}, {0, 2, 3}, {0, 1, 3}
      };
   }

//
// ────────────────────────────────────────────────────────────── CUBOCOLORES ─────
//

   CuboColores::CuboColores() : MallaInd("Cubo de colores aleatorio")
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
         col_ver.push_back(   { (float)RNG(0, 1), (float)RNG(0, 1), (float)RNG(0, 1) } );
      }
   }