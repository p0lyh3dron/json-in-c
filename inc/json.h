#pragma once

#define HAS_OBJECT 	1 << 0
#define VALUE_IS_ARRAY 	1 << 1

#define nullptr 0x0

#include <stdio.h>
#include <malloc.h>

typedef unsigned int u32_t;

typedef struct json_head_s
{
	u32_t flags;
	const char* label;
	union
	{
		struct json_head_s* next;
		const char* value;
	};
}json_head_t;

void hop			//	Skips white space
	( char* buf,		//	Input buffer
	  u32_t* p )		//	Buffer index
{
start:;
	for ( ; buf[ *p ] && buf[ *p ] <= ' '; ++*p )
	{
		
	}
}

char* string			//	Reads string
	( char* buf,		//	Input buffer
	  u32_t* p )		//	Buffer index
{
	char* str = buf + *p;
	for ( ; buf[ *p ] && buf[ *p ] != '\"' ; ++*p )
	{
		
	}
	buf[ *p ] = '\0';
	++*p;
	
	return str;
}

json_head_t parse
	( char* buf, u32_t* p, u32_t fileLen )
{
	json_head_t json;
	json.flags = 0;
	json.label = nullptr;
	json.next  = nullptr;

	hop( buf, &p );
	
	for ( ; p < fileLen; )
	{
		if ( buf[ p ] == '}' )
		{
			++p;
			return json;
		}
		json.label = string( buf, &p );
		if ( buf[ p ] == ':' )
		{
			++p;
			hop( buf, &p );
			if ( buf[ p ] == '{' )
			{
				++p;
				json.next = parse( buf, &p, fileLen );
			}
		}
	}

	return json;
}
