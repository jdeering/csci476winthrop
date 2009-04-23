#pragma once
#include "GameFramework.h"
class GFObject
{
	/* SO THAT THE FRAMEWORK CAN ACCESS PROTECTED MEMBERS */
	friend class GameFramework;

	public:
		/* 
			A QUICK COMMENT ABOUT THIS OPERATOR:
			there should be no case where this operator is EVER true, except in the case
			where a function return value is checked against null. for that reason, this
			operator serves only to service the needs of error checking.
		*/
		bool operator==(const GFObject& o)
		{ return _ref == o._ref; };

	protected:
		/* PROTECTED CONSTRUCTOR */
		GFObject(int ref) : _ref(ref) { };

		static int const GFW_BUFFER_SIZE = 128;
	
		/* REFERENCE NUMBER FOR FRAMEWORK */
		int _ref;

		void _clrBuffer(char buffer[]){ memset(buffer, 0, GFW_BUFFER_SIZE); }
};
