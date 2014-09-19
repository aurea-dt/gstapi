////////////////////////////////////////////////////////////////////////////////
//	ADT_Tools.h
//	Mario Chirinos Colunga
//	Aurea Desarrollo Tecnológico.
//	24 Jun 2009 - 
//------------------------------------------------------------------------------
//	Funciones deversas para la biblioteca ADT
//	Notas:	
//		
////////////////////////////////////////////////////////////////////////////////
#ifndef ADT_TOOLS_H
#define ADT_TOOLS_H

// your public header include


// the declaration of your class...
//------------------------------------------------------------------------------
const char* engNotation(long double value, const char *units, int exp);
const char* engNotation(long double value, const char *units);
const char* sciNotation(long double value, const char *units);
bool checkPath(const char* userPath);
//------------------------------------------------------------------------------

#endif
