#pragma once

/* credits @uc */
template<typename Function>Function getvfunc(void*_VMT, int Index)
{
	void***_TVMT = (void***)_VMT;
	void**VMT = *_TVMT;
	void*_Address = VMT[Index];
	return(Function)(_Address);
}
