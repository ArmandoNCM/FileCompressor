#include <limits>
#include <bitset>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

// http://en.cppreference.com/w/cpp/language/type_alias
using byte = unsigned char ;

// http://en.cppreference.com/w/cpp/types/numeric_limits
constexpr std::size_t BITS_PER_BYTE = std::numeric_limits<byte>::digits ;

// http://en.cppreference.com/w/cpp/utility/bitset
using bits_in_byte = std::bitset<BITS_PER_BYTE> ;

std::string read_bits( const char* path_to_file )
{
    std::string bitstring ;
    std::ifstream file( path_to_file, std::ios::binary ) ; // open in binary mode

    char c ;
    while( file.get(c) ) // read byte by byte
        bitstring += bits_in_byte( byte(c) ).to_string() ; // append as string of '0' '1'

    return bitstring ;
}


int main(int argc, char const *argv[])
{
	if(argc < 2)
		return 1;
	std::cout << read_bits(argv[1]) << std::endl;
}