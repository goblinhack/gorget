//
// Copyright goblinhack@gmail.com
//

#ifndef MY_FILENODE_HPP
#define MY_FILENODE_HPP

auto dir_exists(const char *indir) -> bool;
auto dir_dot() -> char *;
auto dir_dotdot(char *s) -> char *;
auto dospath2unix(char *in) -> char *;

#endif
