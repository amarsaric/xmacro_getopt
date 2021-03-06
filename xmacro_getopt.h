/*
 *
 * XMACRO_GETOPT - A wrapper for the getopt and getopt_long functions.
 * Copyright (C) 2014-2017 Amar Saric (asaric <at> gmail <dot> com).
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/.
 *
 */
 
#ifndef XMACRO_GETOPT_H
#define XMACRO_GETOPT_H

#include <unistd.h>
#include <getopt.h>

#define XMACRO_GETOPT_CONCAT(A, B) A##B 
 
#ifndef  XMACRO_GETOPT_USE_SHORT_OPTIONS

#define XMACRO_GETOPT_OPTION_WITH_ARG XMACRO_GETOPT_OPTION_NO_ARG	
#undef  XMACRO_GETOPT_OPTION_NO_ARG
#define XMACRO_GETOPT_OPTION_NO_ARG(TAG, SHORT, LONG) XMACRO_GETOPT_CONCAT(TAG, _INDEX), 
#undef  XMACRO_GETOPT_OPTION_SHORT_ONLY_NO_ARG
#define XMACRO_GETOPT_OPTION_SHORT_ONLY_NO_ARG(TAG, SHORT) XMACRO_GETOPT_CONCAT(TAG, _INDEX), 
enum INDEXES
{
    XMACRO_GETOPT_OPTIONS_NO_ARG
    XMACRO_GETOPT_OPTIONS_WITH_ARG
    XMACRO_GETOPT_OPTIONS_SHORT_ONLY_NO_ARG
    XMACRO_GETOPT_NUM_OF_OPTIONS
};   	

#undef  XMACRO_GETOPT_OPTION_NO_ARG
#define XMACRO_GETOPT_OPTION_NO_ARG(TAG, SHORT, LONG)  TAG = SHORT,  
#undef  XMACRO_GETOPT_OPTION_SHORT_ONLY_NO_ARG
#define XMACRO_GETOPT_OPTION_SHORT_ONLY_NO_ARG(TAG, SHORT) TAG = SHORT, 
enum VALUES
{
    XMACRO_GETOPT_OPTIONS_NO_ARG
    XMACRO_GETOPT_OPTIONS_WITH_ARG
    XMACRO_GETOPT_OPTIONS_SHORT_ONLY_NO_ARG
};   	

#undef  XMACRO_GETOPT_OPTION_NO_ARG
#define XMACRO_GETOPT_OPTION_NO_ARG(TAG, SHORT, LONG) 0,   
#undef  XMACRO_GETOPT_OPTION_SHORT_ONLY_NO_ARG
#define XMACRO_GETOPT_OPTION_SHORT_ONLY_NO_ARG(TAG, SHORT) 0,
unsigned char xmacro_getopt_option_used[] = {
    XMACRO_GETOPT_OPTIONS_NO_ARG
    XMACRO_GETOPT_OPTIONS_WITH_ARG
    XMACRO_GETOPT_OPTIONS_SHORT_ONLY_NO_ARG
};

#undef  XMACRO_GETOPT_OPTION_NO_ARG
#define XMACRO_GETOPT_OPTION_NO_ARG(TAG, SHORT, LONG) {LONG, no_argument, NULL, SHORT},
#undef  XMACRO_GETOPT_OPTION_WITH_ARG
#define XMACRO_GETOPT_OPTION_WITH_ARG(TAG, SHORT, LONG) {LONG, required_argument, NULL, SHORT},
struct option xmacro_getopt_lopts[] = {
    XMACRO_GETOPT_OPTIONS_NO_ARG
    XMACRO_GETOPT_OPTIONS_WITH_ARG
    {0, 0, 0, 0}
};	

#undef  XMACRO_GETOPT_OPTION_NO_ARG
#define XMACRO_GETOPT_OPTION_NO_ARG(TAG, SHORT, LONG) , SHORT
#undef  XMACRO_GETOPT_OPTION_WITH_ARG
#define XMACRO_GETOPT_OPTION_WITH_ARG(TAG, SHORT, LONG) , SHORT, ':'
#undef XMACRO_GETOPT_OPTION_SHORT_ONLY_NO_ARG
#define XMACRO_GETOPT_OPTION_SHORT_ONLY_NO_ARG(TAG, SHORT) , SHORT 

char xmacro_getopt_optstring[] = {':' XMACRO_GETOPT_OPTIONS_NO_ARG XMACRO_GETOPT_OPTIONS_SHORT_ONLY_NO_ARG XMACRO_GETOPT_OPTIONS_WITH_ARG, '0'};

#define  XMACRO_GETOPT(ARGC, ARGV) getopt_long(ARGC, ARGV, xmacro_getopt_optstring, xmacro_getopt_lopts, NULL)

#else /*  XMACRO_GETOPT_USE_LONG_OPTIONS */

#define XMACRO_GETOPT_OPTION_WITH_ARG XMACRO_GETOPT_OPTION_NO_ARG	

#undef  XMACRO_GETOPT_OPTION_NO_ARG
#define XMACRO_GETOPT_OPTION_NO_ARG(TAG, SHORT) XMACRO_GETOPT_CONCAT(TAG, _INDEX),    
enum INDEXES
{
    XMACRO_GETOPT_OPTIONS_NO_ARG
    XMACRO_GETOPT_OPTIONS_WITH_ARG
    XMACRO_GETOPT_NUM_OF_OPTIONS
};   	

#undef  XMACRO_GETOPT_OPTION_NO_ARG
#define XMACRO_GETOPT_OPTION_NO_ARG(TAG, SHORT) TAG = SHORT,   

enum VALUES
{
    XMACRO_GETOPT_OPTIONS_NO_ARG
    XMACRO_GETOPT_OPTIONS_WITH_ARG
};   	

#undef  XMACRO_GETOPT_OPTION_NO_ARG
#define XMACRO_GETOPT_OPTION_NO_ARG(TAG, SHORT) 0,    
unsigned char xmacro_getopt_option_used[] ={
    XMACRO_GETOPT_OPTIONS_NO_ARG
    XMACRO_GETOPT_OPTIONS_WITH_ARG
};

#undef  XMACRO_GETOPT_OPTION_NO_ARG
#define XMACRO_GETOPT_OPTION_NO_ARG(TAG, SHORT) , SHORT
#undef  XMACRO_GETOPT_OPTION_WITH_ARG
#define XMACRO_GETOPT_OPTION_WITH_ARG(TAG, SHORT) , SHORT, ':'
char xmacro_getopt_optstring[] = {':' XMACRO_GETOPT_OPTIONS_NO_ARG XMACRO_GETOPT_OPTIONS_WITH_ARG, '0'};

#define  XMACRO_GETOPT(ARGC, ARGV) getopt(ARGC, ARGV, xmacro_getopt_optstring)

#endif /* XMACRO_GETOPT_USE_LONG_OPTIONS */

#endif /* XMACRO_GETOPT_H */
