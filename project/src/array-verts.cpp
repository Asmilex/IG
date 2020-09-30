// *********************************************************************
// **
// ** Informática Gráfica - curso 2020-21
// ** Implementaciones de las clases 'DescrTabla' y 'ArrayVerts'
// **
// *********************************************************************

#include <vector>
#include "array-verts.h"


// -----------------------------------------------------------------------------

const std::vector<GLenum> valores_tipo_tabla =
{
   GL_ARRAY_BUFFER,
   GL_ELEMENT_ARRAY_BUFFER
};

const std::vector<GLenum> valores_atributo =
{
   GL_VERTEX_ARRAY,
   GL_TEXTURE_COORD_ARRAY,
   GL_COLOR_ARRAY,
   GL_NORMAL_ARRAY
};

const std::vector<GLenum> tipos_numericos_atributos =
{
   GL_FLOAT,
   GL_DOUBLE
};

const std::vector<GLenum> tipos_numericos_indices =
{
   GL_UNSIGNED_BYTE,
   GL_UNSIGNED_SHORT,
   GL_UNSIGNED_INT
};
// -----------------------------------------------------------------------------
// devuelve cuantos bytes ocupa un valor numérico del tipo de datos OpenGL
// especificado por el parámetro 'tipo'

unsigned NumBytesValor( const GLenum tipo )
{
   using namespace std ;
   switch( tipo )
   {
      case GL_FLOAT          : return sizeof( GLfloat );
      case GL_DOUBLE         : return sizeof( GLdouble );
      case GL_UNSIGNED_BYTE  : return sizeof( GLubyte );
      case GL_UNSIGNED_SHORT : return sizeof( GLushort );
      case GL_UNSIGNED_INT   : return sizeof( GLuint );
      default :
         cout << "error: valor incorrecto de 'tipo' en 'NumBytesValor(..)'." << endl ;
         exit(1);
   }
}
// -----------------------------------------------------------------------------

bool no_incluye( const std::vector<GLenum> & vec, const GLenum val )
{
   return find( vec.begin(), vec.end(), val ) == vec.end() ;
}
// -----------------------------------------------------------------------------

bool incluye( const std::vector<GLenum> & vec, const GLenum val )
{
   return find( vec.begin(), vec.end(), val ) != vec.end() ;
}

// ******************************************************************************
//
// Implementación de la clase 'DescrTabla'
//
// -----------------------------------------------------------------------------

DescrTabla::DescrTabla( const GLenum  p_tipo_tabla,      const GLenum   p_atributo,
                          const GLenum  p_tipo_valores,    const GLint    p_num_vals_tupla,
                          const GLsizei p_num_tuplas_ind,  const GLvoid * p_datos )
{
   using namespace std ;

   tipo_tabla      = p_tipo_tabla ;
   atributo        = p_atributo ;
   tipo_valores    = p_tipo_valores ;
   num_vals_tupla  = p_num_vals_tupla ;
   num_tuplas_ind  = p_num_tuplas_ind ;
   datos           = p_datos ;

   comprobar();

   num_bytes_valor = NumBytesValor( p_tipo_valores ) ;
   tamano_en_bytes = num_bytes_valor * num_vals_tupla * num_tuplas_ind ;
   nombre_vbo      = 0 ; // todavía no está en la GPU (se envía en la primera activación en MD (activar_md))

}
// -----------------------------------------------------------------------------
// comprueba que el descriptor de buffer está en un estado correcto, si no lo está
// imprime mensaje explicativo y aborta el programa

void DescrTabla::comprobar()
{
   using namespace std ;

   if ( ! incluye( valores_tipo_tabla, tipo_tabla ) )
   {
      cout << "error: 'p_tipo_tabla' incorrecto en 'DescrTabla::DescrTabla()'" << endl ;
      exit(1);
   }
   if ( num_tuplas_ind == 0 )
   {
      cout << "error: el valor de 'p_num_tuplas_ind' no puede ser cero en 'DescrTabla::DescrTabla()'" << endl ;
      exit(1);
   }
   if ( datos == nullptr )
   {
      cout << "error: el valor de 'p_datos' no puede ser 'nullptr' en 'DescrTabla::DescrTabla()'" << endl ;
      exit(1);
   }

   if ( tipo_tabla == GL_ARRAY_BUFFER ) // tabla de coordenadas o atributos
   {
      if ( ! incluye( valores_atributo, atributo ) )
      {
         cout << "error: valor incorrecto de 'p_atributo' en 'DescrTabla::DescrTabla()'" << endl ;
         exit(1);
      }
      if ( ! incluye( tipos_numericos_atributos, tipo_valores ))
      {
         cout << "error: valor incorrecto de 'p_tipo_valores' en 'DescrTabla::DescrTabla()'" << endl ;
         exit(1);
      }
      if ( num_vals_tupla != 2 && num_vals_tupla != 3 && num_vals_tupla != 4 )
      {
         cout << "error: valor incorrecto de 'p_num_vals_tupla' en 'DescrTabla::DescrTabla()', debe ser 2, 3, o 4" << endl ;
         exit(1);
      }
      if ( atributo == GL_NORMAL_ARRAY && num_vals_tupla != 3 )
      {
         cout << "error: valor de 'p_num_vals_tupla' no es 3 para la tabla de normales en 'DescrTabla::DescrTabla()', debe ser 2, 3, o 4" << endl ;
         exit(1);
      }
   }
   else // tipo_tabla == GL_ELEMENT_BUFFER (tabla de índices)
   {
      if ( ! incluye( tipos_numericos_indices, tipo_valores ) )
      {
         cout << "error: valor incorrecto de 'p_tipo_valores' en 'DescrTabla::DescrTabla' (tabla de índices)" << endl ;
         exit(1);
      }
      if ( num_vals_tupla != 1 )
      {
         cout << "error: el número de valores por tupla debe ser 1 en 'DescrTabla::DescrTabla' (tabla de índices)" << endl ;
         exit(1);
      }
   }
}



// -----------------------------------------------------------------------------
// destructor (no libera memoria con los datos, solo en la GPU si procede)

DescrTabla::~DescrTabla()
{
   // si se ha reservado memoria en la GPU, liberarla
   if ( nombre_vbo != 0 )
      glDeleteBuffers( 1, &nombre_vbo );

}
// -----------------------------------------------------------------------------
// Establece donde están los datos en RAM o en la GPU (usando OpenGL 2.0)
//   'ptr_offset' es o bien un puntero en RAM (para modo inmediato), o bien un
//   offset en un VBO de la GPU (típicamente 0) (para modo diferido)

void DescrTabla::fijarPuntero( const GLvoid * ptr_offset )
{
   using namespace std ;
   assert( tipo_tabla == GL_ARRAY_BUFFER );
   // COMPLETAR: práctica 1: indicar localización y formato de tabla (hay que invocar
   // a 'glVertexPointer' o 'glTexCoordPointer' o 'glColorPointer' o 'glNormalPointer',
   // según que atributo se codifica en la tabla)
   //
   // .....

}

// -----------------------------------------------------------------------------
// Activa el  buffer (modo inmediato) - solo para tablas de atributos

void DescrTabla::activar_mi()
{
   using namespace std ;
   if ( tipo_tabla != GL_ARRAY_BUFFER )
   {
      cout << "error: no se puede invocar 'activar_mi' para una tabla de índices." << endl ;
      exit(1);
   }
   CError();

   fijarPuntero(datos);             // Especifica localización y formato
   glEnableClientState(atributo);   // Habilita el uso de la tabla

   CError();
}
// -----------------------------------------------------------------------------
// Activa el buffer (modo diferido) - para cualquier tabla (atributos o índices)

void DescrTabla::activar_md()
{
   CError();

   if (nombre_vbo == 0) {
      glGenBuffers(1, &nombre_vbo);           // Crear el nuevo nombre de VBO
      glBindBuffer(tipo_tabla, nombre_vbo);   // Enlazar tabla con el nuevo VBO
      glBufferData(tipo_tabla, tamano_en_bytes, datos, GL_STATIC_DRAW);    // Alojar en VRAM
   }
   else {
      // VBO ya estaba creado; activarlo simplemente
      glBindBuffer(tipo_tabla, nombre_vbo);
   }

   if (tipo_tabla == GL_ARRAY_BUFFER) {
      // Si tratamos una tabla de atributos, especificar localización y formato; y habilitar su uso

      fijarPuntero(0);
      glBindBuffer(tipo_tabla, 0);
      glEnableClientState(atributo);
   }

   CError();
}

// ******************************************************************************
//
// Implementación de la clase 'ArrayVertices'
//
// -----------------------------------------------------------------------------

// Constructor: crea un array de vértices, indicando las coordenadas de los mismos
ArrayVertices::ArrayVertices( const GLenum tipo_valores, const GLint num_vals_tupla,
                              const GLsizei p_num_vertices,   const GLvoid * datos )
{
   assert( datos != nullptr );
   assert( 0 < p_num_vertices );
   assert( incluye( tipos_numericos_atributos, tipo_valores ) );
   assert( num_vals_tupla == 2 || num_vals_tupla == 3 || num_vals_tupla == 4 );

   num_vertices = p_num_vertices ;

   // crear descriptor de buffer
   coordenadas = new DescrTabla( GL_ARRAY_BUFFER, GL_VERTEX_ARRAY, tipo_valores, num_vals_tupla, num_vertices, datos );
   assert( coordenadas != nullptr );
}

// -----------------------------------------------------------------------------
// destructor: destruye los buffers (libera memoria ocupada en la GPU, si hay alguna,
// no destruye ni modifica las tablas en RAM)

ArrayVertices::~ArrayVertices()
{
   delete coordenadas ;
   delete colores ;
   delete normales ;
   delete coords_textura ;
   delete indices ;
}
 // -----------------------------------------------------------------------------

// ;étodos para establecer las tablas de atributos (son opcionales)
// (se asume que el numero de tuplas en cada tabla coincide con el número de vértices especificados en el constructor)

// Establece puntero a tabla de colores
void ArrayVertices::fijarColores( const GLenum tipo_valores, const GLint num_vals_tupla, const GLvoid *datos )
{
   // comprobar que los parámetros son correctos
   assert( datos != nullptr );
   assert( incluye( tipos_numericos_atributos, tipo_valores ) );
   assert( num_vals_tupla == 2 || num_vals_tupla == 3 || num_vals_tupla == 4 );

   // crear descriptor de buffer
   colores = new DescrTabla( GL_ARRAY_BUFFER, GL_COLOR_ARRAY, tipo_valores, num_vals_tupla, num_vertices, datos );
   assert( colores != nullptr );
}
// -----------------------------------------------------------------------------
// Establece puntero a la tabla de coordenadas de textura

void ArrayVertices::fijarCoordText( const GLenum tipo_valores, const GLint num_vals_tupla, const GLvoid *datos )
{
   // comprobar que los parámetros son correctos
   assert( datos != nullptr );
   assert( incluye( tipos_numericos_atributos, tipo_valores ) );
   assert( num_vals_tupla == 2 || num_vals_tupla == 3 || num_vals_tupla == 4 );

   // crear descriptor de tabla
   coords_textura = new DescrTabla( GL_ARRAY_BUFFER, GL_TEXTURE_COORD_ARRAY, tipo_valores, num_vals_tupla, num_vertices, datos );
   assert( coords_textura != nullptr );
}
// -----------------------------------------------------------------------------
// Establece puntero a la tabla de normales de vértices (se asumen 3 reales por normal)

void ArrayVertices::fijarNormales( const GLenum tipo_valores, const GLvoid *datos )
{
   // comprobar que los parámetros son correctos
   assert( datos != nullptr );
   assert( incluye( tipos_numericos_atributos, tipo_valores ) );

   // crear descriptor de tabla
   normales = new DescrTabla( GL_ARRAY_BUFFER, GL_NORMAL_ARRAY, tipo_valores, 3, num_vertices, datos );
   assert( normales != nullptr );
}
// -----------------------------------------------------------------------------
// Método para establecer puntero a la tabla de índices (es opcional)

void ArrayVertices::fijarIndices( const GLenum tipo_valores, const GLsizei p_num_indices, const GLvoid * datos )
{
   // comprobar que los parámetros son correctos
   assert( datos != nullptr );
   assert( incluye( tipos_numericos_indices, tipo_valores ) );
   num_indices = p_num_indices ;

   // crear descriptor de buffer (el segundo parámetro no se lee, puede tener cualquier valor)
   indices = new DescrTabla( GL_ELEMENT_ARRAY_BUFFER, 0, tipo_valores, 1, p_num_indices, datos );
   assert( indices != nullptr );
}

// -----------------------------------------------------------------------------
// Comprobar que el formato de las tablas es el esperado antes de visualizar con begin/end,
// (la visualización con begin/end solo va a funcionar para instancias de 'ArrayVerts' con
// datos flotantes en simple precisión (float), con tres valores por tupla, excepto la tabla
// de coordenadas de textura con dos valores por tupla)
// Si el formato no es el adecuado el programa aborta (la función 'assert' se invoca
// con 'false' como argumento)

void ArrayVertices::comprobarFormato_MI_BVE()
{
   assert( coordenadas->tipo_valores == GL_FLOAT );
   assert( coordenadas->num_vals_tupla == 3 );

   if ( colores != nullptr )
   {
      assert( colores->tipo_valores == GL_FLOAT );
      assert( colores->num_vals_tupla == 3 );
   }
   if ( normales != nullptr )
   {
      assert( normales->tipo_valores == GL_FLOAT );
      assert( normales->num_vals_tupla == 3 );
   }
   if ( coords_textura != nullptr )
   {
      assert( coords_textura->tipo_valores == GL_FLOAT );
      assert( coords_textura->num_vals_tupla == 2 );
   }
   if ( indices != nullptr )
      assert( indices->tipo_valores == GL_UNSIGNED_INT );
}

// -----------------------------------------------------------------------------
// Métodos que visualizan el array de vértices (no modifcan estado de OpenGL, excepto
// los punteros a buffers que al final quedan todos deshabilitados)
// 'mode' indica el tipo de primitiva: GL_TRIANGLES, GL_LINES, GL_POLYGON, etc....

// -----------------------------------------------------------------------------
// Visualizar en modo inmediato, usando  una llamada por vértice (glBegin/glVertex/glEnd)

void ArrayVertices::visualizarGL_MI_BVE( const GLenum tipo_primitiva )
{
   CError();
   // comprobar que el formato de las tablas es el único que acepta este método
   // (aborta si no lo es)
   assert( coordenadas != nullptr );
   comprobarFormato_MI_BVE();

   /*
      Si hay índices, recorrer los vértices en el orden dado.
      En otro caso, recorrerlos conforme nos los encontramos.

      Debemos enviar los atributos correspondientes a cada vértice si es que existieran.
      Se asume que las coordenadas, colores y normales son tuplas de 3 float (no doubles), y las
      coords de textura tuplas de 2 flotantes. Los indices son 'unsigned int'
   */


   const int nv = (indices != nullptr)
      ? indices->num_tuplas_ind
      : num_vertices;

   glBegin(tipo_primitiva);

   for (GLuint i = 0; i < nv; i++) {
      const GLuint index_vertex = (indices->datos != nullptr)
         ? *((GLuint *)indices->datos + i*sizeof(GLuint))
         : i;

      if (colores != nullptr) {
         glColor3fv ((const GLfloat *) colores->datos + 3*index_vertex);
      }
      if (normales != nullptr) {
         glNormal3fv((const GLfloat *) normales->datos + 3*index_vertex);
      }
      if (coords_textura != nullptr) {
         glTexCoord2fv((const GLfloat *) coords_textura->datos + 2*index_vertex);
      }

      glVertex3fv((const GLfloat *) coordenadas->datos + 3*index_vertex);
   }

   glEnd();
   CError();
}
// -----------------------------------------------------------------------------

// Visualizar en modo inmediato, con una única llamada a 'DrawArrays' (no indexado)
// o 'DrawElements' (indexado)

void ArrayVertices::visualizarGL_MI_DAE( const GLenum tipo_primitiva )
{
   using namespace std ;
   //cout << __FUNCTION__ << ": inicio " << endl ;

   assert( coordenadas != nullptr );
   CError();

   /*
      Tareas a realizar:
         1. Activar VAO por defecto
         2. Activar tablas no vacías (en modo inmediato)
         3. Deshabilitar todas las tablas al inicio y al final
         4. Dibujarlo según esté indexada o no.

   */

   glBindVertexArray(0);
   deshabilitar_tablas();

   coordenadas->activar_mi();

   if (colores != nullptr) {
      colores->activar_mi();
   }
   if (normales != nullptr) {
      normales->activar_mi();
   }
   if (coords_textura != nullptr) {
      coords_textura->activar_mi();
   }

   // Comprobar si estamos usando índices
   if (indices != nullptr) {
      glDrawElements(tipo_primitiva, num_indices, indices->tipo_valores, indices->datos);
   }
   else {
      glDrawArrays(tipo_primitiva, 0, num_vertices);
   }

   deshabilitar_tablas();

   CError();
}
// -----------------------------------------------------------------------------

void ArrayVertices::deshabilitar_tablas()
{
   glDisableClientState( GL_VERTEX_ARRAY );
   glDisableClientState( GL_COLOR_ARRAY );
   glDisableClientState( GL_TEXTURE_COORD_ARRAY );
   glDisableClientState( GL_NORMAL_ARRAY );
   CError();
}
// -----------------------------------------------------------------------------

// Visualizar en modo diferido, con una única llamada a 'DrawArrays' (no indexado)
// o 'DrawElements' (indexado), usando VBOs y un VAO

void ArrayVertices::visualizarGL_MD_VAO( const GLenum tipo_primitiva )
{
   using namespace std ;
   //cout << __FUNCTION__ << " : inicio " << endl ;
   CError();

   if (nombre_vao == 0) {
      // Crear VAO nuevo
      glGenVertexArrays(1, &nombre_vao);
      glBindVertexArray(nombre_vao);

      coordenadas->activar_md();

      if (colores != nullptr) {
         colores->activar_md();
      }
      if (normales != nullptr) {
         normales->activar_md();
      }
      if (coords_textura != nullptr) {
         coords_textura->activar_md();
      }
      if (indices != nullptr) {
         indices->activar_md();
      }
   }
   else {
      glBindVertexArray(nombre_vao);
   }

   if (indices != nullptr) {
      glDrawElements(tipo_primitiva, num_indices, indices->tipo_valores, indices->datos);
   }
   else {
      glDrawArrays(tipo_primitiva, 0, num_vertices);
   }

   // Deshabilitar VAO para acabar
   glBindVertexArray(0);

   CError();
}
// -----------------------------------------------------------------------------
