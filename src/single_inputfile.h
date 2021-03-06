//////////////////////////////
///// single_inputfile.h /////
/////   (Singleton)      /////
//////////////////////////////

#if !defined  INPUT_FILE_HH
#define       INPUT_FILE_HH

#include <cstring>
#include "os_select.h"

//---------------//
class SingleInputFile{
//---------------//
public:
  static SingleInputFile* GetInstance()
  {
    static SingleInputFile instance;  // only instance
    return &instance;
  } 

  void SetName( const char* filename ) ;

  void GetName( char name[] ) { std::strcpy( name, m_name ) ; }
  void GetNameBody ( char body[]) ;
  bool GetNameExt  ( char ext[] ) ; // RETURN: success / fail

  void GetBMPName( char name[] ) { std::strcpy( name, m_bmp_name ) ; }
  void GetPGMName( char name[] ) { std::strcpy( name, m_pgm_name ) ; }
  void GetPPMName( char name[] ) { std::strcpy( name, m_ppm_name ) ; }
  void GetPLYName( char name[] ) { std::strcpy( name, m_ply_name ) ; }

 private:
  // private constructor 
  SingleInputFile()
  { 
     std::strcpy(m_name, ""); 
     m_name_length = 0 ;
    
     std::strcpy(m_bmp_name, ""); 
     std::strcpy(m_pgm_name, ""); 
     std::strcpy(m_ppm_name, ""); 
     std::strcpy(m_ply_name, ""); 
  }

  char m_name [256];
  int  m_name_length ;

  char m_bmp_name [256];
  char m_pgm_name [256];
  char m_ppm_name [256];
  char m_ply_name [256];

}; // SingleInputFile


//-----
inline 
void SingleInputFile::SetName( const char* filename ) 
{ 
  char body[252];

  std::strcpy( m_name, filename ); 
  m_name_length = strlen ( m_name ) ;

  GetNameBody ( body ) ;
  strcpy( m_bmp_name, body); 
  strcat( m_bmp_name, "."); 
  strcat( m_bmp_name, "bmp"); 

  strcpy( m_pgm_name, body); 
  strcat( m_pgm_name, "."); 
  strcat( m_pgm_name, "pgm"); 

  strcpy( m_ppm_name, body); 
  strcat( m_ppm_name, "."); 
  strcat( m_ppm_name, "ppm"); 

  strcpy( m_ply_name, body); 
  strcat( m_ply_name, "."); 
  strcat( m_ply_name, "ply"); 
}



//-----
inline 
void SingleInputFile::GetNameBody ( char body[] )
{
  // local const
#if defined OS_WIN
  const char SEPARATOR = '\';
#else
  const char SEPARATOR = '/';
#endif


  for ( int i = 0; i < m_name_length; i++ ) {
    //    if( m_name[i] == '.' ) { 
    if( m_name[i] == '.' && m_name[i+1] != SEPARATOR ) { //TANAKA
      body[i] = '\0';
      break; 
    }
    else {
      body[i] = m_name[i] ;
    }
    
  }

}


//-----
inline 
bool SingleInputFile::GetNameExt ( char body[] )
{
  // local variables
  char* p ;
  bool flag_found = false ;

  // local const
#if defined OS_WIN
  const char SEPARATOR = '\';
#else
  const char SEPARATOR = '/';
#endif

  // Calc
  for ( p = m_name; p != NULL ; p++ ) {
    //    if( *p == '.' ) { 
    if( *p == '.' && *(p+1) != SEPARATOR ) { //TANAKA
      flag_found = true ;
      p++ ;  // go to the head of ext
      break; 
    }
  }

  // Set 
  if( flag_found ) { std::strcpy( body, p ); }

  // EndFn
  return flag_found ;

}


#endif
