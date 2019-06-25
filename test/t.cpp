/*
  c++ -g -v -std=c++14 -I$home/.local/include t.cpp test.cpp -lclcxx -L$home/.local/lib

  c++ -g -v -std=c++14 -I$home/.local/include t.cpp test.cpp ../../CLCXX/lib/libclcxx.so -Wl,-rpath,../../CLCXX/lib

*/

#include <iostream>
#include <string>

#include "clcxx/clcxx.hpp"

// defined in test.cpp
CLCXX_PACKAGE TEST(clcxx::Package& ) ;

void error_handler(char *s)
{
    std::cout << "Error handler: " << "s" << std::endl ;
}

void reg_package(clcxx::MetaData *meta, uint8_t type)
{
    std::cout << "reg package: " << (int)type << std::endl ;

    switch(type) {
    case 0: // class
        std::cout << "Class:" ;
        std::cout << "  name = " << meta->Class.name << std::endl;
        //super_classes = 0x0,
        std::cout << "  slot_names = " << meta->Class.slot_names << std::endl;
        std::cout << "  slot_types = " << meta->Class.slot_types << std::endl;
        //constructor = 0x0,
        //destructor =

        break;
    case 1: // constant
        break;
    case 2: //function
        std::cout << "Function:";
        std::cout << "  name = " << meta->Func.name << std::endl;
        std::cout << "  method_p = " << (meta->Func.method_p ? "true" : "false") << std::endl;
        //class_obj = 0x0,
        std::cout << "  func_ptr = " << std::hex << meta->Func.func_ptr << std::endl;
        if (meta->Func.arg_types == 0)
            std::cout << "  arg_types = " << " 0 " << std::endl;
        else
            std::cout << "  arg_types = " << meta->Func.arg_types << std::endl;
        std::cout << "  retrun_type = " << meta->Func.return_type << std::endl;

        break;
    }
    std::cout << std::endl << std::flush ;

/*
  name = 0x55555578f3c0 "hi",
  method_p = false,
  class_obj = 0x0,
  thunk_ptr = 0x555555561d4a <clcxx::detail::CallFunctor<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, char*>::apply(void const*, void*)>,
  func_ptr = 0x55555578f3e0,
  arg_types = 0x55555578f440 "(:pointer :char)+",
  return_type = 0x55555578f460 ":string"
*/
}


int main()
{
    std::cout << "" << std::endl ;

    bool r ;
    r = clcxx_init(&error_handler, &reg_package) ;

    r = register_package("TEST", TEST);

    return 0;
}
