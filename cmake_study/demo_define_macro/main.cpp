#include <iostream>

int main(){
#if defined(PPT)	
	std::cout<< "defined PPT"<<std::endl;
#endif
#ifdef HAVE_PI
	std::cout<< "pi: "<<PI<<std::endl;
#endif

#ifdef E
	std::cout << "e: " << E << std::endl;
#endif
}