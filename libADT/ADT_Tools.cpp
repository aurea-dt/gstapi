////////////////////////////////////////////////////////////////////////////////
//	ADT_Tools.cpp
//	Mario Chirinos Colunga
//	Aurea Desarrollo Tecnológico.
//	24 Jun 2009 - 
//------------------------------------------------------------------------------
//	Funciones deversas para la biblioteca ADT
//	Notas:	
//		
////////////////////////////////////////////////////////////////////////////////
#include"ADT_Tools.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

#include <sys/stat.h>

using namespace std;
//-------------------------- Formato Ingenieria --------------------------------
const char* engNotation(long double value, const char *units, int exp)
{
	if(exp <0 || exp > 3)
		return "error";

	int uni=8;
	const char* prefix[17] = {"Y", "Z", "E", "P", "T", "G", "M", "k", "", "m", "μ", "n", "p", "f", "a", "z", "y"};
	const char* expSym[3] = {"", "²", "³"};
	if (value!=0)
	{
		if (value <1)
			do
			{
				value *= pow(1000, exp);
				uni++;

			}while (value <1);// || numero >= 1000);

		if (value >= 1000)
			do
			{
				value /= pow(1000, exp);
				uni--;
			}while (value >= 1000);//(numero <1 || numero >= 1000);
		stringstream ss;
		string formatedValue;
		ss << fixed << setprecision(3) << value << " "<< prefix[uni] << units << expSym[exp-1];

		getline (ss, formatedValue);

		return formatedValue.c_str();
	}
	else 
		return "error";
}
//------------------------------------------------------------------------------
const char* engNotation(long double value, const char *units)
{
	int uni=0;
	if (value!=0)
	{
		if (value <1)
			do
			{
				value *= 1000;
				uni-=3;

			}while (value <1);// || numero >= 1000);

		if (value >= 1000)
			do
			{
				value /= 1000;
				uni+=3;
			}while (value >= 1000);//(numero <1 || numero >= 1000);
		stringstream ss;
		string formatedValue;
		ss << fixed << setprecision(3) << value << "e" << (uni>0?"+":"") << uni << " " << units;

		getline (ss, formatedValue);

		return formatedValue.c_str();
	}
	else 
		return "error";
}
//----------------------------Formato Cientifico--------------------------------
const char* sciNotation(long double value, const char *units)
{
	//if(exp <0 || exp > 3)
	//	return "error";

	//const char* expSym[3] = {"", "²", "³"};
	stringstream ss;
	string formatedValue;
	ss << scientific << setprecision(3) << value << " " << units;// << expSym[exp-1];
	
	getline (ss, formatedValue);
	return formatedValue.c_str();
}
//------------------------------------------------------------------------------
bool checkPath(const char* userPath )//Check if the directory userPath exisit
{
   struct stat statBuf;

   if( stat( userPath, &statBuf ) != 0 ) 
         return false;

  return true;//S_ISDIR( statBuf.st_mode );//retunring if is a FILE 
}
//------------------------------------------------------------------------------

