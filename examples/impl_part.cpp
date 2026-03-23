// impl_part.cppm
// Internal module partition unit
// is this a module partition implementations? CK

module;

#ifdef PLAY_HAS_IMPORT_STD
import std;
#else
# include <iostream>
# include <string_view>
#endif

module M;

constexpr std::string_view W{"World."};
// MSVC error C7619: cannot export 'World' as module partition 'impl_part' does not contribute to the exported interface of
// module unit 'M'
void World() {
    std::cout << W << '\n';
}
